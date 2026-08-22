module;
#include <cassert>
#include <memory>
#include <string>
#include <vector>

#include "lib/game_settings.h"
export module control_interface;
import :observation_interface;

using std::shared_ptr, std::unique_ptr;

export namespace sc2 {

// SharedProtocolInterface protocol_interface;

class ControlInterface {
public:
    AppState app_state_;
    bool     is_multiplayer_;

    // Protocol and socket interface to the game.
    ProtocolInterface protocol_interface;

    // Client& client_;
    //
    // explicit ControlImpl(sc2::Client& client);
    // ~ControlImpl() override;

    // Observation from last step.
    ObservationPtr         observation_ptr;
    ResponseObservationPtr response_observation_ptr;

    unique_ptr<ObservationInterface> observation_impl_;
    unique_ptr<QueryInterface>       query_impl_;
    unique_ptr<DebugImpl>            debug_impl_;
    ProcessInfo                      process_info_;

    // Errors that may have occurred during calls to the various interfaces.
    vector<ClientError> client_errors_;
    vector<std::string> protocol_errors_;

    std::mutex error_mutex_;

    ControlInterface::ControlInterface (Client& client):
            client_ (client),
            app_state_ (AppState::normal),
            is_multiplayer_ (false),
            observation_impl_ (nullptr),
            query_impl_ (nullptr),
            debug_impl_ (nullptr) {
        protocol_interface.SetControl (this);
        observation_impl_ = std::make_unique<ObservationInterface> (
                protocol_interface,
                observation_ptr,
                response_observation_ptr,
                *this
        );
        query_impl_ = std::make_unique<QueryImpl> (
                protocol_interface,
                *this,
                *observation_impl_
        );
        debug_impl_ = std::make_unique<DebugImpl> (
                protocol_interface,
                *observation_impl_,
                *this
        );
    }

    ControlInterface::~ControlInterface () {
        protocol_interface.Quit();
    }

    ProtocolInterface& ControlInterface::Proto () {
        return protocol_interface;
    }

    bool ControlInterface::Connect (
            const std::string& address, int port, int timeout_ms
    ) {
        // Keep retrying the connection until the timeout is hit.
        bool         connected = false;
        unsigned int timeout_seconds =
                ((unsigned int) timeout_ms + 1500) / 1000;
        if ( timeout_seconds < 1 ) {
            timeout_seconds = 1;
        }

        std::cout << "Connecting to " << address << ":" << port << "...\n";

        for ( unsigned int count_seconds = 0; count_seconds < timeout_seconds;
              ++count_seconds ) {
            if ( protocol_interface
                         .ConnectToGame (address, port, timeout_ms) ) {
                connected = true;
                break;
            }
            SleepFor (1000);
        }

        if ( !connected ) {
            std::cerr << "Unable to connect to game\n";
            return false;
        }

        std::cout << "Connected to " << address << ":" << port << '\n';

        return true;
    }

    bool ControlInterface::RemoteSaveMap (
            const void* data, int data_size, std::string remote_path
    ) {
        // Request.
        {
            GameRequestPtr request = protocol_interface.MakeRequest();
            SC2APIProtocol::RequestSaveMap* request_save_map =
                    request->mutable_save_map();
            request_save_map->set_map_path (remote_path);
            request_save_map->set_map_data (data, data_size);

            if ( !protocol_interface.SendRequest (request) ) {
                return false;
            }
        }

        // Response.
        const GameResponsePtr response = WaitForResponse();
        if ( !response.get() ) {
            return false;
        }

        if ( !response->has_save_map() ) {
            std::cerr << "Error in ResponseSaveMap" << '\n';
            return false;
        }
        const SC2APIProtocol::ResponseSaveMap& response_save_game =
                response->save_map();

        bool success = true;
        if ( response_save_game.has_error() ) {
            success               = false;
            std::string errorCode = "Unknown";
            switch ( response_save_game.error() ) {
                case SC2APIProtocol::ResponseSaveMap::InvalidMapData: {
                    errorCode = "Invalid Map Data";
                    break;
                }
                default: {
                    break;
                }
            }
        }

        return success;
    }

