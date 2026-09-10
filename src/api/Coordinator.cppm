module;
#include <algorithm>
#include <cassert>
#include <functional>
#include <iostream>
#include <string>
#include <thread>

#include "utils/manage_process.h"
export module Coordinator;
import Agent;
import Client;


import ReplayObserver;
import action_interface;
import action_feature_layer_interface;
import args;
import enum_db;
import error_handler;
import game_settings;
import game_types;
import protocol_interface;
import scan_directory;

export namespace sc2 {
using namespace std;

PlayerSetup CreateParticipant ( const string &player_name, const Race race ) {
    return PlayerSetup ( Participant, player_name, race );
}

PlayerSetup CreateComputer (
    const Race       race          = Random,
    const Difficulty difficulty    = Easy,
    const AIBuild    ai_build      = RandomBuild,
    const string    &computer_name = ""
) {
    // Generates computer's name based on settings if no name is passed.
    if ( string final_name = computer_name; final_name.empty( ) ) {
        ostringstream name_stream;
        name_stream << "Computer-" << RaceToString ( race ) << "-"
                    << DifficultyToString ( difficulty ) << "-"
                    << AIBuildToString ( ai_build );
        final_name = name_stream.str( );
    }
    return { Computer, computer_name, race, difficulty, ai_build };
}

/*! @brief Frontend for running a game.
 *
 * The Coordinator acts as a game and bot manager. It is used to launch
 * StarCraft II and setup protocol connections between a user's bot and the
 * running StarCraft II instance. With it a user steps forward a simulation and
 * it will fill out bot interface data.
 *
 * @note Only called in main. */

/*! Coordinator of one or more clients. Used to start, step and stop games and
 * replays. */
class Coordinator {
public:
    vector<Agent *>          agents_;
    vector<ReplayObserver *> replay_observers_;

    bool game_ended_ { };
    bool starcraft_started_ { };

    GameSettings      game_settings_;
    ReplaySettings    replay_settings_;
    InterfaceSettings interface_settings_;
    ProcessSettings   process_settings_;

    int window_width_  = 1'024;
    int window_height_ = 768;

    int window_start_x_ = 100;
    int window_start_y_ = 200;

    // If a ReplayObserver fails, try to recover
    bool replay_recovery_ = true;
    int  last_port_       = 0;

    bool use_generalized_ability_id = true;

    Coordinator ( )
        : process_settings_ (
              false,
              1,
              "",
              "127.0.0.1",
              kDefaultProtoInterfaceTimeout,
              8'168,
              false
          ) { }

    ~Coordinator ( ) {
        for ( const ProcessInfo &p : process_settings_.process_info ) {
            TerminateProcess ( p.process_id );
        }
    }

    // Initialization and setup.

    /*! @brief Used to load settings. Settings will be discovered in the
     * following order:
     *    1. If command line arguments are provided it will use them. Invoke
     * binary with --help to see expected arguments.
     *    2. (Recommended) If the StarCraft II binary has been run the function
     * will auto discover its location.
     * @param args Provided in main signature. Conversion from `int argc, char*
     * argv[]` required.
     * @return True if settings were found or discovered. */
    bool LoadSettings (const span<char *> args ) {
        return ParseSettings ( args, process_settings_, game_settings_ );
    }

    /*! @brief Specifies whether bots or replays OnStep function should be run
     * in parallel. If set to true make sure your bots are thread-safe if they
     * reach into shared code.
     * @param value True to multithread, false otherwise. */
    void SetMultithreaded (const bool value ) {
        process_settings_.multi_threaded = value;
    }

    /*! @brief Specifies whether the game should run in realtime or not. If the
     * game is running in real time that means the CCoordinator is not stepping
     * it forward. The game is running and your bot reaches into it
     * asynchronously to read state.
     * @param value True to be realtime, false otherwise. */
    void SetRealtime (const bool value ) {
        // Realtime must be set before LaunchStarcraft is called.
        assert ( !starcraft_started_ );
        process_settings_.realtime = value;
    }

    /*! @brief Sets the number of game loops to run for each step.
     * @param step_size Number of gameloops to run for each step. */
    void SetStepSize (const int step_size ) {
        if ( step_size < 1 ) {
            assert ( 0 );
            return;
        }

        // SetStepSize must be set before LaunchStarcraft is called.
        assert ( !starcraft_started_ );
        process_settings_.step_size = step_size;
    }

    /*! @brief Sets the path to the StarCraft II binary.
     * @param path Absolute file path. */
    void SetProcessPath ( const string &path ) {
        assert ( !starcraft_started_ );
        process_settings_.process_path = path;
    }

