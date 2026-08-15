#include "sc2_coordinator.h"

#include <algorithm>
#include <cassert>
#include <fstream>
#include <iostream>
#include <thread>

#include "sc2_agent.h"
#include "sc2_args.h"
#include "sc2_control_interfaces.h"
#include "sc2_interfaces.h"
#include "sc2_replay_observer.h"
#include "s2clientprotocol/sc2api.pb.h"
#include "sc2lib/sc2_errors.h"
#include "sc2utils/sc2_manage_process.h"

import sc2_scan_directory;

namespace sc2 {

using ranges::any_of,
    std::vector;

void RunParallel(const function<void(Agent* a)>& step, const vector<Agent*>& agents) {
    // Run all steps in parallel.
    vector<thread> threads(agents.size());
    for (size_t i = 0; i < agents.size(); ++i) {
        Agent* a = agents[i];
        threads[i] = thread(bind(step, a));
    }

    for (auto& t : threads) {
        t.join();
    }
}

int LaunchProcess(ProcessSettings& process_settings, Client* client, int window_width, int window_height,
                  int window_start_x, int window_start_y, int port, int client_num = 0) {
    assert(client);
    process_settings.process_info.push_back(sc2::ProcessInfo());
    ProcessInfo& pi = process_settings.process_info.back();

    // Get the next port
    pi.port = port;

    // Command line arguments that will be passed to sc2.
    vector<string> cl = {"-listen", process_settings.net_address, "-port", to_string(pi.port)};

    cl.push_back("-displayMode");
    if (process_settings.full_screen && client_num == 0)
        cl.push_back("1");
    else
        cl.push_back("0");

    if (process_settings.data_version.size() > 0) {
        cl.push_back("-dataVersion");
        cl.push_back(process_settings.data_version);
    }

    for (const string& command : process_settings.extra_command_lines)
        cl.push_back(command);

    cl.push_back("-windowwidth");
    cl.push_back(to_string(window_width));
    cl.push_back("-windowheight");
    cl.push_back(to_string(window_height));

    if (client_num < 2) {
        cl.push_back("-windowx");
        cl.push_back(to_string(window_start_x + window_width * client_num));
        cl.push_back("-windowy");
        cl.push_back(to_string(window_start_y));
    } else if (client_num < 4) {
        cl.push_back("-windowx");
        cl.push_back(to_string(window_start_x + window_width * (client_num - 2)));
        cl.push_back("-windowy");
        cl.push_back(to_string(window_start_y + window_height));
    }

    pi.process_path = process_settings.process_path;
    pi.process_id = StartProcess(process_settings.process_path, cl);
    if (!pi.process_id) {
        cerr << "Unable to start sc2 executable with path: " << process_settings.process_path << '\n';
    } else {
        cout << "Launched SC2 (" << process_settings.process_path << "), PID: " << to_string(pi.process_id)
                  << '\n';
    }

    client->Control()->SetProcessInfo(pi);
    return pi.port;
}

bool AttachClients(const ProcessSettings& process_settings, const vector<Client*>& clients) {
    bool connected = false;

    // Since connect is blocking do it after the processes are launched.
    for (size_t i = 0; i < clients.size(); ++i) {
        const ProcessInfo& pi = process_settings.process_info[i];
        Client* c = clients[i];

        connected = c->Control()->Connect(process_settings.net_address, pi.port, process_settings.timeout_ms);
        if (!connected)
            throw ClientConnectionError(process_settings.net_address, pi.port);
    }

    return connected;
}

int LaunchProcesses(ProcessSettings& process_settings, const vector<Client*>& clients, int window_width,
                    int window_height, int window_start_x, int window_start_y) {
    int last_port = 0;
    // Start an sc2 process for each bot.
    int clientIndex = 0;
    for (auto c : clients) {
        last_port = LaunchProcess(
            process_settings, c, window_width, window_height, window_start_x, window_start_y,
            process_settings.port_start + static_cast<int>(process_settings.process_info.size()) - 1, clientIndex++);
    }

    AttachClients(process_settings, clients);

    return last_port;
}

static void CallOnStep(Agent* a) {
    ControlInterface* control = a->Control();
    if (!control->IsInGame()) {
        a->OnGameEnd();
        control->RequestLeaveGame();  // Only for multiplayer.
        return;
    }

    ActionInterface* action = a->Actions();
    control->IssueEvents(action->Commands());
    if (action) {
        action->SendActions();
    }

    if (ActionFeatureLayerInterface* action_feature_layer = a->ActionsFeatureLayer()) {
        action_feature_layer->SendActions();
    }
}

// Implementation.
class CoordinatorImpl {
public:
    vector<Agent*> agents_;
    vector<ReplayObserver*> replay_observers_;

