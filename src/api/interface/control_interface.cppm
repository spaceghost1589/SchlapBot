module;
#include <cassert>
#include <iostream>
#include <memory>
#include <string>

#include <s2clientprotocol/sc2api.pb.h>

#include "lib/game_settings.h"
export module Client:control_interface;
import :observation_interface;
import error_handler;
import protocol_interface;

using std::cerr, std::cout, std::fstream, std::lock_guard, std::make_unique,
        std::mutex, std::ofstream, std::shared_ptr, std::size_t, std::string,
        std::to_string, std::unique_ptr;

namespace {




} // namespace

export namespace sc2 {

class Client;
class QueryInterface;
class DebugInterface;

class ControlInterface
{
public:
    AppState app_state_;
    bool     is_multiplayer_;

    // Observation from last step.
    ObservationPtr         observation_ptr;
    ResponseObservationPtr response_observation_ptr;

    unique_ptr<ObservationInterface> observation_face_;
    unique_ptr<QueryInterface>       query_impl_;
    unique_ptr<DebugInterface>       debug_impl_;
    ProcessInfo                      process_info_;

    ControlInterface::ControlInterface ( Client& client ):
        client_ ( client ),
        app_state_ ( AppState::normal ),
        is_multiplayer_ ( false ),
        observation_face_ ( nullptr ),
        query_impl_ ( nullptr ),
        debug_impl_ ( nullptr ) {
        observation_face_ = make_unique<ObservationInterface> (
                observation_ptr,
                response_observation_ptr,
                *this
        );
        query_impl_ = make_unique<QueryImpl> ( *this, *observation_face_ );
        debug_impl_ = make_unique<DebugImpl> ( *observation_face_, *this );
    }

    ControlInterface::~ControlInterface ( ) {
        ProtoFace::Quit( );
    }

    bool ControlInterface::Connect (
            const string& address, int port, int timeout_ms
    ) {
        // Keep retrying the connection until the timeout is hit.
        bool         connected = false;
        unsigned int timeout_seconds =
                ( static_cast<unsigned int> ( timeout_ms ) + 1500 ) / 1000;
        if ( timeout_seconds < 1 )
        {
            timeout_seconds = 1;
        }

        cout << "Connecting to " << address << ":" << port << "...\n";

        for ( unsigned int count_seconds = 0; count_seconds < timeout_seconds;
              ++count_seconds )
        {
            if ( sc2::ProtoFace::ConnectToGame ( address, port, timeout_ms ) )
            {
                connected = true;
                break;
            }
            SleepFor ( 1000 );
        }

        if ( !connected )
        {
            cerr << "Unable to connect to game\n";
            return false;
        }

        cout << "Connected to " << address << ":" << port << '\n';

        return true;
    }

    bool ControlInterface::RemoteSaveMap (
            const void* data, int data_size, string remote_path
    ) {
        // Request.
        {
            GameRequestPtr                  request = ProtoFace::MakeRequest( );
            SC2APIProtocol::RequestSaveMap* request_save_map =
                    request->mutable_save_map( );
            request_save_map->set_map_path ( remote_path );
            request_save_map->set_map_data ( data, data_size );

            if ( !ProtoFace::SendRequest ( request ) )
            {
                return false;
            }
        }

        // Response.
        const GameResponsePtr response = WaitForResponse( );
        if ( !response.get( ) )
        {
            return false;
        }

        if ( !response->has_save_map( ) )
        {
            cerr << "Error in ResponseSaveMap" << '\n';
            return false;
        }
        const SC2APIProtocol::ResponseSaveMap& response_save_game =
                response->save_map( );

        bool success = true;
        if ( response_save_game.has_error( ) )
        {
            success          = false;
            string errorCode = "Unknown";
            switch ( response_save_game.error( ) )
            {
                case SC2APIProtocol::ResponseSaveMap::InvalidMapData : {
                    errorCode = "Invalid Map Data";
                    break;
                }
                default : {
                    break;
                }
            }
        }

        return success;
    }