    /*! @brief Set the correct data version of a replay to allow faster replay
     * loading. Saves a few seconds if replay is not up to date. Works only in
     * combination with correct process path set by "SetProcessPath".
     * @param version Look in "protocol/buildinfo/versions.json" for the
     * property "data-hash". Or read it from "ReplayInfo.data_version". */
    [[maybe_unused]]
    void SetDataVersion ( const string &version ) {
        assert ( !starcraft_started_ );
        process_settings_.data_version = version;
    }

    /*! @brief Sets the timeout for network operations.
     * @param timeout_ms in milliseconds. */
    void SetTimeoutMS (const uint32_t timeout_ms ) {
        process_settings_.timeout_ms = timeout_ms;
    }

    /*! @brief Sets the first port number to use. Subsequent port assignments
     * are sequential.
     * @param port_start First port number. */
    void SetPortStart (const int port_start ) {
        assert ( !starcraft_started_ );
        process_settings_.port_start = port_start;
    }

    /*! @brief Indicates whether feature layers should be provided in the
     * observation.
     * @param settings Configuration of feature layer settings.
     * @see FeatureLayerSettings */
    void SetFeatureLayers ( const FeatureLayerSettings &settings ) {
        // Feature Layers must be set before LaunchStarcraft is called.
        assert ( !starcraft_started_ );
        interface_settings_.use_feature_layers     = true;
        interface_settings_.feature_layer_settings = settings;
    }

    //! @see RenderSettings
    void SetRender ( const RenderSettings &settings ) {
        // Render must be set before LaunchStarcraft is called.
        assert ( !starcraft_started_ );
        interface_settings_.use_render      = true;
        interface_settings_.render_settings = settings;
    }

    /*! @brief Sets the game window dimensions.
     * @param width Width of game window.
     * @param height Height of game window. */
    void SetWindowSize (const int width, const int height ) {
        assert ( !starcraft_started_ );
        window_width_  = width;
        window_height_ = height;
    }

    /*! @brief Sets the game window location.
     * @param x X position of game window.
     * @param y y position of game window. */
    void SetWindowLocation ( const int x, const int y ) {
        assert ( !starcraft_started_ );
        window_start_x_ = x;
        window_start_y_ = y;
    }

    /*! @brief Uses generalized abilities where possible.
     * @example BUILD_TECHLAB_BARRACKS, BUILD_TECHLAB_FACTORY,
     * BUILD_TECHLAB_STARPORT ability ids are generalized to BUILD_TECHLAB
     * ability id in the observation. */
    // TODO Why is this here?
    void SetUseGeneralizedAbilityId ( const bool value ) {
        assert ( !starcraft_started_ );
        use_generalized_ability_id = value;
    }

    //! Sets the replay perspective. Use 0 to observe all players.
    void SetReplayPerspective ( const int player_id ) {
        replay_settings_.player_id = player_id;
    }

    /*! @brief Appends a command line argument to be fed to StarCraft II when
     * starting.
     * @param option The string to be appended to the executable invoke. */
    void AddCommandLine ( const string &option ) {
        process_settings_.extra_command_lines.push_back ( option );
    }

    /*! @brief When set to true, less actions will be generated because the game
     * will not try to keep your unit selection. Useful to reduce the number of
     * actions, but may complicate the debugging process. */
    void SetRawAffectsSelection ( const bool value ) {
        game_settings_.raw_affects_selection = value;
    }

    /*! @brief Specifies whether the game should run in fullscreen or not.
     * This usually indicates that a real player (the first registered
     * participant) is using the first launched instance to play (the first
     * registered participant). The game will be launched in the windowed mode
     * for the second player (second participant). It should be used in
     * combination with SetRealtime(true), otherwise the game has no sound. */
    void SetFullScreen ( const bool value ) {
        process_settings_.full_screen = value;
    }

    void AddAgent ( Agent *agent ) {
        assert ( agent );
        agents_.push_back ( agent );
        if ( agents_.back( ) == agent )
            SRC_LocationOut ( "Agent added." );
    }

    /*! @brief Sets up the bots and whether they are controlled by in-built AI,
     * human or a custom bot.
     * @param participants A vector of player setups for each participant in the
     * game.
     * @see PlayerSetup */
    void SetParticipants (
        const unordered_map<Agent *, PlayerSetup> &participants
    ) {
        game_settings_.player_setup.clear( );
        agents_.clear( );
        SRC_LocationOut ( "GameSettings and Agents cleared." );

        for ( const auto [agent, player_setup] : participants ) {
            if ( agent != nullptr ) {
                AddAgent ( agent );
            }
            game_settings_.player_setup.push_back ( player_setup );
        }
    }

