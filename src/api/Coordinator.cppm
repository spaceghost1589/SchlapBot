/*! \file Coordinator.cppm
    \brief Frontend for running a game.

    The Coordinator acts as a game and bot manager. It is used to launch
   StarCraft and setup protocol connections between a user's bot and the running
   StarCraft instance. With it a user steps forward a simulation and it will
   fill out bot interface data.

   Only called in main.
*/
module;
#include <cassert>
#include <functional>
#include <iostream>
#include <thread>

#include "api/agent.h"
#include "api/args.h"
#include "api/replay_observer.h"
#include "lib/game_settings.h"
#include "utils/manage_process.h"
export module Coordinator;
import enum_db;
import protocol_interface;


using std::function, std::ifstream, std::ofstream, std::cerr, std::cout,
        std::span, std::string, std::thread, std::to_string, std::vector;

// #include "s2clientprotocol/sc2api.pb.h"
//
// #include "agent.h"
// #include "args.h"
// #include "control_interfaces.h"
// #include "interfaces.h"
// #include "replay_observer.h"
// #include "lib/errors.h"
// #include "utils/manage_process.h"
//
// import scan_directory;

// }

export namespace sc2 {

//! Coordinator of one or more clients. Used to start, step and stop games and
//! replays.
class Coordinator {
public:
    vector<Agent*>          agents_;
    vector<ReplayObserver*> replay_observers_;

    bool game_ended_ {};
    bool starcraft_started_ {};

    GameSettings      game_settings_;
    ReplaySettings    replay_settings_;
    InterfaceSettings interface_settings_;
    ProcessSettings   process_settings_;

    bool Relaunch(ReplayObserver* replay_observer);

    int window_width_  = 1024;
    int window_height_ = 768;

    int window_start_x_ = 100;
    int window_start_y_ = 200;

    // If a ReplayObserver fails, try to recover
    bool replay_recovery_ = true;
    int  last_port_       = 0;

    bool use_generalized_ability_id = true;

    Coordinator():
            agents_(),
            replay_observers_(),
            game_ended_(),
            starcraft_started_(false),
            game_settings_(),
            process_settings_(false,
                              1,
                              "",
                              "127.0.0.1",
                              kDefaultProtoInterfaceTimeout,
                              8168,
                              false) {}

    ~Coordinator() {
        for ( const ProcessInfo& p : process_settings_.process_info ) {
            TerminateProcess(p.process_id);
        }
    }

    // Initialization and setup.

    //! Used to load settings. Settings will be discovered in the following
    //! order:
    //!   1. If command line arguments are provided it will use them. Invoke
    //!   binary with --help to see expected arguments.
    //!   2. (Recommended) If the StarCraft II binary has been run the function
    //!   will auto discover its location.
    //! @param args Provided in main signature. Conversion from `int argc, char*
    //! argv[]` required.
    //! @return True if settings were found or discovered.
    bool LoadSettings(span<char*> args) {
        return ParseSettings(args, process_settings_, game_settings_);
    }

    //! Specifies whether bots or replays OnStep function should be run in
    //! parallel. If set to true make sure your bots are thread-safe if they
    //! reach into shared code.
    //! @param value True to multithread, false otherwise.
    void SetMultithreaded(bool value) {
        process_settings_.multi_threaded = value;
    }

    //! Specifies whether the game should run in realtime or not. If the game is
    //! running in real time that means the CCoordinator is not stepping it
    //! forward. The game is running and your bot reaches into it asynchronously
    //! to read state.
    //! @param value True to be realtime, false otherwise.
    void SetRealtime(bool value) {
        // Realtime must be set before LaunchStarcraft is called.
        assert(!starcraft_started_);
        process_settings_.realtime = value;
    }

    //! Sets the number of game loops to run for each step.
    //! @param step_size Number of gameloops to run for each step.
    void SetStepSize(int step_size) {
        if ( step_size < 1 ) {
            assert(0);
            return;
        }

        // SetStepSize must be set before LaunchStarcraft is called.
        assert(!starcraft_started_);
        process_settings_.step_size = step_size;
    }

    //! Sets the path to the StarCraft II binary.
    //! @param path Absolute file path.
    void SetProcessPath(const string& path) {
        assert(!starcraft_started_);
        process_settings_.process_path = path;
    }