    bool ControlInterface::CreateGame (
            const string&              map_name,
            const vector<PlayerSetup>& players,
            bool                       realtime
    ) {
        const GameRequestPtr                     request = ProtoFace::MakeRequest( );
        SC2APIProtocol::RequestCreateGame* request_create_game =
                request->mutable_create_game( );
        ResolveMap ( map_name, request_create_game );
        for ( const PlayerSetup& setup : players )
        {
            SC2APIProtocol::PlayerSetup* playerSetup =
                    request_create_game->add_player_setup( );
            playerSetup->set_type ( SC2APIProtocol::PlayerType ( setup.type ) );
            playerSetup->set_race (
                    SC2APIProtocol::Race ( int ( setup.race ) )
            );
            playerSetup->set_player_name ( setup.player_name );
            playerSetup->set_difficulty (
                    SC2APIProtocol::Difficulty ( setup.difficulty )
            );
            playerSetup->set_ai_build (
                    SC2APIProtocol::AIBuild ( setup.ai_build )
            );
        }

        request_create_game->set_realtime ( realtime );

        if ( !ProtoFace::SendRequest ( request ) )
        {
            return false;
        }

        const GameResponsePtr response = WaitForResponse( );
        if ( !response.get( ) )
        {
            return false;
        }

        if ( !response->has_create_game( ) )
        {
            cerr << "Error in ResponseCreateGame" << '\n';
            return false;
        }

        const SC2APIProtocol::ResponseCreateGame& response_create_game =
                response->create_game( );

        bool success = true;
        if ( response_create_game.has_error( ) )
        {
            string errorCode = "Unknown";
            switch ( response_create_game.error( ) )
            {
                case SC2APIProtocol::ResponseCreateGame::MissingMap : {
                    errorCode = "Missing Map";
                    break;
                }
                case SC2APIProtocol::ResponseCreateGame::InvalidMapPath : {
                    errorCode = "Invalid Map Path";
                    break;
                }
                case SC2APIProtocol::ResponseCreateGame::InvalidMapData : {
                    errorCode = "Invalid Map Data";
                    break;
                }
                case SC2APIProtocol::ResponseCreateGame::InvalidMapName : {
                    errorCode = "Invalid Map Name";
                    break;
                }
                case SC2APIProtocol::ResponseCreateGame::InvalidMapHandle : {
                    errorCode = "Invalid Map Handle";
                    break;
                }
                case SC2APIProtocol::ResponseCreateGame::MissingPlayerSetup : {
                    errorCode = "Missing Player Setup";
                    break;
                }
                case SC2APIProtocol::ResponseCreateGame::InvalidPlayerSetup : {
                    errorCode = "Invalid Player Setup";
                    break;
                }
                default : {
                    break;
                }
            }

            cerr << "CreateGame request returned an error code: " << errorCode
                 << '\n';
            success = false;
        }

        if ( response_create_game.has_error_details( ) &&
             response_create_game.error_details( ).length( ) > 0 )
        {
            cerr << "CreateGame request returned error details: "
                 << response_create_game.error_details( ) << '\n';
            success = false;
        }

        return success;
    }

    // General.