    bool ControlInterface::CreateGame (
            const std::string&         map_name,
            const vector<PlayerSetup>& players,
            bool                       realtime
    ) {
        GameRequestPtr request = protocol_interface.MakeRequest();
        SC2APIProtocol::RequestCreateGame* request_create_game =
                request->mutable_create_game();
        ResolveMap (map_name, request_create_game);
        for ( const PlayerSetup& setup : players ) {
            SC2APIProtocol::PlayerSetup* playerSetup =
                    request_create_game->add_player_setup();
            playerSetup->set_type (SC2APIProtocol::PlayerType (setup.type));
            playerSetup->set_race (SC2APIProtocol::Race (int (setup.race)));
            playerSetup->set_player_name (setup.player_name);
            playerSetup->set_difficulty (
                    SC2APIProtocol::Difficulty (setup.difficulty)
            );
            playerSetup->set_ai_build (
                    SC2APIProtocol::AIBuild (setup.ai_build)
            );
        }

        request_create_game->set_realtime (realtime);

        if ( !protocol_interface.SendRequest (request) ) {
            return false;
        }

        const GameResponsePtr response = WaitForResponse();
        if ( !response.get() ) {
            return false;
        }

        if ( !response->has_create_game() ) {
            std::cerr << "Error in ResponseCreateGame" << '\n';
            return false;
        }

        const SC2APIProtocol::ResponseCreateGame& response_create_game =
                response->create_game();

        bool success = true;
        if ( response_create_game.has_error() ) {
            std::string errorCode = "Unknown";
            switch ( response_create_game.error() ) {
                case SC2APIProtocol::ResponseCreateGame::MissingMap: {
                    errorCode = "Missing Map";
                    break;
                }
                case SC2APIProtocol::ResponseCreateGame::InvalidMapPath: {
                    errorCode = "Invalid Map Path";
                    break;
                }
                case SC2APIProtocol::ResponseCreateGame::InvalidMapData: {
                    errorCode = "Invalid Map Data";
                    break;
                }
                case SC2APIProtocol::ResponseCreateGame::InvalidMapName: {
                    errorCode = "Invalid Map Name";
                    break;
                }
                case SC2APIProtocol::ResponseCreateGame::InvalidMapHandle: {
                    errorCode = "Invalid Map Handle";
                    break;
                }
                case SC2APIProtocol::ResponseCreateGame::MissingPlayerSetup: {
                    errorCode = "Missing Player Setup";
                    break;
                }
                case SC2APIProtocol::ResponseCreateGame::InvalidPlayerSetup: {
                    errorCode = "Invalid Player Setup";
                    break;
                }
                default: {
                    break;
                }
            }

            std::cerr << "CreateGame request returned an error code: "
                      << errorCode << '\n';
            success = false;
        }

        if ( response_create_game.has_error_details() &&
             response_create_game.error_details().length() > 0 ) {
            std::cerr << "CreateGame request returned error details: "
                      << response_create_game.error_details() << '\n';
            success = false;
        }

        return success;
    }

    // General.