    void SetReplayRecovery ( const bool value ) {
        replay_recovery_ = value;
    }

    //! @brief Add an instance of ReplayObserver, each ReplayObserver will run a
    //! separate StarCraft II client.
    //! @param replay_observer A pointer to the replay observer to utilize.
    //! @see ReplayObserver
    void AddReplayObserver ( ReplayObserver *replay_observer ) {
        assert ( replay_observer );
        replay_observers_.push_back ( replay_observer );
    }

    static int LaunchProcess (
        ProcessSettings &process_settings,
        Client          *client,
        const int        window_width,
        const int        window_height,
        const int        window_start_x,
        const int        window_start_y,
        const int        port,
        const int        client_num = 0
    ) {
        assert ( client );
        process_settings.process_info.push_back ( ProcessInfo( ) );
        ProcessInfo &pi = process_settings.process_info.back( );

        // Get the next port
        pi.port = port;

        // Command line arguments that will be passed to sc2.
        vector<string> cl = { "-listen",
                              process_settings.net_address,
                              "-port",
                              to_string ( pi.port ) };

        cl.push_back ( "-displayMode" );
        if ( process_settings.full_screen && client_num == 0 )
            cl.push_back ( "1" );
        else
            cl.push_back ( "0" );

        if ( process_settings.data_version.size( ) > 0 ) {
            cl.push_back ( "-dataVersion" );
            cl.push_back ( process_settings.data_version );
        }

        for ( const string &command : process_settings.extra_command_lines )
            cl.push_back ( command );

        cl.push_back ( "-windowwidth" );
        cl.push_back ( to_string ( window_width ) );
        cl.push_back ( "-windowheight" );
        cl.push_back ( to_string ( window_height ) );

        if ( client_num < 2 ) {
            cl.push_back ( "-windowx" );
            cl.push_back (
                to_string ( window_start_x + window_width * client_num )
            );
            cl.push_back ( "-windowy" );
            cl.push_back ( to_string ( window_start_y ) );
        } else if ( client_num < 4 ) {
            cl.push_back ( "-windowx" );
            cl.push_back (
                to_string ( window_start_x + window_width * ( client_num - 2 ) )
            );
            cl.push_back ( "-windowy" );
            cl.push_back ( to_string ( window_start_y + window_height ) );
        }

        pi.process_path = process_settings.process_path;
        pi.process_id   = StartProcess ( process_settings.process_path, cl );
        if ( !pi.process_id ) {
            cerr << "Unable to start sc2 executable with path: "
                 << process_settings.process_path << '\n';
        } else {
            cout << "Launched SC2 (" << process_settings.process_path
                 << "), PID: " << to_string ( pi.process_id ) << '\n';
        }

        client->Client::SetProcessInfo ( pi );
        return pi.port;
    }

    bool ShouldRelaunch ( const ReplayObserver *replay_observer ) {
        const ReplayInfo &replay_info = replay_observer->GetReplayInfo( );

        const bool version_match =
            replay_info.base_build == ProtoFace::base_build_ &&
            replay_info.data_version == ProtoFace::data_version_;
        if ( version_match )
            return false;

        // Version failed to download. Just continue with trying to load in
        // current version. It will likely fail, and then just skip past this
        // replay.
        if ( !FindBaseExe (
                 process_settings_.process_path,
                 replay_info.base_build
             ) )
            return false;

        cout << "Replay is from a different version. Relaunching client "
                "into the correct "
                "version..."
             << '\n';
        process_settings_.data_version = replay_info.data_version;
        Error::Log ( ClientError::WrongGameVersion );
        return true;
    }

    bool Relaunch ( ReplayObserver *replay_observer ) {
        const ProcessInfo &pi = replay_observer->GetProcessInfo( );

        // Try to kill SC2 then relaunch it
        TerminateProcess ( pi.process_id );

        // NOTE (alkurbatov): Reset the control interface
        // so internal state gets reinitialized.
        replay_observer->Reset( );

        last_port_ = LaunchProcess (
            process_settings_,
            replay_observer,
            window_width_,
            window_height_,
            window_start_x_,
            window_start_y_,
            last_port_ + 1
        );

        const ProcessInfo &pi_new = replay_observer->GetProcessInfo( );

        return replay_observer->Connect (
            process_settings_.net_address,
            pi_new.port,
            process_settings_.timeout_ms
        );
    }