    bool ControlInterface::IssueEvents ( const Tags& commands ) {
        if ( observation_face_->current_game_loop_ ==
             observation_face_->previous_game_loop )
        {
            return false;
        }

        void ControlInterface::IssueUnitDestroyedEvents( ) const {
            if ( !observation_ptr->has_raw_data( ) )
            {
                return;
            }

            const SC2APIProtocol::ObservationRaw& raw =
                    observation_ptr->raw_data( );
            if ( raw.has_event( ) )
            {
                const SC2APIProtocol::Event& event = raw.event( );
                for ( const auto& tag : event.dead_units( ) )
                {
                    const Unit* unit =
                            observation_face_->unit_pool_.GetUnit ( tag );

                    if ( !unit )
                    {
                        continue;
                    }

                    observation_face_->unit_pool_.MarkDead ( tag );
                    client_.OnUnitDestroyed ( unit );
                }
            }
        }

        void ControlInterface::IssueUnitAddedEvents( ) const {
            for ( auto unit : observation_face_->unit_pool_.GetNewUnits( ) )
            {
                if ( unit->alliance == Unit::Alliance::Self )
                {
                    client_.OnUnitCreated ( unit );
                }
                else if ( unit->alliance == Unit::Alliance::Neutral &&
                          unit->display_type == Unit::DisplayType::Visible )
                {
                    client_.OnNeutralUnitCreated ( unit );
                }
            }

            for ( auto unit :
                  observation_face_->unit_pool_.GetUnitsEnteringVision( ) )
            {
                if ( unit->alliance == Unit::Alliance::Enemy &&
                     unit->display_type == Unit::DisplayType::Visible )
                {
                    client_.OnUnitEnterVision ( unit );
                }
            }
        }

        void ControlInterface::IssueBuildingCompletedEvents( ) const {
            for ( auto unit :
                  observation_face_->unit_pool_.GetCompletedBuildings( ) )
            {
                if ( unit->alliance == Unit::Alliance::Self )
                {
                    client_.OnBuildingConstructionComplete ( unit );
                }
            }
        }

        void ControlInterface::IssueIdleEvents ( const Tags& commands ) const {
            auto& unit_pool = observation_face_->unit_pool_;
            // identify idled units where commands were issued last step, but
            // units have no orders now (maybe failed, maybe executed instantly)
            for ( auto t : commands )
            {
                const auto* unit = unit_pool.GetExistingUnit ( t );
                if ( unit && unit->orders.empty( ) )
                {
                    unit_pool.AddUnitIdled ( unit );
                }
            }

            // add newly created units (if they are completed)
            for ( const auto* u : unit_pool.GetNewUnits( ) )
            {
                if ( u->build_progress >= 1.0f && u->orders.empty( ) )
                {
                    unit_pool.AddUnitIdled ( u );
                }
            }

            // send only one idle event for any unit in any frame
            for ( const auto* u : unit_pool.GetIdledUnits( ) )
            {
                client_.OnUnitIdle ( u );
            }
        }

        void ControlInterface::IssueUpgradeEvents( ) const {
            set<uint32_t> previous;
            for ( UpgradeID upID : observation_face_->upgrades_previous_ )
            {
                previous.insert ( upID );
            }

            for ( UpgradeID upID : observation_face_->upgrades_ )
            {
                if ( previous.find ( upID ) == previous.end( ) )
                {
                    client_.OnUpgradeCompleted ( upID );
                }
            }
        }

        void ControlInterface::IssueAlertEvents( ) const {
            // Iterate the alerts and issue relevant events.
            for ( const auto alert : observation_ptr->alerts( ) )
            {
                switch ( alert )
                {
                    case SC2APIProtocol::Alert::NuclearLaunchDetected : {
                        client_.OnNuclearLaunchDetected( );
                        break;
                    }
                    case SC2APIProtocol::Alert::NydusWormDetected : {
                        client_.OnNydusDetected( );
                        break;
                    }
                    default : {
                        break;
                    }
                }
            }
        }

        void ControlInterface::IssueUnitDamagedEvents( ) const {
            for ( const auto& u :
                  observation_face_->unit_pool_.GetDamagedUnits( ) )
            {
                client_.OnUnitDamaged ( u.unit, u.health, u.shields );
            }
        }

        // Run the users OnStep function after events have been issued.
        client_.OnStep( );

        return true;
    }

    void ControlInterface::OnGameStart ( ) {
        Units units = observation_face_->GetUnits (
                Unit::Alliance::Self,
                [] ( const Unit& unit ) {
            return unit.unit_type == UNIT_TYPEID::TERRAN_COMMANDCENTER ||
                   unit.unit_type == UNIT_TYPEID::PROTOSS_NEXUS ||
                   unit.unit_type == UNIT_TYPEID::ZERG_HATCHERY;
        }
        );

        if ( units.empty( ) )
        {
            return;
        }

        // For now, until the api supports allies, the first (and only) building
        // in this list should be the start location
        observation_face_->start_location_ = units[0]->pos;

        // Clear start locations here since ControlInterface::OnGameStart is
        // called before the clients OnGameStart.
        observation_face_->game_info_.start_locations.clear( );
        observation_face_->game_info_.start_locations.push_back (
                observation_face_->start_location_
        );
    }