    bool ControlInterface::IssueEvents (const Tags& commands) {
        if ( observation_impl_->current_game_loop_ ==
             observation_impl_->previous_game_loop ) {
            return false;
        }

        void ControlInterface::IssueUnitDestroyedEvents() const {
            if ( !observation_ptr->has_raw_data() ) {
                return;
            }

            const SC2APIProtocol::ObservationRaw& raw =
                    observation_ptr->raw_data();
            if ( raw.has_event() ) {
                const SC2APIProtocol::Event& event = raw.event();
                for ( const auto& tag : event.dead_units() ) {
                    const Unit* unit =
                            observation_impl_->unit_pool_.GetUnit (tag);

                    if ( !unit ) {
                        continue;
                    }

                    observation_impl_->unit_pool_.MarkDead (tag);
                    client_.OnUnitDestroyed (unit);
                }
            }
        }

        void ControlInterface::IssueUnitAddedEvents() const {
            for ( auto unit : observation_impl_->unit_pool_.GetNewUnits() ) {
                if ( unit->alliance == Unit::Alliance::Self ) {
                    client_.OnUnitCreated (unit);
                } else if ( unit->alliance == Unit::Alliance::Neutral &&
                            unit->display_type == Unit::DisplayType::Visible ) {
                    client_.OnNeutralUnitCreated (unit);
                }
            }

            for ( auto unit :
                  observation_impl_->unit_pool_.GetUnitsEnteringVision() ) {
                if ( unit->alliance == Unit::Alliance::Enemy &&
                     unit->display_type == Unit::DisplayType::Visible ) {
                    client_.OnUnitEnterVision (unit);
                }
            }
        }

        void ControlInterface::IssueBuildingCompletedEvents() const {
            for ( auto unit :
                  observation_impl_->unit_pool_.GetCompletedBuildings() ) {
                if ( unit->alliance == Unit::Alliance::Self ) {
                    client_.OnBuildingConstructionComplete (unit);
                }
            }
        }

        void ControlInterface::IssueIdleEvents (const Tags& commands) const {
            auto& unit_pool = observation_impl_->unit_pool_;
            // identify idled units where commands were issued last step, but
            // units have no orders now (maybe failed, maybe executed instantly)
            for ( auto t : commands ) {
                const auto* unit = unit_pool.GetExistingUnit (t);
                if ( unit && unit->orders.empty() ) {
                    unit_pool.AddUnitIdled (unit);
                }
            }

            // add newly created units (if they are completed)
            for ( const auto* u : unit_pool.GetNewUnits() ) {
                if ( u->build_progress >= 1.0f && u->orders.empty() ) {
                    unit_pool.AddUnitIdled (u);
                }
            }

            // send only one idle event for any unit in any frame
            for ( const auto* u : unit_pool.GetIdledUnits() ) {
                client_.OnUnitIdle (u);
            }
        }

        void ControlInterface::IssueUpgradeEvents() const {
            set<uint32_t> previous;
            for ( UpgradeID upID : observation_impl_->upgrades_previous_ ) {
                previous.insert (upID);
            }

            for ( UpgradeID upID : observation_impl_->upgrades_ ) {
                if ( previous.find (upID) == previous.end() ) {
                    client_.OnUpgradeCompleted (upID);
                }
            }
        }

        void ControlInterface::IssueAlertEvents() const {
            // Iterate the alerts and issue relevant events.
            for ( const auto alert : observation_ptr->alerts() ) {
                switch ( alert ) {
                    case SC2APIProtocol::Alert::NuclearLaunchDetected: {
                        client_.OnNuclearLaunchDetected();
                        break;
                    }
                    case SC2APIProtocol::Alert::NydusWormDetected: {
                        client_.OnNydusDetected();
                        break;
                    }
                    default: {
                        break;
                    }
                }
            }
        }

        void ControlInterface::IssueUnitDamagedEvents() const {
            for ( const auto& u :
                  observation_impl_->unit_pool_.GetDamagedUnits() ) {
                client_.OnUnitDamaged (u.unit, u.health, u.shields);
            }
        }

        // Run the users OnStep function after events have been issued.
        client_.OnStep();

        return true;
    }

    void ControlInterface::OnGameStart () {
        Units units = observation_impl_->GetUnits (
                Unit::Alliance::Self,
                [] (const Unit& unit) {
            return unit.unit_type == UNIT_TYPEID::TERRAN_COMMANDCENTER ||
                   unit.unit_type == UNIT_TYPEID::PROTOSS_NEXUS ||
                   unit.unit_type == UNIT_TYPEID::ZERG_HATCHERY;
        }
        );

        if ( units.empty() ) {
            return;
        }

        // For now, until the api supports allies, the first (and only) building
        // in this list should be the start location
        observation_impl_->start_location_ = units[0]->pos;

        // Clear start locations here since ControlInterface::OnGameStart is
        // called before the clients OnGameStart.
        observation_impl_->game_info_.start_locations.clear();
        observation_impl_->game_info_.start_locations.push_back (
                observation_impl_->start_location_
        );
    }