    bool ShouldIgnore (
        ReplayObserver *replay_observer,
        const string   &file
    ) const {
        if ( file.empty( ) )
            return true;

        // NOTE (alkurbatov): Gather replay information with the available
        // observer. In case of any error occurred during loading of replays
        // info ignore the target replay.
        if ( !replay_observer->GatherReplayInfo ( file, true ) )
            return true;

        // If the replay isn't being pruned based on replay info start it.
        return replay_observer->IgnoreReplay (
            replay_observer->GetReplayInfo( ),
            replay_settings_.player_id
        );
    }

    static bool AttachClients (
        const ProcessSettings  &process_settings,
        const vector<Client *> &clients
    ) {
        bool connected = false;

        // Since connect is blocking do it after the processes are launched.
        for ( size_t i = 0; i < clients.size( ); ++i ) {
            const ProcessInfo &pi     = process_settings.process_info[i];
            Client            *client = clients[i];

            connected = client->Connect (
                process_settings.net_address,
                pi.port,
                process_settings.timeout_ms
            );
            if ( !connected )
                throw ClientConnectionError (
                    process_settings.net_address,
                    pi.port
                );
        }

        return connected;
    }

    static int LaunchProcesses (
        ProcessSettings        &process_settings,
        const vector<Client *> &clients,
        const int               window_width,
        const int               window_height,
        const int               window_start_x,
        const int               window_start_y
    ) {
        int last_port   = 0;
        // Start an sc2 process for each bot.
        int clientIndex = 0;
        for ( Client *c : clients ) {
            last_port = LaunchProcess (
                process_settings,
                c,
                window_width,
                window_height,
                window_start_x,
                window_start_y,
                process_settings.port_start +
                    static_cast<int> ( process_settings.process_info.size( ) ) -
                    1,
                clientIndex++
            );
        }

        AttachClients ( process_settings, clients );

        return last_port;
    }

    void StartReplay ( ) {
        // If no replays given in the settings don't try.
        if ( replay_settings_.replay_file.empty( ) ) {
            return;
        }

        assert ( !replay_observers_.empty( ) );
        if ( !starcraft_started_ ) {
            last_port_ = LaunchProcesses (
                process_settings_,
                vector<Client *> (
                    replay_observers_.begin( ),
                    replay_observers_.end( )
                ),
                window_width_,
                window_height_,
                window_start_x_,
                window_start_y_
            );
        }

        // Run a replay with each available replay observer.
        for ( ReplayObserver *replay_observer : replay_observers_ ) {
            // If the replay observer is idle or out of game use it for a new
            // replay.
            if ( !replay_observer->IsReadyForCreateGame( ) ) {
                continue;
            }

            replay_observer->UseGeneralizedAbility (
                use_generalized_ability_id
            );

            auto &replays = replay_settings_.replay_file;
            while ( replays.size( ) != 0 ) {
                const string &file = replay_settings_.replay_file.back( );

                if ( ShouldIgnore ( replay_observer, file ) ) {
                    replays.pop_back( );
                    continue;
                }

                if ( ShouldRelaunch ( replay_observer ) ) {
                    break;
                }

                const bool launched = replay_observer->LoadReplay (
                    file,
                    interface_settings_,
                    replay_settings_.player_id,
                    process_settings_.realtime
                );
                replays.pop_back( );
                if ( launched )
                    break;
            }
        }

        starcraft_started_ = true;
    }

    // Start-up.

    //! Uses settings gathered from LoadSettings, specifically the path to the
    //! executable, to run StarCraft II.
    void LaunchStarcraft ( ) {
        if ( !DoesFileExist ( process_settings_.process_path ) ) {
            cerr << "Executable path can't be found, try running the "
                    "StarCraft II executable "
                    "first."
                 << '\n';
            if ( !process_settings_.process_path.empty( ) ) {
                cerr << process_settings_.process_path
                     << " does not exist on your filesystem.";
            }
            cerr << '\n';
            assert ( !"Could not find the executable. Supply a valid path." );
            exit ( 1 );
        }

        assert ( !agents_.empty( ) );

        // TODO: Check the case that a pid in the process_info_ struct is no
        // longer running. The process may have died.
        int port_start = 0;
        if ( process_settings_.process_info.size( ) != agents_.size( ) ) {
            port_start = LaunchProcesses (
                process_settings_,
                vector<Client *> ( agents_.begin( ), agents_.end( ) ),
                window_width_,
                window_height_,
                window_start_x_,
                window_start_y_
            );
        }

        SetupPorts ( agents_.size( ), port_start );

        starcraft_started_ = true;
        last_port_         = port_start;
    }