    // Diagnostic.
    void ControlInterface::DumpProtocolUsage ( ) {
        const vector<uint32_t>& stats = ProtoFace::GetStats( );
        cout << "******************************************************"
             << '\n';
        cout << "Protocol use by message type:" << '\n';
        for ( size_t i = 0; i < stats.size( ); ++i )
        {
            if ( stats[i] == 0 )
            {
                continue;
            }

            cout << to_string ( i ) << ": " << to_string ( stats[i] ) << '\n';
        }

        cout << "******************************************************"
             << '\n';
    }

    // Save/Load.
    void ControlInterface::Save ( ) {
        GameRequestPtr request = Proto( ).MakeRequest( );
        request->mutable_quick_save( );
        if ( !Proto( ).SendRequest ( request ) )
        {
            return;
        }
        WaitForResponse( );
    }

    void ControlInterface::Load ( ) {
        GameRequestPtr request = Proto( ).MakeRequest( );
        request->mutable_quick_load( );
        if ( !Proto( ).SendRequest ( request ) )
        {
            return;
        }
        WaitForResponse( );
    }

    bool ControlInterface::RequestJoinGame (
            PlayerSetup              setup,
            const InterfaceSettings& settings,
            const Ports&             ports,
            bool                     raw_affects_selection
    ) {
        observation_face_->ClearFlags( );

        is_multiplayer_ = ports.IsValid( );

        GameRequestPtr                   request = ProtoFace::MakeRequest( );
        SC2APIProtocol::RequestJoinGame* request_join_game =
                request->mutable_join_game( );

        request_join_game->set_race (
                SC2APIProtocol::Race ( int ( setup.race ) )
        );
        request_join_game->set_player_name ( setup.player_name );

        if ( is_multiplayer_ )
        {
            // Set shared port.
            request_join_game->set_shared_port ( ports.shared_port );

            // Set server ports.
            SC2APIProtocol::PortSet* server_ports =
                    request_join_game->mutable_server_ports( );
            server_ports->set_game_port ( ports.server_ports.game_port );
            server_ports->set_base_port ( ports.server_ports.base_port );

            // Set client ports. Right now only 1v1 is supported.
            for ( const PortSet& client_ports : ports.client_ports )
            {
                SC2APIProtocol::PortSet* client_port =
                        request_join_game->add_client_ports( );
                client_port->set_game_port ( client_ports.game_port );
                client_port->set_base_port ( client_ports.base_port );
            }
        }

        SC2APIProtocol::InterfaceOptions* options =
                request_join_game->mutable_options( );

        options->set_raw ( true );
        options->set_score ( true );
        options->set_show_cloaked ( true );
        options->set_show_burrowed_shadows ( true );
        options->set_show_placeholders ( true );

        // If raw_affects_selection == true, will not generate a deselect
        // command after sending a command to a unit
        options->set_raw_affects_selection ( raw_affects_selection );

        if ( settings.use_feature_layers )
        {
            SC2APIProtocol::SpatialCameraSetup* setupProto =
                    options->mutable_feature_layer( );
            setupProto->set_width (
                    settings.feature_layer_settings.camera_width
            );
            SC2APIProtocol::Size2DI* resolution =
                    setupProto->mutable_resolution( );
            resolution->set_x ( settings.feature_layer_settings.map_x );
            resolution->set_y ( settings.feature_layer_settings.map_y );
            SC2APIProtocol::Size2DI* minimap_resolution =
                    setupProto->mutable_minimap_resolution( );
            minimap_resolution->set_x (
                    settings.feature_layer_settings.minimap_x
            );
            minimap_resolution->set_y (
                    settings.feature_layer_settings.minimap_y
            );
        }
        if ( settings.use_render )
        {
            SC2APIProtocol::SpatialCameraSetup* setupProto =
                    options->mutable_render( );
            SC2APIProtocol::Size2DI* resolution =
                    setupProto->mutable_resolution( );
            resolution->set_x ( settings.render_settings.map_x );
            resolution->set_y ( settings.render_settings.map_y );
            SC2APIProtocol::Size2DI* minimap_resolution =
                    setupProto->mutable_minimap_resolution( );
            minimap_resolution->set_x ( settings.render_settings.minimap_x );
            minimap_resolution->set_y ( settings.render_settings.minimap_y );
        }

        return ProtoFace::SendRequest ( request );
    }