    //! Set the correct data version of a replay to allow faster replay loading.
    //! Saves a few seconds if replay is not up to date. Works only in
    //! combination with correct process path set by "SetProcessPath".
    //! @param version Look in "protocol/buildinfo/versions.json" for the
    //! property "data-hash". Or read it from "ReplayInfo.data_version".
    [[maybe_unused]]
    void SetDataVersion(const string& version) {
        assert(!starcraft_started_);
        process_settings_.data_version = version;
    }

    //! Sets the timeout for network operations.
    //! @param timeout_ms in milliseconds.
    void SetTimeoutMS(uint32_t timeout_ms) {
        process_settings_.timeout_ms = timeout_ms;
    }

    //! Sets the first port number to use. Subsequent port assignments are
    //! sequential.
    //! @param port_start First port number.
    void SetPortStart(int port_start) {
        assert(!starcraft_started_);
        process_settings_.port_start = port_start;
    }

    //! Indicates whether feature layers should be provided in the observation.
    //! @param settings Configuration of feature layer settings.
    //! @sa FeatureLayerSettings
    void SetFeatureLayers(const FeatureLayerSettings& settings) {
        // Feature Layers must be set before LaunchStarcraft is called.
        assert(!starcraft_started_);
        interface_settings_.use_feature_layers     = true;
        interface_settings_.feature_layer_settings = settings;
    }

    //! @sa RenderSettings
    void SetRender(const RenderSettings& settings) {
        // Render must be set before LaunchStarcraft is called.
        assert(!starcraft_started_);
        interface_settings_.use_render      = true;
        interface_settings_.render_settings = settings;
    }

    //! Sets the game window dimensions.
    //! @param width Width of game window.
    //! @param height Height of game window.
    void SetWindowSize(int width, int height) {
        assert(!starcraft_started_);
        window_width_  = width;
        window_height_ = height;
    }

    //! Sets the game window location.
    //! @param x X position of game window.
    //! @param y y position of game window.
    void SetWindowLocation(int x, int y) {
        assert(!starcraft_started_);
        window_start_x_ = x;
        window_start_y_ = y;
    }

    //! Uses generalized abilities where possible. Example:
    //! BUILD_TECHLAB_BARRACKS, BUILD_TECHLAB_FACTORY, BUILD_TECHLAB_STARPORT
    //! ability ids are generalized to BUILD_TECHLAB ability id in the
    //! observation.
    // TODO Why is this here?
    void SetUseGeneralizedAbilityId(bool value) {
        assert(!starcraft_started_);
        use_generalized_ability_id = value;
    }

    //! Sets the replay perspective. Use 0 to observe all players.
    void SetReplayPerspective(int player_id) {
        replay_settings_.player_id = player_id;
    }

    //! Appends a command line argument to be fed to StarCraft II when starting.
    //! @param option The string to be appended to the executable invoke.
    void AddCommandLine(const string& option) {
        process_settings_.extra_command_lines.push_back(option);
    }

    //! When set to true, less actions will be generated because the game will
    //! not try to keep your unit selection. Useful to reduce the number of
    //! actions, but may complicate the debugging process.
    void SetRawAffectsSelection(bool value) {
        game_settings_.raw_affects_selection = value;
    }

    //! Specifies whether the game should run in fullscreen or not.
    //! This usually indicates that a real player (the first registered
    //! participant) is using the first launched instance to play (the first
    //! registered participant).
    //!  The game will be launched in the windowed mode for the second player
    //!  (second participant).
    //! It should be used in combination with SetRealtime(true), otherwise the
    //! game has no sound.
    void SetFullScreen(bool value) {
        process_settings_.full_screen = value;
    }

    void AddAgent(Agent* agent) {
        assert(agent);
        agents_.push_back(agent);
    }

    //! Sets up the bots and whether they are controlled by in-built AI, human
    //! or a custom bot.
    //! @param participants A vector of player setups for each participant in
    //! the game.
    //! @sa PlayerSetup
    void SetParticipants(const vector<PlayerSetup>& participants) {
        game_settings_.player_setup.clear();
        agents_.clear();

        for ( const auto& p : participants ) {
            if ( p.agent ) {
                AddAgent(p.agent);
            }
            game_settings_.player_setup.push_back(p);
        }
    }

    void SetReplayRecovery(const bool value) {
        replay_recovery_ = value;
    }

    //! Add an instance of ReplayObserver, each ReplayObserver will run a
    //! separate StarCraft II client.
    //! @param replay_observer A pointer to the replay observer to utilize.
    //! @sa ReplayObserver
    void AddReplayObserver(ReplayObserver* replay_observer) {
        assert(replay_observer);
        replay_observers_.push_back(replay_observer);
    }