    // Diagnostic.
    void ControlInterface::DumpProtocolUsage () {
        const vector<uint32_t>& stats = protocol_interface.GetStats();
        std::cout << "******************************************************"
                  << '\n';
        std::cout << "Protocol use by message type:" << '\n';
        for ( std::size_t i = 0; i < stats.size(); ++i ) {
            if ( stats[i] == 0 ) {
                continue;
            }

            std::cout << std::to_string (i) << ": " << std::to_string (stats[i])
                      << '\n';
        }

        std::cout << "******************************************************"
                  << '\n';
    }

    void ControlInterface::Error (
            ClientError error, const vector<string>& errors
    ) {
        // An ConnectionClosed error can come off a civetweb worker thread.
        const std::lock_guard guard (error_mutex_);

        // Cache all the errors that happen
        client_errors_.push_back (error);
        for ( const string& e : errors ) {
            protocol_errors_.push_back (e);
        }

    #ifdef SC2API_ASSERT_ON_ERROR
            assert (0);
    #endif
    }

    void ControlInterface::ErrorIf (
            bool                                        condition,
            ClientError                                 error,
            [[maybe_unused]] const vector<std::string>& errors
    ) {
        if ( condition ) {
            Error (error, errors);
        }
    }

    // Save/Load.
    void ControlInterface::Save () {
        GameRequestPtr request = Proto().MakeRequest();
        request->mutable_quick_save();
        if ( !Proto().SendRequest (request) ) {
            return;
        }
        WaitForResponse();
    }

    void ControlInterface::Load () {
        GameRequestPtr request = Proto().MakeRequest();
        request->mutable_quick_load();
        if ( !Proto().SendRequest (request) ) {
            return;
        }
        WaitForResponse();
    }

    bool ControlInterface::RequestJoinGame (
            PlayerSetup              setup,
            const InterfaceSettings& settings,
            const Ports&             ports,
            bool                     raw_affects_selection
    ) {
        observation_impl_->ClearFlags();

        is_multiplayer_ = ports.IsValid();

        GameRequestPtr request = protocol_interface.MakeRequest();
        SC2APIProtocol::RequestJoinGame* request_join_game =
                request->mutable_join_game();

        request_join_game->set_race (SC2APIProtocol::Race (int (setup.race)));
        request_join_game->set_player_name (setup.player_name);

        if ( is_multiplayer_ ) {
            // Set shared port.
            request_join_game->set_shared_port (ports.shared_port);

            // Set server ports.
            SC2APIProtocol::PortSet* server_ports =
                    request_join_game->mutable_server_ports();
            server_ports->set_game_port (ports.server_ports.game_port);
            server_ports->set_base_port (ports.server_ports.base_port);

            // Set client ports. Right now only 1v1 is supported.
            for ( const PortSet& client_ports : ports.client_ports ) {
                SC2APIProtocol::PortSet* client_port =
                        request_join_game->add_client_ports();
                client_port->set_game_port (client_ports.game_port);
                client_port->set_base_port (client_ports.base_port);
            }
        }

        SC2APIProtocol::InterfaceOptions* options =
                request_join_game->mutable_options();

        options->set_raw (true);
        options->set_score (true);
        options->set_show_cloaked (true);
        options->set_show_burrowed_shadows (true);
        options->set_show_placeholders (true);

        // If raw_affects_selection == true, will not generate a deselect
        // command after sending a command to a unit
        options->set_raw_affects_selection (raw_affects_selection);

        if ( settings.use_feature_layers ) {
            SC2APIProtocol::SpatialCameraSetup* setupProto =
                    options->mutable_feature_layer();
            setupProto->set_width (
                    settings.feature_layer_settings.camera_width
            );
            SC2APIProtocol::Size2DI* resolution =
                    setupProto->mutable_resolution();
            resolution->set_x (settings.feature_layer_settings.map_x);
            resolution->set_y (settings.feature_layer_settings.map_y);
            SC2APIProtocol::Size2DI* minimap_resolution =
                    setupProto->mutable_minimap_resolution();
            minimap_resolution->set_x (
                    settings.feature_layer_settings.minimap_x
            );
            minimap_resolution->set_y (
                    settings.feature_layer_settings.minimap_y
            );
        }
        if ( settings.use_render ) {
            SC2APIProtocol::SpatialCameraSetup* setupProto =
                    options->mutable_render();
            SC2APIProtocol::Size2DI* resolution =
                    setupProto->mutable_resolution();
            resolution->set_x (settings.render_settings.map_x);
            resolution->set_y (settings.render_settings.map_y);
            SC2APIProtocol::Size2DI* minimap_resolution =
                    setupProto->mutable_minimap_resolution();
            minimap_resolution->set_x (settings.render_settings.minimap_x);
            minimap_resolution->set_y (settings.render_settings.minimap_y);
        }

        return protocol_interface.SendRequest (request);
    }