    bool ControlInterface::WaitJoinGame ( ) {
        cout << "Waiting for the JoinGame response." << '\n';
        const GameResponsePtr response = WaitForResponse( );
        if ( !response.get( ) )
        {
            cout << "Did not get a JoinGame response." << '\n';
            return false;
        }
        if ( !response->has_join_game( ) )
        {
            cout << "Response received is not JoinGame response." << '\n';
            return false;
        }

        if ( response->error_size( ) > 0 )
        {
            cout << "Error in joining the game." << '\n';
            assert ( 0 );
            return false;
        }

        observation_face_->player_id_ = response->join_game( ).player_id( );

        cout << "WaitJoinGame finished successfully." << '\n';
        return true;
    }

    bool ControlInterface::RequestLeaveGame ( ) {
        if ( !is_multiplayer_ )
        {
            return false;
        }

        GameRequestPtr request = ProtoFace::MakeRequest( );
        request->mutable_leave_game( );
        return ProtoFace::SendRequest ( request );
    }

    bool ControlInterface::PollLeaveGame ( ) {
        if ( !is_multiplayer_ )
        {
            return false;
        }

        if ( ProtoFace::GetResponsePending( ) !=
             SC2APIProtocol::Response::kLeaveGame )
        {
            // If not in a game, then it is in the end state trying to leave the
            // game.
            if ( HasResponsePending( ) )
                Error::Log ( ClientError::ResponseNotConsumed );
            return !IsInGame( );
        }

        // React to receiving a leave response.
        if ( !PollResponse( ) )
        {
            return true;
        }

        // Wait for the end response to be received before proceeding.
        // TODO (?): Add error handling.
        WaitForResponse( );
        return true;
    }

    bool ControlInterface::Step ( int count ) {
        if ( app_state_ != AppState::normal )
        {
            return false;
        }

        GameRequestPtr               request = ProtoFace::MakeRequest( );
        SC2APIProtocol::RequestStep* step    = request->mutable_step( );
        step->set_count ( count );
        return ProtoFace::SendRequest ( request );
    }

    bool ControlInterface::WaitStep ( ) {
        const GameResponsePtr response = WaitForResponse( );
        if ( !response.get( ) ||
             !response->has_step( ) ||
             response->error_size( ) > 0 )
        {
            return false;
        }

        return GetObservation( );
    }

    bool ControlInterface::SaveReplay ( const string& path ) {
        GameRequestPtr request = ProtoFace::MakeRequest( );
        request->mutable_save_replay( );
        if ( !ProtoFace::SendRequest ( request ) )
        {
            return false;
        }

        const GameResponsePtr response = WaitForResponse( );
        if ( !response.get( ) ||
             !response->has_save_replay( ) ||
             response->error_size( ) > 0 )
        {
            return false;
        }

        const SC2APIProtocol::ResponseSaveReplay& response_replay =
                response->save_replay( );

        if ( response_replay.data( ).empty( ) )
        {
            return false;
        }

        ofstream file;
        file.open ( path, fstream::binary );
        if ( !file.is_open( ) )
        {
            return false;
        }

        file.write (
                &response_replay.data( )[0],
                response_replay.data( ).size( )
        );
        return true;
    }

    bool ControlInterface::Ping ( ) {
        return ProtoFace::PingGame( );
    }