    bool game_ended_;
    bool starcraft_started_;

    GameSettings game_settings_;
    ReplaySettings replay_settings_;
    InterfaceSettings interface_settings_;
    ProcessSettings process_settings_;

    CoordinatorImpl();
    ~CoordinatorImpl();

    bool StartGame() const;
    bool CreateGame() const;
    bool JoinGame() const;
    void StartReplay();
    bool ShouldIgnore(ReplayObserver* r, const string& file) const;
    bool ShouldRelaunch(ReplayObserver* r);

    void StepAgents() const;
    void StepAgentsRealtime() const;
    void StepReplayObservers() const;
    void StepReplayObserversRealtime() const;

    bool AnyObserverAvailable() const;

    bool WaitForAllResponses() const;
    void AddAgent(Agent* agent);

    bool Relaunch(ReplayObserver* replay_observer);

    int window_width_ = 1024;
    int window_height_ = 768;

    int window_start_x_ = 100;
    int window_start_y_ = 200;

    // If a ReplayObserver fails, try to recover
    bool replay_recovery_ = true;
    int last_port_ = 0;

    bool use_generalized_ability_id = true;
};

CoordinatorImpl::CoordinatorImpl()
    : agents_(),
      replay_observers_(),
      game_ended_(),
      starcraft_started_(false),
      game_settings_(),
      process_settings_(false, 1, "", "127.0.0.1", kDefaultProtoInterfaceTimeout, 8168, false) {
}

CoordinatorImpl::~CoordinatorImpl() {
    for (auto& p : process_settings_.process_info) {
        TerminateProcess(p.process_id);
    }
}

bool CoordinatorImpl::AnyObserverAvailable() const {
    return any_of(replay_observers_.cbegin(), replay_observers_.cend(),
                       [](ReplayObserver* r) { return !r->Control()->IsInGame(); });
}

bool CoordinatorImpl::ShouldIgnore(ReplayObserver* r, const string& file) const {
    if (file.empty())
        return true;

    // NOTE (alkurbatov): Gather replay information with the available observer.
    // In case of any error occurred during loading of replays info ignore the target replay.
    if (!r->ReplayControl()->GatherReplayInfo(file, true))
        return true;

    // If the replay isn't being pruned based on replay info start it.
    return r->IgnoreReplay(r->ReplayControl()->GetReplayInfo(), replay_settings_.player_id);
}

bool CoordinatorImpl::ShouldRelaunch(ReplayObserver* r) {
    const ReplayInfo& replay_info = r->ReplayControl()->GetReplayInfo();

    bool version_match = replay_info.base_build == r->Control()->Proto().GetBaseBuild() &&
                         replay_info.data_version == r->Control()->Proto().GetDataVersion();
    if (version_match)
        return false;

    // Version failed to download. Just continue with trying to load in current version.
    // It will likely fail, and then just skip past this replay.
    if (!FindBaseExe(process_settings_.process_path, replay_info.base_build))
        return false;

    cout << "Replay is from a different version. Relaunching client into the correct version..." << '\n';
    process_settings_.data_version = replay_info.data_version;
    r->Control()->Error(ClientError::WrongGameVersion);
    return true;
}

void CoordinatorImpl::StartReplay() {
    // If no replays given in the settings don't try.
    if (replay_settings_.replay_file.empty()) {
        return;
    }

    assert(!replay_observers_.empty());
    if (!starcraft_started_) {
        last_port_ = LaunchProcesses(process_settings_,
                                     vector<Client*>(replay_observers_.begin(), replay_observers_.end()),
                                     window_width_, window_height_, window_start_x_, window_start_y_);
    }

    // Run a replay with each available replay observer.
    for (auto r : replay_observers_) {
        // If the replay observer is idle or out of game use it for a new replay.
        if (!r->Control()->IsReadyForCreateGame()) {
            continue;
        }

        r->ReplayControl()->UseGeneralizedAbility(use_generalized_ability_id);

        auto& replays = replay_settings_.replay_file;
        while (replays.size() != 0) {
            const string& file = replay_settings_.replay_file.back();

            if (ShouldIgnore(r, file)) {
                replays.pop_back();
                continue;
            }

            if (ShouldRelaunch(r)) {
                break;
            }

            bool launched = r->ReplayControl()->LoadReplay(file, interface_settings_, replay_settings_.player_id,
                                                           process_settings_.realtime);
            replays.pop_back();
            if (launched)
                break;
        }
    }

    starcraft_started_ = true;
}

void CoordinatorImpl::StepAgents() const {
    auto step_agent = [this](Agent* a) {
        ControlInterface* control = a->Control();

        if (control->GetAppState() != AppState::normal) {
            return;
        }

        if (control->PollLeaveGame()) {
            return;
        }

        if (control->IsFinishedGame()) {
            return;
        }

        control->Step(process_settings_.step_size);
        control->WaitStep();
        if (process_settings_.multi_threaded) {
            CallOnStep(a);
        }
    };

    if (agents_.size() == 1) {
        step_agent(agents_.front());
    } else {
        RunParallel(step_agent, agents_);
    }

    if (!process_settings_.multi_threaded) {
        for (auto a : agents_) {
            if (a->Control()->GetAppState() != AppState::normal) {
                continue;
            }

            // It is possible to have a pending leave game request here.
            if (a->Control()->PollLeaveGame()) {
                continue;
            }

            CallOnStep(a);
        }
    }
}

void CoordinatorImpl::StepAgentsRealtime() const {
    auto step_agent = [](Agent* a) {
        ControlInterface* control = a->Control();
        if (!control) {
            return;
        }

        if (control->GetAppState() != AppState::normal) {
            return;
        }

        if (control->PollLeaveGame()) {
            return;
        }

        if (a->Control()->IsFinishedGame()) {
            return;
        }

        ActionInterface* action = a->Actions();
        if (!action) {
            return;
        }

        // This agent shouldn't call step since it's real time.
        control->GetObservation();
        control->IssueEvents(a->Actions()->Commands());
        action->SendActions();

        if (!control->IsInGame()) {
            a->OnGameEnd();
            a->Control()->RequestLeaveGame();  // Only for multiplayer.
            return;
        }
    };

    if (process_settings_.multi_threaded) {
        RunParallel(step_agent, agents_);
    } else {
        for (auto a : agents_) {
            step_agent(a);
        }
    }
}

void CoordinatorImpl::StepReplayObservers() const {
    // Run all replay observers.
    auto run_replay = [this](ReplayObserver* r) {
        if (r->Control()->GetAppState() != AppState::normal) {
            return;
        }

        // If the replay is loading wait for it to finish loading before performing a step.
        if (r->Control()->HasResponsePending()) {
            // Don't consume a response if there isn't one in the queue.
            if (replay_observers_.size() > 1 && !r->Control()->PollResponse()) {
                return;
            }
            r->ReplayControl()->WaitForReplay();
        }

        if (r->Control()->IsInGame()) {
            r->Control()->Step(process_settings_.step_size);
            r->Control()->WaitStep();

            // If multithreaded run everyone's OnStep in parallel.
            if (process_settings_.multi_threaded) {
                r->Control()->IssueEvents();
                r->ObserverAction()->SendActions();
            }

            if (!r->Control()->IsInGame()) {
                r->OnGameEnd();
            }
        }
    };

    if (replay_observers_.size() == 1) {
        run_replay(replay_observers_.front());
    } else {
        // Run all steps in parallel.
        vector<thread> threads;
        threads.reserve(replay_observers_.size());
        for (auto r : replay_observers_) {
            threads.emplace_back(run_replay, r);
        }

        // Join all threads.
        for (auto& t : threads) {
            t.join();
        }
    }

    // Do everyone's OnStep, if not multi threaded, in single threaded mode.
    if (!process_settings_.multi_threaded) {
        for (auto r : replay_observers_) {
            if (r->Control()->GetAppState() != AppState::normal) {
                continue;
            }

            r->Control()->IssueEvents();
            r->ObserverAction()->SendActions();
        }
    }
}

void CoordinatorImpl::StepReplayObserversRealtime() const {
    // Run all replay observers.
    auto run_replay = [this](ReplayObserver* r) {
        if (r->Control()->GetAppState() != AppState::normal) {
            return;
        }

        // If the replay is loading wait for it to finish loading before performing a step.
        if (r->Control()->HasResponsePending()) {
            // Don't consume a response if there isn't one in the queue.
            if (replay_observers_.size() > 1 && !r->Control()->PollResponse()) {
                return;
            }
            r->ReplayControl()->WaitForReplay();
        }

        if (r->Control()->IsInGame()) {
            r->Control()->GetObservation();

            // If multithreaded run everyone's OnStep in parallel.
            if (process_settings_.multi_threaded) {
                r->Control()->IssueEvents();
            }

            if (!r->Control()->IsInGame()) {
                r->OnGameEnd();
            }
        }
    };

    if (replay_observers_.size() == 1) {
        run_replay(replay_observers_.front());
    } else {
        // Run all steps in parallel.
        vector<thread> threads;
        threads.reserve(replay_observers_.size());
        for (auto r : replay_observers_) {
            threads.emplace_back(run_replay, r);
        }

        // Join all threads.
        for (auto& t : threads) {
            t.join();
        }
    }

    // Do everyone's OnStep, if not multi threaded, in single threaded mode.
    if (!process_settings_.multi_threaded) {
        for (auto r : replay_observers_) {
            if (r->Control()->GetAppState() != AppState::normal) {
                continue;
            }

            r->Control()->IssueEvents();
        }
    }
}

bool CoordinatorImpl::WaitForAllResponses() const {
    static constexpr int sleep_ms = 50;

    int total_sleep_ms = 0;
    for (;;) {
        bool has_responses = false;

        for (Agent* agent : agents_) {
            if (!agent->Control()->HasResponsePending() || agent->Control()->GetAppState() != AppState::normal) {
                continue;
            }

            has_responses = true;

            if (agent->Control()->PollResponse()) {
                agent->Control()->ConsumeResponse();
            }

            break;
        }

        for (ReplayObserver* replay_observer : replay_observers_) {
            if (has_responses) {
                break;
            }

            if (!replay_observer->Control()->HasResponsePending() ||
                replay_observer->Control()->GetAppState() != AppState::normal) {
                continue;
            }
            has_responses = true;

            if (replay_observer->Control()->PollResponse()) {
                replay_observer->Control()->ConsumeResponse();
            }

            break;
        }

        if (!has_responses) {
            break;
        }

        if (total_sleep_ms >= process_settings_.timeout_ms) {
            assert(0);
            return false;
        }

        SleepFor(sleep_ms);
        total_sleep_ms += sleep_ms;
    }

    return true;
}

bool CoordinatorImpl::CreateGame() const {
    // Create the game with the first client.
    Agent* firstClient = agents_.front();
    return firstClient->Control()->CreateGame(game_settings_.map_name,
                                              game_settings_.player_setup,
                                              process_settings_.realtime);
}

bool CoordinatorImpl::JoinGame() const {
    int i = 0;
    for (auto c : agents_) {
        bool game_join_request =
            c->Control()->RequestJoinGame(game_settings_.player_setup[i++], interface_settings_, game_settings_.ports,
                                          game_settings_.raw_affects_selection);

        if (!game_join_request) {
            cerr << "Unable to join game." << '\n';
            exit(1);
        }
    }

    for (auto c : agents_) {
        c->Control()->WaitJoinGame();
    }

    // Check if any errors occurred during game start.
    bool errors_occurred = false;
    for (auto c : agents_) {
        ControlInterface* control = c->Control();
        const vector<ClientError>& client_errors = control->GetClientErrors();
        if (!client_errors.empty()) {
            c->OnError(client_errors, control->GetProtocolErrors());
            errors_occurred = true;
        }

        c->Control()->UseGeneralizedAbility(use_generalized_ability_id);
    }

    if (errors_occurred) {
        return false;
    }

    // Run all clients on game start.
    for (auto c : agents_) {
        c->Control()->GetObservation();
    }
    for (auto c : agents_) {
        c->OnGameFullStart();
    }
    for (auto c : agents_) {
        c->Control()->OnGameStart();
        c->OnGameStart();
    }
    for (auto c : agents_) {
        c->Control()->IssueEvents(c->Actions()->Commands());
    }

    return true;
}

bool CoordinatorImpl::StartGame() const {
    assert(starcraft_started_);
    bool is_game_created = CreateGame();
    if (!is_game_created) {
        cerr << "Failed to create game." << '\n';
        exit(1);
    }
    return JoinGame();
}

bool CoordinatorImpl::Relaunch(ReplayObserver* replay_observer) {
    ControlInterface* control = replay_observer->Control();
    const ProcessInfo& pi = control->GetProcessInfo();

    // Try to kill SC2 then relaunch it
    sc2::TerminateProcess(pi.process_id);

    // NOTE (alkurbatov): Reset the control interface
    // so internal state gets reinitialized.
    replay_observer->Reset();

    // Control interface has been reconstructed.
    control = replay_observer->Control();

    last_port_ = LaunchProcess(process_settings_, replay_observer, window_width_, window_height_, window_start_x_,
                               window_start_y_, last_port_ + 1);

    const ProcessInfo& pi_new = control->GetProcessInfo();

    return control->Connect(process_settings_.net_address, pi_new.port, process_settings_.timeout_ms);
}

// Coordinator.

Coordinator::Coordinator() {
    impl_ = new CoordinatorImpl();
}

Coordinator::~Coordinator() {
    delete impl_;
}

bool Coordinator::StartGame(const string& map_path) const {
    if (!map_path.empty())
        impl_->game_settings_.map_name = map_path;
    return impl_->StartGame();
}

bool Coordinator::JoinGame() const {
    return impl_->JoinGame();
}

bool Coordinator::CreateGame(const string& map_path) const {
    if (!map_path.empty())
        impl_->game_settings_.map_name = map_path;
    return impl_->CreateGame();
}

bool Coordinator::RemoteSaveMap(const void* data, int data_size, const string& remote_path) const {
    for (Agent* c : impl_->agents_) {
        if (!c->Control()->RemoteSaveMap(data, data_size, remote_path))
            return false;
    }

    for (ReplayObserver* c : impl_->replay_observers_) {
        if (!c->Control()->RemoteSaveMap(data, data_size, remote_path))
            return false;
    }

    return true;
}

void Coordinator::SetParticipants(const vector<PlayerSetup>& participants) const {
    impl_->game_settings_.player_setup.clear();
    impl_->agents_.clear();

    for (const auto& p : participants) {
        if (p.agent) {
            impl_->AddAgent(p.agent);
        }
        impl_->game_settings_.player_setup.push_back(p);
    }
}

void Coordinator::SetReplayRecovery(const bool value) const {
    impl_->replay_recovery_ = value;
}

bool Coordinator::LoadSettings(span<char*> args) const {
    return ParseSettings(args, impl_->process_settings_, impl_->game_settings_);
}

void Coordinator::LaunchStarcraft() const {
    if (!DoesFileExist(impl_->process_settings_.process_path)) {
        cerr << "Executable path can't be found, try running the StarCraft II executable first." << '\n';
        if (!impl_->process_settings_.process_path.empty()) {
            cerr << impl_->process_settings_.process_path << " does not exist on your filesystem.";
        }
        cerr << '\n';
        assert(!"Could not find the executable. Supply a valid path.");
        exit(1);
    }

    assert(!impl_->agents_.empty());

    // TODO: Check the case that a pid in the process_info_ struct is no longer running.
    // The process may have died.
    int port_start = 0;
    if (impl_->process_settings_.process_info.size() != impl_->agents_.size()) {
        port_start = LaunchProcesses(
            impl_->process_settings_, vector<sc2::Client*>(impl_->agents_.begin(), impl_->agents_.end()),
            impl_->window_width_, impl_->window_height_, impl_->window_start_x_, impl_->window_start_y_);
    }

    SetupPorts(impl_->agents_.size(), port_start);

    impl_->starcraft_started_ = true;
    impl_->last_port_ = port_start;
}

void Coordinator::Connect(int port) const {
    if (!impl_->agents_.front()->Control()->Connect(impl_->process_settings_.net_address, port,
                                                   impl_->process_settings_.timeout_ms)) {
        cerr << "Failed to attach to starcraft." << '\n';
        exit(1);
    }

    // Assume starcraft has started after successfully attaching to a server.
    impl_->starcraft_started_ = true;
}

void Coordinator::LeaveGame() const {
    for (auto c : impl_->agents_) {
        c->Control()->RequestLeaveGame();
    }
}

void Coordinator::WaitForAllResponses() const {
    impl_->WaitForAllResponses();
}

bool Coordinator::Update() const {
    if (impl_->agents_.size() > 0) {
        if (impl_->process_settings_.realtime) {
            impl_->StepAgentsRealtime();
        } else {
            impl_->StepAgents();
        }
    }

    if (impl_->replay_observers_.size() > 0 && impl_->starcraft_started_) {
        if (impl_->process_settings_.realtime) {
            impl_->StepReplayObserversRealtime();
        } else {
            impl_->StepReplayObservers();
        }
    }

    if (impl_->replay_observers_.size() > 0) {
        if (impl_->AnyObserverAvailable()) {
            impl_->StartReplay();
        }
    }

    // Check for errors in all agents/replay observers at the end of an update.
    bool error_occurred = false;
    for (auto agent : impl_->agents_) {
        const ControlInterface* control = agent->Control();
        const vector<ClientError>& client_errors = control->GetClientErrors();
        if (!client_errors.empty()) {
            agent->OnError(client_errors, control->GetProtocolErrors());
            error_occurred = true;
        }
    }

    bool relaunched = false;
    for (ReplayObserver* replay_observer : impl_->replay_observers_)
        {
        const ControlInterface* control = replay_observer->Control();
        if (const vector<ClientError>& client_errors = control->GetClientErrors(); !client_errors.empty())
            {
            replay_observer->OnError(client_errors, control->GetProtocolErrors());
            error_occurred = true;
            if (impl_->replay_recovery_)
                {
                // An error did occur but if we successfully recovered ignore it. The client will still gets its event
                if (impl_->Relaunch(replay_observer))
                    {
                    error_occurred = false;
                    relaunched = true;
                }
            }
        }
    }

    // End the coordinator update on the idea that an error in the API should mean it's time to stop.
    if (error_occurred) {
        return false;
    }

    return !AllGamesEnded() || relaunched;
}

bool Coordinator::AllGamesEnded() const {
    for (auto a : impl_->agents_) {
        if (a->Control()->IsInGame() || a->Control()->HasResponsePending()) {
            return false;
        }
    }

    for (auto r : impl_->replay_observers_) {
        if (r->Control()->IsInGame() || r->Control()->HasResponsePending()) {
            return false;
        }
    }

    return true;
}

void CoordinatorImpl::AddAgent(Agent* agent) {
    assert(agent);
    agents_.push_back(agent);
}

void Coordinator::AddReplayObserver(ReplayObserver* replay_observer) const {
    assert(replay_observer);
    impl_->replay_observers_.push_back(replay_observer);
}

void Coordinator::SetMultithreaded(bool value) const {
    impl_->process_settings_.multi_threaded = value;
}

void Coordinator::SetRealtime(bool value) const {
    // Realtime must be set before LaunchStarcraft is called.
    assert(!impl_->starcraft_started_);
    impl_->process_settings_.realtime = value;
}

void Coordinator::SetStepSize(int step_size) const {
    if (step_size < 1) {
        assert(0);
        return;
    }

    // SetStepSize must be set before LaunchStarcraft is called.
    assert(!impl_->starcraft_started_);
    impl_->process_settings_.step_size = step_size;
}

void Coordinator::SetProcessPath(const string& path) const {
    assert(!impl_->starcraft_started_);
    impl_->process_settings_.process_path = path;
}

void Coordinator::SetDataVersion(const string& version) const {
    assert(!impl_->starcraft_started_);
    impl_->process_settings_.data_version = version;
}

void Coordinator::SetTimeoutMS(uint32_t timeout_ms) const {
    impl_->process_settings_.timeout_ms = timeout_ms;
}

void Coordinator::SetPortStart(int port_start) const {
    assert(!impl_->starcraft_started_);
    impl_->process_settings_.port_start = port_start;
}

void Coordinator::SetFeatureLayers(const FeatureLayerSettings& settings) const {
    // Feature Layers must be set before LaunchStarcraft is called.
    assert(!impl_->starcraft_started_);
    impl_->interface_settings_.use_feature_layers = true;
    impl_->interface_settings_.feature_layer_settings = settings;
}

void Coordinator::SetRender(const RenderSettings& settings) const {
    // Render must be set before LaunchStarcraft is called.
    assert(!impl_->starcraft_started_);
    impl_->interface_settings_.use_render = true;
    impl_->interface_settings_.render_settings = settings;
}

void Coordinator::SetWindowSize(int width, int height) const {
    assert(!impl_->starcraft_started_);
    impl_->window_width_ = width;
    impl_->window_height_ = height;
}

void Coordinator::SetWindowLocation(int x, int y) const {
    assert(!impl_->starcraft_started_);
    impl_->window_start_x_ = x;
    impl_->window_start_y_ = y;
}

void Coordinator::SetUseGeneralizedAbilityId(bool value) const {
    assert(!impl_->starcraft_started_);
    impl_->use_generalized_ability_id = value;
}

void Coordinator::SetReplayPerspective(int player_id) const {
    impl_->replay_settings_.player_id = player_id;
}

bool Coordinator::SetReplayPath(const string& path) const {
    impl_->replay_settings_.replay_file.clear();

    if (HasExtension(path, ".SC2Replay")) {
        impl_->replay_settings_.replay_file.push_back(path);
    } else {
        impl_->replay_settings_.replay_dir = path;

        // Gather and append all files from the directory.
        if (!impl_->replay_settings_.replay_dir.empty()) {
            scan_directory(impl_->replay_settings_.replay_dir.c_str(), impl_->replay_settings_.replay_file, true, false);
        }
    }

    return !impl_->replay_settings_.replay_file.empty();
}

bool Coordinator::LoadReplayList(const string& path) const {
    if (!DoesFileExist(path))
        return false;

    impl_->replay_settings_.replay_file.clear();

    ifstream replay_file(path);

    string line;
    while (getline(replay_file, line)) {
        if (line.length() < 5)
            continue;

        impl_->replay_settings_.replay_file.push_back(line);
    }

    return true;
}

void Coordinator::SaveReplayList(const string& path) const {
    ofstream replay_file(path, ofstream::out | ofstream::trunc);
    for (const string& line : impl_->replay_settings_.replay_file) {
        replay_file << line << '\n';
    }
}

bool Coordinator::HasReplays() const {
    return !impl_->replay_settings_.replay_file.empty();
}

void Coordinator::AddCommandLine(const string& option) const {
    impl_->process_settings_.extra_command_lines.push_back(option);
}

void Coordinator::SetRawAffectsSelection(bool value) const {
    impl_->game_settings_.raw_affects_selection = value;
}

void Coordinator::SetFullScreen(bool value) const {
    impl_->process_settings_.full_screen = value;
}

string Coordinator::GetExePath() const {
    if (impl_->process_settings_.process_path.length() > 4)
        return impl_->process_settings_.process_path;

    return impl_->process_settings_.process_path;
}

void Coordinator::SetupPorts(size_t num_agents, int port_start, bool check_single) const {
    // Join the game if there are two human participants.
    size_t humans = 0;
    if (check_single) {
        for (const auto& p_setup : impl_->game_settings_.player_setup) {
            if (p_setup.type == sc2::PlayerType::Participant) {
                ++humans;
            }
        }
    } else {
        humans = num_agents;
    }
    if (humans > 1) {
        impl_->game_settings_.ports.shared_port = ++port_start;
        impl_->game_settings_.ports.server_ports.game_port = ++port_start;
        impl_->game_settings_.ports.server_ports.base_port = ++port_start;
        for (size_t i = 1; i < num_agents; ++i) {
            PortSet port_set;
            port_set.game_port = ++port_start;
            port_set.base_port = ++port_start;
            impl_->game_settings_.ports.client_ports.push_back(port_set);
        }
    }
}
}  // namespace sc2