    bool ControlInterface::WaitJoinGame () {
        std::cout << "Waiting for the JoinGame response." << '\n';
        const GameResponsePtr response = WaitForResponse();
        if ( !response.get() ) {
            std::cout << "Did not get a JoinGame response." << '\n';
            return false;
        }
        if ( !response->has_join_game() ) {
            std::cout << "Response received is not JoinGame response." << '\n';
            return false;
        }

        if ( response->error_size() > 0 ) {
            std::cout << "Error in joining the game." << '\n';
            assert (0);
            return false;
        }

        observation_impl_->player_id_ = response->join_game().player_id();

        std::cout << "WaitJoinGame finished successfully." << '\n';
        return true;
    }

    bool ControlInterface::RequestLeaveGame () {
        if ( !is_multiplayer_ ) {
            return false;
        }

        GameRequestPtr request = protocol_interface.MakeRequest();
        request->mutable_leave_game();
        return protocol_interface.SendRequest (request);
    }

    bool ControlInterface::PollLeaveGame () {
        if ( !is_multiplayer_ ) {
            return false;
        }

        if ( protocol_interface.GetResponsePending() !=
             SC2APIProtocol::Response::kLeaveGame ) {
            // If not in a game, then it is in the end state trying to leave the
            // game.
            ErrorIf (HasResponsePending(), ClientError::ResponseNotConsumed);
            return !IsInGame();
        }

        // React to receiving a leave response.
        if ( !PollResponse() ) {
            return true;
        }

        // Wait for the end response to be received before proceeding.
        // TODO (?): Add error handling.
        WaitForResponse();
        return true;
    }

    bool ControlInterface::Step (int count) {
        if ( app_state_ != AppState::normal ) {
            return false;
        }

        GameRequestPtr               request = protocol_interface.MakeRequest();
        SC2APIProtocol::RequestStep* step    = request->mutable_step();
        step->set_count (count);
        return protocol_interface.SendRequest (request);
    }

    bool ControlInterface::WaitStep () {
        const GameResponsePtr response = WaitForResponse();
        if ( !response.get() ||
             !response->has_step() ||
             response->error_size() > 0 ) {
            return false;
        }

        return GetObservation();
    }

    bool ControlInterface::SaveReplay (const std::string& path) {
        GameRequestPtr request = protocol_interface.MakeRequest();
        request->mutable_save_replay();
        if ( !protocol_interface.SendRequest (request) ) {
            return false;
        }

        const GameResponsePtr response = WaitForResponse();
        if ( !response.get() ||
             !response->has_save_replay() ||
             response->error_size() > 0 ) {
            return false;
        }

        const SC2APIProtocol::ResponseSaveReplay& response_replay =
                response->save_replay();

        if ( response_replay.data().empty() ) {
            return false;
        }

        std::ofstream file;
        file.open (path, std::fstream::binary);
        if ( !file.is_open() ) {
            return false;
        }

        file.write (&response_replay.data()[0], response_replay.data().size());
        return true;
    }

    bool ControlInterface::Ping () {
        return protocol_interface.PingGame();
    }