    GameResponsePtr ControlInterface::WaitForResponse ( ) {
        Assert ( app_state_ == AppState::normal );

        GameResponsePtr response = ProtoFace::WaitForResponseInternal( );

        if ( response.get( ) && response->error_size( ) < 1 )
        {
            // Everything is good. No need for any error handling.
            return response;
        }

        if ( response.get( ) && response->error_size( ) > 0 )
        {
            vector<string> errors;
            for ( int i = 0; i < response->error_size( ); ++i )
            {
                errors.push_back ( response->error ( i ) );
            }

            Error::Log ( ClientError::SC2ProtocolError, errors );
            return response;
        }
        Assert ( !response.get( ) );

        // The game application did not responded, the previous request was
        // either not sent or the app is non-responsive.

        // Step 1: distinguish between a hang and a crash. Lots of time has
        // elapsed, so if there was a crash it should have finished by now.
        Assert ( pi_.process_id );
        if ( !IsProcessRunning ( process_info_.process_id ) )
        {
            app_state_ = AppState::crashed;
            cout << "Game application has terminated unexpectedly." << '\n';
            Error::Log ( ClientError::SC2AppFailure );
            return response;
        }

        // Step 2: distinguish between a non-responsive app and a failure to
        // deliver a valid request.
        {
            GameRequestPtr ping_request = ProtoFace::MakeRequest( );
            ping_request->mutable_ping( );

            if ( !ProtoFace::SendRequest ( ping_request, true ) )
            {
                // Mark the game app as unresponsive.
                app_state_ = AppState::timeout;
                Error::Log ( ClientError::SC2ProtocolTimeout );
            }
            else
            {
                // Wait for a ping response. If this fails, the game is
                // unresponsive.
                // TODO (?): Implement a timeout parameter for this wait.
                const GameResponsePtr response_ping =
                        ProtoFace::WaitForResponseInternal( );
                if ( response_ping )
                {
                    if ( ProtoFace::GetLastStatus( ) ==
                         SC2APIProtocol::Status::unknown )
                    {
                        Error::Log ( ClientError::SC2UnknownStatus );
                    }

                    /*! The game is responsive, but there was another problem. This isn't the right place to handle another type of problem. Just return the nullptr.*/
                    Error::Log ( ClientError::SC2UnknownStatus );
                    return response;
                }

                app_state_ = AppState::timeout;
                Error::Log ( ClientError::SC2ProtocolTimeout );
            }
        }

        // The game application has hanged. Try and terminate it.
        app_state_ = AppState::timeout;
        for ( int i = 0;
              i < 10 && IsProcessRunning ( process_info_.process_id );
              ++i )
        {
            TerminateProcess ( process_info_.process_id );
            SleepFor ( 2000 );
        }

        if ( IsProcessRunning ( process_info_.process_id ) )
        {
            // Failed to kill the running process.
            app_state_ = AppState::timeout_zombie;
        }

        cout << "Game application has been terminated due to "
                "unresponsiveness."
             << '\n';
        Error::Log ( ClientError::SC2AppFailure );
        return response;
    }

    void ControlInterface::SetProcessInfo ( const ProcessInfo& pi ) {
        process_info_ = pi;
    }

    const ProcessInfo& ControlInterface::GetProcessInfo ( ) const {
        return process_info_;
    }

    // Game status.
    SC2APIProtocol::Status ControlInterface::GetLastStatus ( ) const {
        return ProtoFace::GetLastStatus( );
    }

    AppState ControlInterface::GetAppState ( ) const {
        return app_state_;
    }

    bool ControlInterface::IsInGame ( ) const {
        if ( app_state_ != AppState::normal )
        {
            return false;
        }

        return GetLastStatus( ) == SC2APIProtocol::Status::in_game ||
               GetLastStatus( ) == SC2APIProtocol::Status::in_replay;
    }

    bool ControlInterface::IsFinishedGame ( ) const {
        if ( app_state_ != AppState::normal )
        {
            return true;
        }

        if ( IsInGame( ) )
        {
            return false;
        }

        if ( HasResponsePending( ) )
        {
            return false;
        }

        return true;
    }