    int LaunchProcess(ProcessSettings& process_settings,
                      Client*          client,
                      int              window_width,
                      int              window_height,
                      int              window_start_x,
                      int              window_start_y,
                      int              port,
                      int              client_num = 0) {
        assert(client);
        process_settings.process_info.push_back(ProcessInfo());
        ProcessInfo& pi = process_settings.process_info.back();

        // Get the next port
        pi.port = port;

        // Command line arguments that will be passed to sc2.
        vector<string> cl = {"-listen",
                             process_settings.net_address,
                             "-port",
                             to_string(pi.port)};

        cl.push_back("-displayMode");
        if ( process_settings.full_screen && client_num == 0 )
            cl.push_back("1");
        else
            cl.push_back("0");

        if ( process_settings.data_version.size() > 0 ) {
            cl.push_back("-dataVersion");
            cl.push_back(process_settings.data_version);
        }

        for ( const string& command : process_settings.extra_command_lines )
            cl.push_back(command);

        cl.push_back("-windowwidth");
        cl.push_back(to_string(window_width));
        cl.push_back("-windowheight");
        cl.push_back(to_string(window_height));

        if ( client_num < 2 ) {
            cl.push_back("-windowx");
            cl.push_back(to_string(window_start_x + window_width * client_num));
            cl.push_back("-windowy");
            cl.push_back(to_string(window_start_y));
        } else if ( client_num < 4 ) {
            cl.push_back("-windowx");
            cl.push_back(to_string(window_start_x
                                   + window_width * (client_num - 2)));
            cl.push_back("-windowy");
            cl.push_back(to_string(window_start_y + window_height));
        }

        pi.process_path = process_settings.process_path;
        pi.process_id   = StartProcess(process_settings.process_path, cl);
        if ( !pi.process_id ) {
            cerr
                    << "Unable to start sc2 executable with path: "
                    << process_settings.process_path
                    << '\n';
        } else {
            cout
                    << "Launched SC2 ("
                    << process_settings.process_path
                    << "), PID: "
                    << to_string(pi.process_id)
                    << '\n';
        }

        client->Client::Control()->SetProcessInfo(pi);
        return pi.port;
    }

    bool ShouldRelaunch(ReplayObserver* r) {
        const ReplayInfo& replay_info = r->ReplayControl()->GetReplayInfo();

        const bool version_match
                = replay_info.base_build == r->Control()->Proto().GetBaseBuild()
               && replay_info.data_version
                          == r->Control()->Proto().GetDataVersion();
        if ( version_match ) return false;

        // Version failed to download. Just continue with trying to load in
        // current version. It will likely fail, and then just skip past this
        // replay.
        if ( !FindBaseExe(process_settings_.process_path,
                          replay_info.base_build) )
            return false;

        cout
                << "Replay is from a different version. Relaunching client "
                   "into the correct "
                   "version..."
                << '\n';
        process_settings_.data_version = replay_info.data_version;
        r->Control()->Error(ClientError::WrongGameVersion);
        return true;
    }

    bool Relaunch(ReplayObserver* replay_observer) {
        ControlInterface*  control = replay_observer->Control();
        const ProcessInfo& pi      = control->GetProcessInfo();

        // Try to kill SC2 then relaunch it
        TerminateProcess(pi.process_id);

        // NOTE (alkurbatov): Reset the control interface
        // so internal state gets reinitialized.
        replay_observer->Reset();

        // Control interface has been reconstructed.
        control = replay_observer->Control();

        last_port_ = LaunchProcess(process_settings_,
                                   replay_observer,
                                   window_width_,
                                   window_height_,
                                   window_start_x_,
                                   window_start_y_,
                                   last_port_ + 1);

        const ProcessInfo& pi_new = control->GetProcessInfo();

        return control->Connect(process_settings_.net_address,
                                pi_new.port,
                                process_settings_.timeout_ms);
    }

    bool ShouldIgnore(ReplayObserver* r, const string& file) const {
        if ( file.empty() ) return true;

        // NOTE (alkurbatov): Gather replay information with the available
        // observer. In case of any error occurred during loading of replays
        // info ignore the target replay.
        if ( !r->ReplayControl()->GatherReplayInfo(file, true) ) return true;

        // If the replay isn't being pruned based on replay info start it.
        return r->IgnoreReplay(r->ReplayControl()->GetReplayInfo(),
                               replay_settings_.player_id);
    }