    GameResponsePtr ControlInterface::WaitForResponse () {
        assert (app_state_ == AppState::normal);

        GameResponsePtr response = protocol_interface.WaitForResponseInternal();

        if ( response.get() && response->error_size() < 1 ) {
            // Everything is good. No need for any error handling.
            return response;
        }

        if ( response.get() && response->error_size() > 0 ) {
            vector<std::string> errors;
            for ( int i = 0; i < response->error_size(); ++i ) {
                errors.push_back (response->error (i));
            }

            Error (ClientError::SC2ProtocolError, errors);
            return response;
        }
        assert (!response.get());

        // The game application did not responded, the previous request was
        // either not sent or the app is non-responsive.

        // Step 1: distinguish between a hang and a crash. Lots of time has
        // elapsed, so if there was a crash it should have finished by now.
        assert (pi_.process_id);
        if ( !IsProcessRunning (process_info_.process_id) ) {
            app_state_ = AppState::crashed;
            std::cout << "Game application has terminated unexpectedly."
                      << '\n';
            Error (ClientError::SC2AppFailure);
            return response;
        }

        // Step 2: distinguish between a non-responsive app and a failure to
        // deliver a valid request.
        {
            GameRequestPtr ping_request = protocol_interface.MakeRequest();
            ping_request->mutable_ping();

            if ( !protocol_interface.SendRequest (ping_request, true) ) {
                // Mark the game app as unresponsive.
                app_state_ = AppState::timeout;
                Error (ClientError::SC2ProtocolTimeout);
            } else {
                // Wait for a ping response. If this fails, the game is
                // unresponsive.
                // TODO (?): Implement a timeout parameter for this wait.
                const GameResponsePtr response_ping =
                        protocol_interface.WaitForResponseInternal();
                if ( response_ping ) {
                    if ( protocol_interface.GetLastStatus() ==
                         SC2APIProtocol::Status::unknown ) {
                        Error (ClientError::SC2UnknownStatus);
                    }

                    // The game is responsive, but there was another problem.
                    // This isn't the right place to handle another type of
                    // problem. Just return the nullptr.
                    Error (ClientError::SC2UnknownStatus);
                    return response;
                }

                app_state_ = AppState::timeout;
                Error (ClientError::SC2ProtocolTimeout);
            }
        }

        // The game application has hanged. Try and terminate it.
        app_state_ = AppState::timeout;
        for ( int i = 0; i < 10 && IsProcessRunning (process_info_.process_id);
              ++i ) {
            TerminateProcess (process_info_.process_id);
            SleepFor (2000);
        }

        if ( IsProcessRunning (process_info_.process_id) ) {
            // Failed to kill the running process.
            app_state_ = AppState::timeout_zombie;
        }

        std::cout << "Game application has been terminated due to "
                     "unresponsiveness."
                  << '\n';
        Error (ClientError::SC2AppFailure);
        return response;
    }

    void ControlInterface::SetProcessInfo (const ProcessInfo& pi) {
        process_info_ = pi;
    }

    const ProcessInfo& ControlInterface::GetProcessInfo () const {
        return process_info_;
    }

    // Game status.
    SC2APIProtocol::Status ControlInterface::GetLastStatus () const {
        return protocol_interface.GetLastStatus();
    }

    AppState ControlInterface::GetAppState () const {
        return app_state_;
    }

    bool ControlInterface::IsInGame () const {
        if ( app_state_ != AppState::normal ) {
            return false;
        }

        return GetLastStatus() == SC2APIProtocol::Status::in_game ||
               GetLastStatus() == SC2APIProtocol::Status::in_replay;
    }

    bool ControlInterface::IsFinishedGame () const {
        if ( app_state_ != AppState::normal ) {
            return true;
        }

        if ( IsInGame() ) {
            return false;
        }

        if ( HasResponsePending() ) {
            return false;
        }

        return true;
    }

    bool ControlInterface::IsReadyForCreateGame () const {
        if ( app_state_ != AppState::normal ) {
            return false;
        }

        // Make sure the pipes are clear first.
        if ( HasResponsePending() ) {
            return false;
        }

        // TODO (?): For multiplayer, it may be possible to be in the ended
        // state but not yet left the game. Must leave the game before create
        // game can be ready again.
        return GetLastStatus() == SC2APIProtocol::Status::launched ||
               GetLastStatus() == SC2APIProtocol::Status::ended;
    }

    bool ControlInterface::HasResponsePending () const {
        return protocol_interface.HasResponsePending();
    }