    //! Attaches to a running StarCraft II.
    void Connect ( const int port ) {
        if ( !agents_.front( )->Connect (
                 process_settings_.net_address,
                 port,
                 process_settings_.timeout_ms
             ) )
        {
            cerr << "Failed to attach to starcraft." << '\n';
            exit ( 1 );
        }

        // Assume StarCraft II has started after successfully attaching to a
        // server.
        starcraft_started_ = true;
    }

    /*! @brief Starts a game on a certain map. There are multiple ways to
     * specify a map: Absolute path: Any .SC2Map file. Relative path: Any
     * .SC2Map file relative to either the library or installation maps folder.
     * Map name: Any BattleNet published map that has been locally cached.
     * @param map_path Path to the map to run.
     * @return True if the game started, false if there was errors or the game
     * didn't start, override OnError callback to see the exact errors. */
    bool StartGame ( const string &map_path ) {
        if ( !map_path.empty( ) )
            game_settings_.map_name = map_path;

        // bool CoordinatorImpl::StartGame() const
        // return StartGame();

        assert ( starcraft_started_ );
        if ( const bool is_game_created = CreateGame ( map_path );
             !is_game_created )
        {
            cerr << "Failed to create game." << '\n';
            exit ( 1 );
        }
        return JoinGame( );
    }

    /*! @brief Creates a game but does not join the agents to the game
     * @param map_path Path to the map to run.
     * @return true if the game was successfully created */
    bool CreateGame ( const string &map_path ) {
        if ( !map_path.empty( ) )
            game_settings_.map_name = map_path;

        // bool CoordinatorImpl::CreateGame() const
        //		return CreateGame();

        // Create the game with the first client.
        Agent *firstClient = agents_.front( );
        return firstClient->CreateGame (
            game_settings_.map_name,
            game_settings_.player_setup,
            process_settings_.realtime
        );
    }

    /*! @brief Joins agents to the game.
     * @returns true if the agents were successfully connected to the game. */
    bool JoinGame ( ) const {
        int i = 0;
        for ( Agent *agent : agents_ ) {
            const bool game_join_request = agent->RequestJoinGame (
                game_settings_.player_setup[i++],
                interface_settings_,
                game_settings_.ports,
                game_settings_.raw_affects_selection
            );

            if ( !game_join_request ) {
                cerr << "Unable to join game." << '\n';
                exit ( 1 );
            }
        }

        for ( Agent *agent : agents_ ) {
            agent->WaitJoinGame( );
        }

        // Check if any errors occurred during game start.
        bool errors_occurred = false;
        for ( const Agent *agent : agents_ ) {
            if ( const vector<ClientError> &client_errors =
                     agent->GetClientErrors( );
                 !client_errors.empty( ) )
                if ( !Error::client_errors_.empty( ) ) {
                    // agent->OnError ( client_errors,
                    // control->GetProtocolErrors( );
                    errors_occurred = true;
                }

            agent->UseGeneralizedAbility ( use_generalized_ability_id );
        }

        if ( errors_occurred ) {
            return false;
        }

        // Run all clients on game start.
        for ( Agent *agent : agents_ ) {
            agent->GetObservation( );
        }
        for ( Agent *agent : agents_ ) {
            agent->OnGameFullStart( );
        }
        for ( Agent *agent : agents_ ) {
            agent->Client::OnGameStart( );
            agent->OnGameStart( );
        }
        for ( Agent *agent : agents_ ) {
            agent->IssueEvents ( agent->Actions( )->CommandsLastCall( ) );
        }

        return true;
    }

    /*! @brief Sets up the sc2 game ports to use
     * @param num_agents Number of agents in the game
     * @param port_start Starting port number
     * @param check_single  Checks if the game is a single player or multiplayer
     * game */
    void SetupPorts (
        const size_t num_agents,
        int          port_start,
        const bool   check_single = true
    ) {
        // Join the game if there are two human participants.
        size_t humans = 0;
        if ( check_single ) {
            for ( const auto &p_setup : game_settings_.player_setup ) {
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
                game_settings_.ports.client_ports.push_back ( port_set );
            }
        }
    }

    // Run.
    static void CallOnStep ( Agent *agent ) {
        if ( !agent->IsInGame( ) ) {
            agent->OnGameEnd( );
            agent->RequestLeaveGame( ); // Only for multiplayer.
            return;
        }

        ActionInterface *action = agent->Actions( );
        agent->IssueEvents ( action->CommandsLastCall( ) );
        if ( action ) {
            action->SendActions( );
        }

        if ( ActionFeatureLayerInterface *action_feature_layer =
                 agent->ActionsFeatureLayer( ) )
        {
            action_feature_layer->SendActions( );
        }
    }