    bool AttachClients(const ProcessSettings& process_settings,
                       const vector<Client*>& clients) {
        bool connected = false;

        // Since connect is blocking do it after the processes are launched.
        for ( size_t i = 0; i < clients.size(); ++i ) {
            const ProcessInfo& pi = process_settings.process_info[i];
            Client*            c  = clients[i];

            connected = c->Control()->Connect(process_settings.net_address,
                                              pi.port,
                                              process_settings.timeout_ms);
            if ( !connected )
                throw ClientConnectionError(process_settings.net_address,
                                            pi.port);
        }

        return connected;
    }

    int LaunchProcesses(ProcessSettings&       process_settings,
                        const vector<Client*>& clients,
                        int                    window_width,
                        int                    window_height,
                        int                    window_start_x,
                        int                    window_start_y) {
        int last_port   = 0;
        // Start an sc2 process for each bot.
        int clientIndex = 0;
        for ( Client* c : clients ) {
            last_port = LaunchProcess(
                    process_settings,
                    c,
                    window_width,
                    window_height,
                    window_start_x,
                    window_start_y,
                    process_settings.port_start
                            + static_cast<int>(
                                    process_settings.process_info.size())
                            - 1,
                    clientIndex++);
        }

        AttachClients(process_settings, clients);

        return last_port;
    }

    void StartReplay() {
        // If no replays given in the settings don't try.
        if ( replay_settings_.replay_file.empty() ) {
            return;
        }

        assert(!replay_observers_.empty());
        if ( !starcraft_started_ ) {
            last_port_
                    = LaunchProcesses(process_settings_,
                                      vector<Client*>(replay_observers_.begin(),
                                                      replay_observers_.end()),
                                      window_width_,
                                      window_height_,
                                      window_start_x_,
                                      window_start_y_);
        }

        // Run a replay with each available replay observer.
        for ( ReplayObserver* r : replay_observers_ ) {
            // If the replay observer is idle or out of game use it for a new
            // replay.
            if ( !r->Control()->IsReadyForCreateGame() ) {
                continue;
            }

            r->ReplayControl()->UseGeneralizedAbility(
                    use_generalized_ability_id);

            auto& replays = replay_settings_.replay_file;
            while ( replays.size() != 0 ) {
                const string& file = replay_settings_.replay_file.back();

                if ( ShouldIgnore(r, file) ) {
                    replays.pop_back();
                    continue;
                }

                if ( ShouldRelaunch(r) ) {
                    break;
                }

                const bool launched = r->ReplayControl()->LoadReplay(
                        file,
                        interface_settings_,
                        replay_settings_.player_id,
                        process_settings_.realtime);
                replays.pop_back();
                if ( launched ) break;
            }
        }

        starcraft_started_ = true;
    }

    // Start-up.

    //! Uses settings gathered from LoadSettings, specifically the path to the
    //! executable, to run StarCraft II.
    void LaunchStarcraft() const {
        if ( !DoesFileExist(process_settings_.process_path) ) {
            cerr
                    << "Executable path can't be found, try running the "
                       "StarCraft II executable "
                       "first."
                    << '\n';
            if ( !process_settings_.process_path.empty() ) {
                cerr
                        << process_settings_.process_path
                        << " does not exist on your filesystem.";
            }
            cerr << '\n';
            assert(!"Could not find the executable. Supply a valid path.");
            exit(1);
        }

        assert(!agents_.empty());

        // TODO: Check the case that a pid in the process_info_ struct is no
        // longer running. The process may have died.
        int port_start = 0;
        if ( process_settings_.process_info.size() != agents_.size() ) {
            port_start = LaunchProcesses(
                    process_settings_,
                    vector<Client*>(agents_.begin(), agents_.end()),
                    window_width_,
                    window_height_,
                    window_start_x_,
                    window_start_y_);
        }

        SetupPorts(agents_.size(), port_start);

        starcraft_started_ = true;
        last_port_         = port_start;
    }

    //! Attaches to a running Starcraft.
    void Connect(int port) const {
        if ( !agents_.front()->Control()->Connect(
                     process_settings_.net_address,
                     port,
                     process_settings_.timeout_ms) ) {
            cerr << "Failed to attach to starcraft." << '\n';
            exit(1);
        }

        // Assume starcraft has started after successfully attaching to a
        // server.
        starcraft_started_ = true;
    }