    bool ControlInterface::GetObservation () {
        if ( app_state_ != AppState::normal ) {
            return false;
        }

        GameRequestPtr request = protocol_interface.MakeRequest();
        request->mutable_observation();
        if ( !protocol_interface.SendRequest (request) ) {
            return false;
        }

        const GameResponsePtr  response = WaitForResponse();
        ResponseObservationPtr response_observation;
        SET_MESSAGE_RESPONSE (response_observation, response, observation);
        if ( response_observation.HasErrors() ) {
            std::cerr << '\n' << "Error in returning observation:" << '\n';
            std::cerr << "The main response is of type: "
                      << std::to_string (response->response_case()) << '\n';
            if ( response_observation.HasResponse() ) {
                std::cerr << "There is no ResponseObservation/message!" << '\n';
            }
            if ( response->error_size() > 0 ) {
                for ( int i = 0; i < response->error_size(); ++i ) {
                    std::cerr << "Error string: " << response->error (i)
                              << '\n';
                }
            } else {
                std::cerr << "No error strings in result." << '\n';
            }
            std::cerr << '\n';
            return false;
        }

        ObservationPtr observation;
        SET_SUBMESSAGE_RESPONSE (
                observation,
                response_observation,
                observation
        );
        if ( observation.HasErrors() ) {
            return false;
        }

        observation_ptr          = observation;
        response_observation_ptr = response_observation;

        observation_impl_->UpdateObservation();

        return true;
    }

    bool ControlInterface::PollResponse () {
        return protocol_interface.PollResponse();
    }

    bool ControlInterface::ConsumeResponse () {
        const GameResponsePtr response = WaitForResponse();
        return response.get();
    }

    void OnGameStart ();

    bool IssueEvents (const Tags& commands = {});

    void IssueUnitDestroyedEvents () const;

    void IssueUnitAddedEvents () const;

    void IssueIdleEvents (const Tags& commands) const;

    void IssueBuildingCompletedEvents () const;

    void IssueUnitDamagedEvents () const;

    void IssueAlertEvents () const;

    void IssueUpgradeEvents () const;

    void DumpProtocolUsage () override;

    void ControlInterface::ResolveMap (
            const std::string&                 map_name,
            SC2APIProtocol::RequestCreateGame* request
    ) {
        // BattleNet map
        std::cout << "Resolving BattleNet map..." << '\n';
        if ( !HasExtension (map_name, ".SC2Map") ) {
            request->set_battlenet_map_name (map_name);
            return;
        }
        std::cout << "No BattleNet map..." << '\n';

        // Absolute path
        std::cout << "Resolving Absolute map path..." << '\n';
        SC2APIProtocol::LocalMap* local_map = request->mutable_local_map();
        if ( DoesFileExist (map_name) ) {
            local_map->set_map_path (map_name);
            return;
        }

        // Relative path - Game maps directory
        std::cout << "Resolving Relative map path..." << '\n';
        const std::string game_relative =
                GetGameMapsDirectory (process_info_.process_path) + map_name;
        if ( DoesFileExist (game_relative) ) {
            local_map->set_map_path (map_name);
            return;
        }

        // Relative path - Library maps directory
        std::cout << "Resolving Relative map path..." << '\n';
        std::string library_relative = GetLibraryMapsDirectory() + map_name;
        if ( DoesFileExist (library_relative) ) {
            local_map->set_map_path (library_relative);
            return;
        }

        // Relative path - Remotely saved maps directory
        local_map->set_map_path (map_name);
    }

    const vector<ClientError>& GetClientErrors () const final {
        return client_errors_;
    }

    const vector<std::string>& GetProtocolErrors () const final {
        return protocol_errors_;
    }

    void ClearClientErrors () override {
        client_errors_.clear();
    }

    void ClearProtocolErrors () override {
        protocol_errors_.clear();
    }

    void UseGeneralizedAbility (bool value) override {
        observation_impl_->use_generalized_ability_ = value;
    }

    void Save () override;

    void Load () override;
};

// using SharedControlInterface = shared_ptr<ControlInterface>;

} // namespace sc2