    static void RunParallel (
        const function<void ( Agent *agent )> &step,
        const vector<Agent *>                 &agents
    ) {
        // Run all steps in parallel.
        vector<thread> threads ( agents.size( ) );
        for ( size_t i = 0; i < agents.size( ); ++i ) {
            Agent *agent     = agents.at ( i );
            threads.at ( i ) = thread ( bind ( step, agent ) );
        }

        for ( auto &thread : threads ) {
            thread.join( );
        }
    }

    void StepAgents ( ) const {
        auto step_agent = [this] ( Agent *agent ) {
            if ( agent->GetAppState( ) != AppState::Normal ) {
                return;
            }

            if ( agent->PollLeaveGame( ) ) {
                return;
            }

            if ( agent->IsFinishedGame( ) ) {
                return;
            }

            agent->Step ( process_settings_.step_size );
            agent->WaitStep( );
            if ( process_settings_.multi_threaded ) {
                CallOnStep ( agent );
            }
        };

        if ( agents_.size( ) == 1 ) {
            step_agent ( agents_.front( ) );
        } else {
            RunParallel ( step_agent, agents_ );
        }

        if ( !process_settings_.multi_threaded ) {
            for ( Agent *agent : agents_ ) {
                if ( agent->GetAppState( ) != AppState::Normal ) {
                    continue;
                }

                // It is possible to have a pending leave game request here.
                if ( agent->PollLeaveGame( ) ) {
                    continue;
                }

                CallOnStep ( agent );
            }
        }
    }

    void StepAgentsRealtime ( ) const {
        auto step_agent = [] ( Agent *agent ) {
            if ( !agent ) {
                return;
            }

            if ( agent->GetAppState( ) != AppState::Normal ) {
                return;
            }

            if ( agent->PollLeaveGame( ) ) {
                return;
            }

            if ( agent->IsFinishedGame( ) ) {
                return;
            }

            ActionInterface *action = agent->Actions( );
            if ( !action ) {
                return;
            }

            // This agent shouldn't call step since it's real time.
            agent->GetObservation( );
            agent->IssueEvents ( agent->Actions( )->CommandsLastCall( ) );
            action->SendActions( );

            if ( !agent->IsInGame( ) ) {
                agent->OnGameEnd( );
                agent->RequestLeaveGame( ); // Only for multiplayer.
            }
        };

        if ( process_settings_.multi_threaded ) {
            RunParallel ( step_agent, agents_ );
        } else {
            for ( Agent *agent : agents_ ) {
                step_agent ( agent );
            }
        }
    }

    void StepReplayObservers ( ) const {
        // Run all replay observers.
        auto run_replay = [this] ( ReplayObserver *replay_observer ) {
            if ( replay_observer->GetAppState( ) != AppState::Normal ) {
                return;
            }

            // If the replay is loading wait for it to finish loading before
            // performing a step.
            if ( replay_observer->HasResponsePending( ) ) {
                // Don't consume a response if there isn't one in the queue.
                if ( replay_observers_.size( ) > 1 &&
                     !replay_observer->PollResponse( ) )
                {
                    return;
                }
                replay_observer->WaitForReplay( );
            }

            if ( replay_observer->IsInGame( ) ) {
                replay_observer->Step ( process_settings_.step_size );
                replay_observer->WaitStep( );

                // If multithreaded run everyone's OnStep in parallel.
                if ( process_settings_.multi_threaded ) {
                    replay_observer->IssueEvents( );
                    replay_observer->ObserverAction( )->SendActions( );
                }

                if ( !replay_observer->IsInGame( ) ) {
                    replay_observer->OnGameEnd( );
                }
            }
        };

        if ( replay_observers_.size( ) == 1 ) {
            run_replay ( replay_observers_.front( ) );
        } else {
            // Run all steps in parallel.
            vector<thread> threads;
            threads.reserve ( replay_observers_.size( ) );
            for ( auto r : replay_observers_ ) {
                threads.emplace_back ( run_replay, r );
            }

            // Join all threads.
            for ( auto &t : threads ) {
                t.join( );
            }
        }

        // Do everyone's OnStep, if not multi threaded, in single threaded mode.
        if ( !process_settings_.multi_threaded ) {
            for ( ReplayObserver *replay_observer : replay_observers_ ) {
                if ( replay_observer->GetAppState( ) != AppState::Normal ) {
                    continue;
                }

                replay_observer->IssueEvents( );
                replay_observer->ObserverAction( )->SendActions( );
            }
        }
    }