    //! Starts a game on a certain map. There are multiple ways to specify a
    //! map: Absolute path: Any .SC2Map file. Relative path: Any .SC2Map file
    //! relative to either the library or installation maps folder. Map name:
    //! Any BattleNet published map that has been locally cached.
    //! @param map_path Path to the map to run.
    //! @return True if the game started, false if there was errors or the game
    //! didn't start, override OnError callback to see the exact errors.
    bool StartGame(const string& map_path) {
        if ( !map_path.empty() ) game_settings_.map_name = map_path;

        // bool CoordinatorImpl::StartGame() const
        // return StartGame();

        assert(starcraft_started_);
        if ( const bool is_game_created = CreateGame(); !is_game_created ) {
            cerr << "Failed to create game." << '\n';
            exit(1);
        }
        return JoinGame();
    }

    //! Creates a game but does not join the agents to the game
    //! @param map_path Path to the map to run.
    //! @return true if the game was successfully created
    bool CreateGame(const string& map_path) {
        if ( !map_path.empty() ) game_settings_.map_name = map_path;

        // bool CoordinatorImpl::CreateGame() const
        //		return CreateGame();

        // Create the game with the first client.
        Agent* firstClient = agents_.front();
        return firstClient->Control()->CreateGame(game_settings_.map_name,
                                                  game_settings_.player_setup,
                                                  process_settings_.realtime);
    }

    //! Joins agents to the game
    //! Returns true if the agents were successfully connected to the game
    bool JoinGame() const {
        int i = 0;
        for ( Agent* c : agents_ ) {
            const bool game_join_request = c->Control()->RequestJoinGame(
                    game_settings_.player_setup[i++],
                    interface_settings_,
                    game_settings_.ports,
                    game_settings_.raw_affects_selection);

            if ( !game_join_request ) {
                cerr << "Unable to join game." << '\n';
                exit(1);
            }
        }

        for ( Agent* c : agents_ ) {
            c->Control()->WaitJoinGame();
        }

        // Check if any errors occurred during game start.
        bool errors_occurred = false;
        for ( Agent* c : agents_ ) {
            const ControlInterface* control = c->Control();
            if ( const vector<ClientError>& client_errors
                 = control->GetClientErrors();
                 !client_errors.empty() ) {
                c->OnError(client_errors, control->GetProtocolErrors());
                errors_occurred = true;
            }

            c->Control()->UseGeneralizedAbility(use_generalized_ability_id);
        }

        if ( errors_occurred ) {
            return false;
        }

        // Run all clients on game start.
        for ( Agent* c : agents_ ) {
            c->Control()->GetObservation();
        }
        for ( Agent* c : agents_ ) {
            c->OnGameFullStart();
        }
        for ( Agent* c : agents_ ) {
            c->Control()->OnGameStart();
            c->OnGameStart();
        }
        for ( Agent* c : agents_ ) {
            c->Control()->IssueEvents(c->Actions()->Commands());
        }

        return true;
    }

    //! Sets up the sc2 game ports to use
    //! @param num_agents Number of agents in the game
    //! @param port_start Starting port number
    //! @param check_single  Checks if the game is a single player or
    //! multiplayer game
    void SetupPorts(size_t num_agents,
                    int    port_start,
                    bool   check_single) {
        // Join the game if there are two human participants.
        size_t humans = 0;
        if ( check_single ) {
            for ( const auto& p_setup : game_settings_.player_setup ) {
                if ( p_setup.type == Participant ) {
                    ++humans;
                }
            }
        } else {
            humans = num_agents;
        }
        if ( humans > 1 ) {
            game_settings_.ports.shared_port            = ++port_start;
            game_settings_.ports.server_ports.game_port = ++port_start;
            game_settings_.ports.server_ports.base_port = ++port_start;
            for ( size_t i = 1; i < num_agents; ++i ) {
                PortSet port_set;
                port_set.game_port = ++port_start;
                port_set.base_port = ++port_start;
                game_settings_.ports.client_ports.push_back(port_set);
            }
        }
    }

    // Run.
    static void CallOnStep(Agent* agent) {
        ControlInterface* control = agent->Control();
        if ( !control->IsInGame() ) {
            agent->OnGameEnd();
            control->RequestLeaveGame(); // Only for multiplayer.
            return;
        }

        ActionInterface* action = agent->Actions();
        control->IssueEvents(action->Commands());
        if ( action ) {
            action->SendActions();
        }

        if ( ActionFeatureLayerInterface* action_feature_layer
             = agent->ActionsFeatureLayer() ) {
            action_feature_layer->SendActions();
        }
    }