    bool ControlInterface::IsReadyForCreateGame ( ) const {
        if ( app_state_ != AppState::normal )
        {
            return false;
        }

        // Make sure the pipes are clear first.
        if ( HasResponsePending( ) )
        {
            return false;
        }

        // TODO (?): For multiplayer, it may be possible to be in the ended
        // state but not yet left the game. Must leave the game before create
        // game can be ready again.
        return GetLastStatus( ) == SC2APIProtocol::Status::launched ||
               GetLastStatus( ) == SC2APIProtocol::Status::ended;
    }

    bool ControlInterface::HasResponsePending ( ) const {
        return ProtoFace::HasResponsePending( );
    }

    bool ControlInterface::GetObservation ( ) {
        if ( app_state_ != AppState::normal )
        {
            return false;
        }

        GameRequestPtr request = ProtoFace::MakeRequest( );
        request->mutable_observation( );
        if ( !ProtoFace::SendRequest ( request ) )
        {
            return false;
        }

        const GameResponsePtr  response = WaitForResponse( );
        ResponseObservationPtr response_observation;
        SET_MESSAGE_RESPONSE ( response_observation, response, observation );
        if ( response_observation.HasErrors( ) )
        {
            cerr << '\n' << "Error in returning observation:" << '\n';
            cerr << "The main response is of type: "
                 << to_string ( response->response_case( ) ) << '\n';
            if ( response_observation.HasResponse( ) )
            {
                cerr << "There is no ResponseObservation/message!" << '\n';
            }
            if ( response->error_size( ) > 0 )
            {
                for ( int i = 0; i < response->error_size( ); ++i )
                {
                    cerr << "Error string: " << response->error ( i ) << '\n';
                }
            }
            else
            {
                cerr << "No error strings in result." << '\n';
            }
            cerr << '\n';
            return false;
        }

        ObservationPtr observation;
        SET_SUBMESSAGE_RESPONSE (
                observation,
                response_observation,
                observation
        );
        if ( observation.HasErrors( ) )
        {
            return false;
        }

        observation_ptr          = observation;
        response_observation_ptr = response_observation;

        observation_face_->UpdateObservation( );

        return true;
    }

    bool ControlInterface::PollResponse ( ) {
        return ProtoFace::PollResponse( );
    }

    bool ControlInterface::ConsumeResponse ( ) {
        const GameResponsePtr response = WaitForResponse( );
        return response.get( );
    }

    void ControlInterface::ResolveMap (
            const string& map_name, SC2APIProtocol::RequestCreateGame* request
    ) {
        // BattleNet map
        cout << "Resolving BattleNet map..." << '\n';
        if ( !HasExtension ( map_name, ".SC2Map" ) )
        {
            request->set_battlenet_map_name ( map_name );
            return;
        }
        cout << "No BattleNet map..." << '\n';

        // Absolute path
        cout << "Resolving Absolute map path..." << '\n';
        SC2APIProtocol::LocalMap* local_map = request->mutable_local_map( );
        if ( DoesFileExist ( map_name ) )
        {
            local_map->set_map_path ( map_name );
            return;
        }

        // Relative path - Game maps directory
        cout << "Resolving Relative map path..." << '\n';
        const string game_relative =
                GetGameMapsDirectory ( process_info_.process_path ) + map_name;
        if ( DoesFileExist ( game_relative ) )
        {
            local_map->set_map_path ( map_name );
            return;
        }

        // Relative path - Library maps directory
        cout << "Resolving Relative map path..." << '\n';
        string library_relative = GetLibraryMapsDirectory( ) + map_name;
        if ( DoesFileExist ( library_relative ) )
        {
            local_map->set_map_path ( library_relative );
            return;
        }

        // Relative path - Remotely saved maps directory
        local_map->set_map_path ( map_name );
    }

    void UseGeneralizedAbility ( bool value ) {
        observation_face_->use_generalized_ability_ = value;
    }
};

} // namespace sc2