    void StepReplayObserversRealtime ( ) const {
        // Run all replay observers.
        auto run_replay = [this] ( ReplayObserver *replay_observer ) {
            if ( replay_observer->GetAppState( ) != AppState::Normal ) {
                return;
            }

            // If the replay is loading wait for it to finish loading before
            // performing a step.
            if ( replay_observer->HasResponsePending( ) ) {
                // Don't consume a response if there isn't one in the queue.
                if ( replay_observers_.size( ) > 1 &&
                     !replay_observer->PollResponse( ) )
                {
                    return;
                }
                replay_observer->WaitForReplay( );
            }

            if ( replay_observer->IsInGame( ) ) {
                replay_observer->GetObservation( );

                // If multithreaded run everyone's OnStep in parallel.
                if ( process_settings_.multi_threaded ) {
                    replay_observer->IssueEvents( );
                }

                if ( !replay_observer->IsInGame( ) ) {
                    replay_observer->OnGameEnd( );
                }
            }
        };

        if ( replay_observers_.size( ) == 1 ) {
            run_replay ( replay_observers_.front( ) );
        } else {
            // Run all steps in parallel.
            vector<thread> threads;
            threads.reserve ( replay_observers_.size( ) );
            for ( auto r : replay_observers_ ) {
                threads.emplace_back ( run_replay, r );
            }

            // Join all threads.
            for ( auto &t : threads ) {
                t.join( );
            }
        }

        // Do everyone's OnStep, if not multi threaded, in single threaded mode.
        if ( !process_settings_.multi_threaded ) {
            for ( ReplayObserver *replay_observer : replay_observers_ ) {
                if ( replay_observer->GetAppState( ) != AppState::Normal ) {
                    continue;
                }

                replay_observer->IssueEvents( );
            }
        }
    }

    bool AnyObserverAvailable ( ) const {
        return ranges::any_of (
            replay_observers_,
            [] ( const ReplayObserver *replay_observer ) {
            return !replay_observer->IsInGame( );
        }
        );
    }

    /*! @brief Helper function used to actually run a bot. This function will
     * behave differently in real-time compared to non real-time.
     *
     * In real-time there is no step sent over the wire but instead will request
     * and read observations as the game runs.
     *
     * For non-real time Update will perform the following:
     *   1. Step the simulation forward by a certain amount of game steps, this
     * essentially moves the game loops forward.
     *   2. Wait for the step to complete, the step is completed when a response
     * is received and read from the StarCraft II binary. When the step is
     * completed an Observation has been received. It is parsed and various
     * client events are dispatched.
     *   3. Call the user's OnStep function.
     *
     * Real time applications will perform the following:
     *   1. The Observation is directly requested. The process will block while
     * waiting for it.
     *   2. The Observation is parsed and client events are dispatched.
     *   3. Unit actions batched from the ActionInterface are dispatched.
     * @return False if the game has ended, true otherwise. */
    bool Update ( ) {
        if ( agents_.size( ) != 0 ) {
            if ( process_settings_.realtime ) {
                StepAgentsRealtime( );
            } else {
                StepAgents( );
            }
        }

        if ( replay_observers_.size( ) != 0 && starcraft_started_ ) {
            if ( process_settings_.realtime ) {
                StepReplayObserversRealtime( );
            } else {
                StepReplayObservers( );
            }
        }

        if ( replay_observers_.size( ) != 0 ) {
            if ( AnyObserverAvailable( ) ) {
                StartReplay( );
            }
        }

        // Check for errors in all agents/replay observers at the end of an
        // update.
        bool error_occurred = false;
        for ( const Agent *agent : agents_ ) {
            if ( const vector<ClientError> &client_errors =
                     agent->GetClientErrors( );
                 !client_errors.empty( ) )
            {
                // agent->OnError ( client_errors, control->GetProtocolErrors( )
                // );
                error_occurred = true;
            }
        }

        bool relaunched = false;
        for ( ReplayObserver *replay_observer : replay_observers_ ) {
            if ( const vector<ClientError> &client_errors =
                     replay_observer->GetClientErrors( );
                 !client_errors.empty( ) )
            {
                // replay_observer->OnError (
                //         client_errors,
                //         control->GetProtocolErrors( )
                // );
                error_occurred = true;
                if ( replay_recovery_ ) {
                    // An error did occur but if we successfully recovered
                    // ignore it. The client will still gets its event
                    if ( Relaunch ( replay_observer ) ) {
                        error_occurred = false;
                        relaunched     = true;
                    }
                }
            }
        }

        // End the Coordinator update on the idea that an error in the API
        // should mean it's time to stop.
        if ( error_occurred ) {
            return false;
        }

        return !AllGamesEnded( ) || relaunched;
    }