    void RunParallel(const function<void(Agent* agent)>& step,
                     const vector<Agent*>&               agents) {
        // Run all steps in parallel.
        vector<thread> threads(agents.size());
        for ( size_t i = 0; i < agents.size(); ++i ) {
            Agent* agent = agents[i];
            threads[i]   = thread(bind(step, agent));
        }

        for ( auto& t : threads ) {
            t.join();
        }
    }

    void StepAgents() const {
        auto step_agent = [this](Agent* agent) {
            ControlInterface* control = agent->Control();

            if ( control->GetAppState() != AppState::normal ) {
                return;
            }

            if ( control->PollLeaveGame() ) {
                return;
            }

            if ( control->IsFinishedGame() ) {
                return;
            }

            control->Step(process_settings_.step_size);
            control->WaitStep();
            if ( process_settings_.multi_threaded ) {
                CallOnStep(agent);
            }
        };

        if ( agents_.size() == 1 ) {
            step_agent(agents_.front());
        } else {
            RunParallel(step_agent, agents_);
        }

        if ( !process_settings_.multi_threaded ) {
            for ( Agent* agent : agents_ ) {
                if ( agent->Control()->GetAppState() != AppState::normal ) {
                    continue;
                }

                // It is possible to have a pending leave game request here.
                if ( agent->Control()->PollLeaveGame() ) {
                    continue;
                }

                CallOnStep(agent);
            }
        }
    }

    void StepAgentsRealtime() const {
        auto step_agent = [](Agent* agent) {
            ControlInterface* control = agent->Control();
            if ( !control ) {
                return;
            }

            if ( control->GetAppState() != AppState::normal ) {
                return;
            }

            if ( control->PollLeaveGame() ) {
                return;
            }

            if ( agent->Control()->IsFinishedGame() ) {
                return;
            }

            ActionInterface* action = agent->Actions();
            if ( !action ) {
                return;
            }

            // This agent shouldn't call step since it's real time.
            control->GetObservation();
            control->IssueEvents(agent->Actions()->Commands());
            action->SendActions();

            if ( !control->IsInGame() ) {
                agent->OnGameEnd();
                agent->Control()->RequestLeaveGame(); // Only for multiplayer.
            }
        };

        if ( process_settings_.multi_threaded ) {
            RunParallel(step_agent, agents_);
        } else {
            for ( Agent* agent : agents_ ) {
                step_agent(agent);
            }
        }
    }

    void StepReplayObservers() const {
        // Run all replay observers.
        auto run_replay = [this](ReplayObserver* r) {
            if ( r->Control()->GetAppState() != AppState::normal ) {
                return;
            }

            // If the replay is loading wait for it to finish loading before
            // performing a step.
            if ( r->Control()->HasResponsePending() ) {
                // Don't consume a response if there isn't one in the queue.
                if ( replay_observers_.size() > 1
                     && !r->Control()->PollResponse() ) {
                    return;
                }
                r->ReplayControl()->WaitForReplay();
            }

            if ( r->Control()->IsInGame() ) {
                r->Control()->Step(process_settings_.step_size);
                r->Control()->WaitStep();

                // If multithreaded run everyone's OnStep in parallel.
                if ( process_settings_.multi_threaded ) {
                    r->Control()->IssueEvents();
                    r->ObserverAction()->SendActions();
                }

                if ( !r->Control()->IsInGame() ) {
                    r->OnGameEnd();
                }
            }
        };

        if ( replay_observers_.size() == 1 ) {
            run_replay(replay_observers_.front());
        } else {
            // Run all steps in parallel.
            vector<thread> threads;
            threads.reserve(replay_observers_.size());
            for ( auto r : replay_observers_ ) {
                threads.emplace_back(run_replay, r);
            }

            // Join all threads.
            for ( auto& t : threads ) {
                t.join();
            }
        }

        // Do everyone's OnStep, if not multi threaded, in single threaded mode.
        if ( !process_settings_.multi_threaded ) {
            for ( ReplayObserver* r : replay_observers_ ) {
                if ( r->Control()->GetAppState() != AppState::normal ) {
                    continue;
                }

                r->Control()->IssueEvents();
                r->ObserverAction()->SendActions();
            }
        }
    }