    //! @brief Requests for the currently running game to end.
    void LeaveGame ( ) const {
        for ( Agent *agent : agents_ ) {
            agent->RequestLeaveGame( );
        }
    }

    // Status.

    //! @returns true if all running games have ended.
    bool AllGamesEnded ( ) const {
        for ( const Agent *agent : agents_ ) {
            if ( agent->IsInGame( ) || agent->HasResponsePending( ) ) {
                return false;
            }
        }

        for ( const ReplayObserver *replay_observer : replay_observers_ ) {
            if ( replay_observer->IsInGame( ) ||
                 replay_observer->HasResponsePending( ) )
            {
                return false;
            }
        }

        return true;
    }

    // Replay specific.

    /*! @brief Sets the path for to a folder of replays to analyze.
     * @param path The folder path. */
    bool SetReplayPath ( const string &path ) {
        replay_settings_.replay_file.clear( );

        if ( HasExtension ( path, ".SC2Replay" ) ) {
            replay_settings_.replay_file.push_back ( path );
        } else {
            replay_settings_.replay_dir = path;

            // Gather and append all files from the directory.
            if ( !replay_settings_.replay_dir.empty( ) ) {
                scan_directory (
                    replay_settings_.replay_dir.c_str( ),
                    replay_settings_.replay_file,
                    true,
                    false
                );
            }
        }

        return !replay_settings_.replay_file.empty( );
    }

    /*! @brief Loads replays from a file.
     * @param path The file path. */
    bool LoadReplayList ( const string &path ) {
        if ( !DoesFileExist ( path ) )
            return false;

        replay_settings_.replay_file.clear( );

        ifstream replay_file ( path );

        string line;
        while ( getline ( replay_file, line ) ) {
            if ( line.length( ) < 5 )
                continue;

            replay_settings_.replay_file.push_back ( line );
        }

        return true;
    }

    /*! @brief Saves replays to a file.
     * @param path The file path. */
    void SaveReplayList ( const string &path ) const {
        ofstream replay_file ( path, ofstream::out | ofstream::trunc );
        for ( const string &line : replay_settings_.replay_file ) {
            replay_file << line << '\n';
        }
    }

    /*! @brief Determines if there are unprocessed replays.
     * @return Is true if there are replays left. */
    bool HasReplays ( ) const {
        return !replay_settings_.replay_file.empty( );
    }

    // Misc.

    //! @brief Blocks for all bots to receive any pending responses
    bool WaitForAllResponses ( ) const {
        static constexpr int sleep_ms = 50;

        int total_sleep_ms = 0;
        for ( ;; ) {
            bool has_responses = false;

            for ( Agent *agent : agents_ ) {
                if ( !agent->HasResponsePending( ) ||
                     agent->GetAppState( ) != AppState::Normal )
                {
                    continue;
                }

                has_responses = true;

                if ( agent->PollResponse( ) ) {
                    agent->ConsumeResponse( );
                }

                break;
            }

            for ( ReplayObserver *replay_observer : replay_observers_ ) {
                if ( has_responses ) {
                    break;
                }

                if ( !replay_observer->HasResponsePending( ) ||
                     replay_observer->GetAppState( ) != AppState::Normal )
                {
                    continue;
                }
                has_responses = true;

                if ( replay_observer->PollResponse( ) ) {
                    replay_observer->ConsumeResponse( );
                }

                break;
            }

            if ( !has_responses ) {
                break;
            }

            if ( total_sleep_ms >= process_settings_.timeout_ms ) {
                assert ( 0 );
                return false;
            }

            SleepFor ( sleep_ms );
            total_sleep_ms += sleep_ms;
        }
        return true;
    }

    /*! @brief Saves a binary blob as a map to a remote location.
     * @param data The map data.
     * @param data_size The size of map data.
     * @param remote_path The file path to save the data to.
     * @return Is true if the save is successful. */
    bool RemoteSaveMap (
        const void   *data,
        const int     data_size,
        const string &remote_path
    ) const {
        for ( Agent *agent : agents_ ) {
            if ( !agent->RemoteSaveMap ( data, data_size, remote_path ) )
                return false;
        }

        for ( ReplayObserver *replay_observer : replay_observers_ ) {
            if ( !replay_observer
                      ->RemoteSaveMap ( data, data_size, remote_path ) )
                return false;
        }

        return true;
    }

    /*! @brief Gets the game executable path.
     * @return The game executable path. */
    string GetExePath ( ) const {
        if ( process_settings_.process_path.length( ) > 4 )
            return process_settings_.process_path;

        return process_settings_.process_path;
    }
};

} // namespace sc2