    void StepReplayObserversRealtime() const {
        // Run all replay observers.
        auto run_replay = [this](ReplayObserver* r) {
            if ( r->Control()->GetAppState() != AppState::normal ) {
                return;
            }

            // If the replay is loading wait for it to finish loading before
            // performing a step.
            if ( r->Control()->HasResponsePending() ) {
                // Don't consume a response if there isn't one in the queue.
                if ( replay_observers_.size() > 1
                     && !r->Control()->PollResponse() ) {
                    return;
                }
                r->ReplayControl()->WaitForReplay();
            }

            if ( r->Control()->IsInGame() ) {
                r->Control()->GetObservation();

                // If multithreaded run everyone's OnStep in parallel.
                if ( process_settings_.multi_threaded ) {
                    r->Control()->IssueEvents();
                }

                if ( !r->Control()->IsInGame() ) {
                    r->OnGameEnd();
                }
            }
        };

        if ( replay_observers_.size() == 1 ) {
            run_replay(replay_observers_.front());
        } else {
            // Run all steps in parallel.
            vector<thread> threads;
            threads.reserve(replay_observers_.size());
            for ( auto r : replay_observers_ ) {
                threads.emplace_back(run_replay, r);
            }

            // Join all threads.
            for ( auto& t : threads ) {
                t.join();
            }
        }

        // Do everyone's OnStep, if not multi threaded, in single threaded mode.
        if ( !process_settings_.multi_threaded ) {
            for ( ReplayObserver* r : replay_observers_ ) {
                if ( r->Control()->GetAppState() != AppState::normal ) {
                    continue;
                }

                r->Control()->IssueEvents();
            }
        }
    }

    bool AnyObserverAvailable() const {
        return any_of(replay_observers_.cbegin(),
                      replay_observers_.cend(),
                      [](ReplayObserver* r) {
            return !r->Control()->IsInGame();
        });
    }

    //! Helper function used to actually run a bot. This function will behave
    //! differently in real-time compared to non real-time.
    //!  In real-time there is no step sent over the wire but instead will
    //!  request and read observations as the game runs.
    //! * For non-real time Update will perform the following:
    //!     1. Step the simulation forward by a certain amount of game steps,
    //!     this essentially moves the game loops forward.
    //!     2. Wait for the step to complete, the step is completed when a
    //!     response is received and read from the StarCraft II binary.
    //!         * When the step is completed an Observation has been received.
    //!         It is parsed and various client events are dispatched.
    //!     3. Call the user's OnStep function.
    //! * Real time applications will perform the following:
    //!     1. The Observation is directly requested. The process will block
    //!     while waiting for it.
    //!     2. The Observation is parsed and client events are dispatched.
    //!     3. Unit actions batched from the ActionInterface are dispatched.
    //! @return False if the game has ended, true otherwise.
    bool Update() const {
        if ( agents_.size() > 0 ) {
            if ( process_settings_.realtime ) {
                StepAgentsRealtime();
            } else {
                StepAgents();
            }
        }

        if ( replay_observers_.size() > 0 && starcraft_started_ ) {
            if ( process_settings_.realtime ) {
                StepReplayObserversRealtime();
            } else {
                StepReplayObservers();
            }
        }

        if ( replay_observers_.size() > 0 ) {
            if ( AnyObserverAvailable() ) {
                StartReplay();
            }
        }

        // Check for errors in all agents/replay observers at the end of an
        // update.
        bool error_occurred = false;
        for ( Agent* agent : agents_ ) {
            const ControlInterface* control = agent->Control();
            if ( const vector<ClientError>& client_errors
                 = control->GetClientErrors();
                 !client_errors.empty() ) {
                agent->OnError(client_errors, control->GetProtocolErrors());
                error_occurred = true;
            }
        }

        bool relaunched = false;
        for ( ReplayObserver* replay_observer : replay_observers_ ) {
            const ControlInterface* control = replay_observer->Control();
            if ( const vector<ClientError>& client_errors
                 = control->GetClientErrors();
                 !client_errors.empty() ) {
                replay_observer->OnError(client_errors,
                                         control->GetProtocolErrors());
                error_occurred = true;
                if ( replay_recovery_ ) {
                    // An error did occur but if we successfully recovered
                    // ignore it. The client will still gets its event
                    if ( Relaunch(replay_observer) ) {
                        error_occurred = false;
                        relaunched     = true;
                    }
                }
            }
        }

        // End the CCoordinator update on the idea that an error in the API
        // should mean it's time to stop.
        if ( error_occurred ) {
            return false;
        }

        return !AllGamesEnded() || relaunched;
    }

    //! Requests for the currently running game to end.
    void LeaveGame() const {
        for ( Agent* c : agents_ ) {
            c->Control()->RequestLeaveGame();
        }
    }

    // Status.

    //! Returns true if all running games have ended.
    bool AllGamesEnded() const {
        for ( Agent* agent : agents_ ) {
            if ( agent->Control()->IsInGame()
                 || agent->Control()->HasResponsePending() ) {
                return false;
            }
        }

        for ( ReplayObserver* r : replay_observers_ ) {
            if ( r->Control()->IsInGame()
                 || r->Control()->HasResponsePending() ) {
                return false;
            }
        }

        return true;
    }

    // Replay specific.
    //! Sets the path for to a folder of replays to analyze.
    //! @param path The folder path.
    bool SetReplayPath(const string& path) const {
        replay_settings_.replay_file.clear();

        if ( HasExtension(path, ".SC2Replay") ) {
            replay_settings_.replay_file.push_back(path);
        } else {
            replay_settings_.replay_dir = path;

            // Gather and append all files from the directory.
            if ( !replay_settings_.replay_dir.empty() ) {
                scan_directory(replay_settings_.replay_dir.c_str(),
                               replay_settings_.replay_file,
                               true,
                               false);
            }
        }

        return !replay_settings_.replay_file.empty();
    }

    //! Loads replays from a file.
    //! @param path The file path.
    bool LoadReplayList(const string& path) const {
        if ( !DoesFileExist(path) ) return false;

        replay_settings_.replay_file.clear();

        ifstream replay_file(path);

        string line;
        while ( getline(replay_file, line) ) {
            if ( line.length() < 5 ) continue;

            replay_settings_.replay_file.push_back(line);
        }

        return true;
    }

    //! Saves replays to a file.
    //! @param path The file path.
    void SaveReplayList(const string& path) const {
        ofstream replay_file(path, ofstream::out | ofstream::trunc);
        for ( const string& line : replay_settings_.replay_file ) {
            replay_file << line << '\n';
        }
    }

    //! Determines if there are unprocessed replays.
    //! @return Is true if there are replays left.
    bool HasReplays() const {
        return !replay_settings_.replay_file.empty();
    }

    // Misc.

    //! Blocks for all bots to receive any pending responses
    bool WaitForAllResponses() const {
        static constexpr int sleep_ms = 50;

        int total_sleep_ms = 0;
        for ( ;; ) {
            bool has_responses = false;

            for ( Agent* agent : agents_ ) {
                if ( !agent->Control()->HasResponsePending()
                     || agent->Control()->GetAppState() != AppState::normal ) {
                    continue;
                }

                has_responses = true;

                if ( agent->Control()->PollResponse() ) {
                    agent->Control()->ConsumeResponse();
                }

                break;
            }

            for ( ReplayObserver* replay_observer : replay_observers_ ) {
                if ( has_responses ) {
                    break;
                }

                if ( !replay_observer->Control()->HasResponsePending()
                     || replay_observer->Control()->GetAppState()
                                != AppState::normal ) {
                    continue;
                }
                has_responses = true;

                if ( replay_observer->Control()->PollResponse() ) {
                    replay_observer->Control()->ConsumeResponse();
                }

                break;
            }

            if ( !has_responses ) {
                break;
            }

            if ( total_sleep_ms >= process_settings_.timeout_ms ) {
                assert(0);
                return false;
            }

            SleepFor(sleep_ms);
            total_sleep_ms += sleep_ms;
        }
        return true;
    }

    //! Saves a binary blob as a map to a remote location.
    //! @param data The map data.
    //! @param data_size The size of map data.
    //! @param remote_path The file path to save the data to.
    //! @return Is true if the save is successful.
    bool RemoteSaveMap(const void*   data,
                       int           data_size,
                       const string& remote_path) const {
        for ( Agent* c : agents_ ) {
            if ( !c->Control()->RemoteSaveMap(data, data_size, remote_path) )
                return false;
        }

        for ( ReplayObserver* c : replay_observers_ ) {
            if ( !c->Control()->RemoteSaveMap(data, data_size, remote_path) )
                return false;
        }

        return true;
    }

    //! Gets the game executable path.
    //! @return The game executable path.
    string GetExePath() const {
        if ( process_settings_.process_path.length() > 4 )
            return process_settings_.process_path;

        return process_settings_.process_path;
    }
};

} // namespace sc2
