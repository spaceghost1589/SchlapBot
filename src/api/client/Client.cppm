module;
#include <cassert>
#include <fstream>
#include <iostream>
#include <memory>
#include <set>
#include <string>
#include <vector>

#include <s2clientprotocol/sc2api.pb.h>

#include "utils/macro/message_response.h"
#include "utils/manage_process.h"
export module Client;
import debug_interface;
import observation_interface;
import protocol_interface;
import query_interface;
import data;
import error_handler;
import game_settings;
import game_types;
import map_info;
import point;
import proto_to_pods;
import renderer;
import score;
import type_enums;
import unit;

namespace {
using namespace std;
} // namespace

export namespace sc2 {


GameResponsePtr WaitForResponse ( );

/*! The base class for Agent and ReplayObserver.
 * The Client and ClientEvents provides most of the functionality a user would
 * be interested in for examining game state and scripting bots. A user should
 * prefer to inherit from either Agent or ReplayObserver, those classes both
 * inherit from Client. */


//! The base class for Agent (then Bot) and ReplayObserver.\n\n
//! Merged with Control Interface.
class Client {
public:
    // Observation from last step.
    ObservationPtr         observation_;
    ResponseObservationPtr response_;

    unique_ptr<ObservationInterface> observation_face_ =
        make_unique<ObservationInterface> ( observation_, response_ );
    unique_ptr<QueryInterface> query_face_ =
        make_unique<QueryInterface> ( *observation_face_ );
    unique_ptr<DebugInterface> debug_face_ =
        make_unique<DebugInterface> ( *observation_face_ );

    // ProcessInfo pi_;

    // Errors that may have occurred during calls to the various interfaces.
    vector<ClientError> client_errors_;
    vector<string>      protocol_errors_;

    bool is_multiplayer_ { false };

    explicit Client ( ) { }

    virtual ~Client ( ) {
        ProtoFace::Quit( );
    }

    /*! @brief Called when a game is started after a load. Fast restarting will
     * not call this. */
    virtual void OnGameFullStart ( ) { }

    /*! @brief Called when a game is started or restarted. */
    virtual void OnGameStart ( ) {
        const Units units = observation_face_->GetUnits (
            Unit::Alliance::Self,
            [] ( const Unit &unit ) {
            return unit.unit_type == UNIT_TYPEID::TERRAN_COMMANDCENTER ||
                   unit.unit_type == UNIT_TYPEID::PROTOSS_NEXUS ||
                   unit.unit_type == UNIT_TYPEID::ZERG_HATCHERY;
        }
        );

        if ( units.empty( ) ) {
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

    /*! @brief Called when a game has ended. */
    virtual void OnGameEnd ( ) { }

    /*! @brief In non realtime games this function gets called after each step
     * as indicated by step size. In realtime this function gets called as often
     * as possible after request/responses are received from the game gathering
     * observation state. */
    virtual void OnStep ( ) { }

    /*! @brief Called whenever one of the player's units has been destroyed.
     * @param unit The destroyed unit. */
    virtual void OnUnitDestroyed ( const Unit *unit ) { }

    /*! @brief Called when a neutral unit is created. For example, mineral
     * fields observed for the first time.
     * @param unit The observed unit. */
    virtual void OnNeutralUnitCreated ( const Unit *unit ) { }

    /*! @brief Called when a Unit has been created by the player.
     * @param unit The created unit. */
    virtual void OnUnitCreated ( const Unit *unit ) { }

    /*! @brief Called when a unit becomes idle, this will only occur as an event
     * so will only be called when the unit becomes idle and not a second time.
     * Being idle is defined by having orders in the previous step and not
     * currently having orders or if it did not exist in the previous step
     * and now does, a unit being created, for instance, will call both
     * OnUnitCreated and OnUnitIdle if it does not have a rally set.
     * @param unit The idle unit. */
    virtual void OnUnitIdle ( const Unit *unit ) { }

    /*! @brief Called when an upgrade is finished, warp gate, ground weapons,
     * baneling speed, etc.
     * @param upgrade The completed upgrade. */
    virtual void OnUpgradeCompleted ( UpgradeID upgrade ) { }

    /*! @brief Called when the unit in the previous step had a build progress
     * less than 1.0 but is greater than or equal to 1.0 in the current step.
     * @param unit The constructed unit. */
    virtual void OnBuildingConstructionComplete ( const Unit *unit ) { }

    /*! @brief Called when the unit in the current observation has lower health
     * or shields than in the previous observation.
     * @param {Unit*} unit The damaged unit.
     * @param unit The unit taking damage.
     * @param health The change in health (damage is positive)
     * @param shields The change in shields (damage is positive) */
    virtual void
        OnUnitDamaged ( const Unit *unit, float health, float shields ) { }

    /*! @brief Called when a nydus is placed. */
    virtual void OnNydusDetected ( ) { }

    /*! @brief Called when a nuclear launch is detected. */
    virtual void OnNuclearLaunchDetected ( ) { }

    /*! @brief Called when an enemy unit enters vision from out of fog of war.
     * @param unit The unit entering vision. */
    virtual void OnUnitEnterVision ( const Unit *unit ) { }

    /*! @brief Called for various errors the library can encounter.
     * @see ClientError enum for possible errors. */
    virtual void OnError (
        const vector<ClientError> &client_errors,
        const vector<string>      &protocol_errors = { }
    ) { }

    /*! @brief The ObservationInterface is used to query game state. */
    const ObservationInterface *Observation ( ) const {
        // TODO (?): Should this return a nullptr if the interface is not
        // valid (e.g., before a game is started)?
        return observation_face_.get( );
    }

    /*! @brief The UnitQuery interface is used to issue commands to units. */
    QueryInterface *Query ( ) const {
        // TODO (?): Should this return a nullptr if the interface is not
        // valid (e.g., before a game is started)?
        return query_face_.get( );
    }

    /*! @brief The DebugInterface allows a derived class to print text, draw
     * primitive shapes and spawn/destroy units. */
    DebugInterface *Debug ( ) const {
        return debug_face_.get( );
    }

    // TODO do something with this.
    /*! @brief The ControlInterface is only meant to be used by the
     * coordinator as it provides functionality for connecting to
     * StarCraft II, setting up a websocket connection and issuing blocking
     * commands via SC2's protocol. */

    // TODO refactor. What needs to be reset?
    virtual void Reset ( ) {
        // delete ctrl_face_;
        // ctrl_face_ = new ControlInterface ( *this );
    }

    virtual bool Connect (
        const string &address,
        const int     port,
        const int     timeout_ms
    ) {
        // Keep retrying the connection until the timeout is hit.
        bool         connected = false;
        unsigned int timeout_seconds =
            ( static_cast<unsigned int> ( timeout_ms ) + 1'500 ) / 1'000;
        if ( timeout_seconds < 1 ) {
            timeout_seconds = 1;
        }

        cout << "Connecting to " << address << ":" << port << "...\n";

        for ( unsigned int count_seconds = 0; count_seconds < timeout_seconds;
              ++count_seconds )
        {
            if ( ProtoFace::ConnectToGame ( address, port, timeout_ms ) ) {
                connected = true;
                break;
            }
            SleepFor ( 1'000 );
        }

        if ( !connected ) {
            cerr << "Unable to connect to game" << endl;
            return false;
        }

        cout << "Connected to " << address << ":" << port << '\n';

        return true;
    }

    /*! @brief Saves a binary blob as a map to a remote location.
     * @param data The map data.
     * @param data_size The size of map data.
     * @param remote_path The file path to save the data to.
     * @return Is true if the save is successful.
     * @see @c Coordinator::RemoteSaveMap */
    virtual bool RemoteSaveMap (
        const void *data,
        const int   data_size,
        string      remote_path
    ) {
        // Request.
        {
            const GameRequestPtr            request = ProtoFace::MakeRequest( );
            SC2APIProtocol::RequestSaveMap *request_save_map =
                request->mutable_save_map( );
            request_save_map->set_map_path ( remote_path );
            request_save_map->set_map_data ( data, data_size );

            if ( !ProtoFace::SendRequest ( request ) ) {
                return false;
            }
        }

        // Response.
        const GameResponsePtr response = WaitForResponse( );
        if ( !response.get( ) ) {
            return false;
        }

        if ( !response->has_save_map( ) ) {
            cerr << "Error in ResponseSaveMap" << endl;
            return false;
        }
        const SC2APIProtocol::ResponseSaveMap &response_save_game =
            response->save_map( );

        if ( response_save_game.has_error( ) ) {
            cerr << "RemoteSaveMap Error: "
                 << ResponseSaveMap_Error_Name ( response_save_game.error( ) )
                 << endl;
            response_save_game.PrintDebugString( );
            return false;
        }
        return true;
    }

    static void ResolveMap (
        const string                      &map_name,
        SC2APIProtocol::RequestCreateGame *request
    )
    {
        // BattleNet map
        if ( !HasExtension ( map_name, ".SC2Map" ) ) {
            request->set_battlenet_map_name ( map_name );
            return;
        }

        // Absolute path
        SC2APIProtocol::LocalMap *local_map = request->mutable_local_map( );
        if ( DoesFileExist ( map_name ) ) {
            local_map->set_map_path ( map_name );
            return;
        }

        // Relative path - Game maps directory
        const string game_relative =
            GetGameMapsDirectory ( ProtoFace::pi_.process_path ) + map_name;
        if ( DoesFileExist ( game_relative ) ) {
            local_map->set_map_path ( map_name );
            return;
        }

        // Relative path - Library maps directory
        if ( string library_relative = GetLibraryMapsDirectory( ) + map_name;
             DoesFileExist ( library_relative ) )
        {
            local_map->set_map_path ( library_relative );
            return;
        }

        // Relative path - Remotely saved maps directory
        local_map->set_map_path ( map_name );
    }

    virtual bool CreateGame (
        const string              &map_name,
        const vector<PlayerSetup> &players,
        const bool                 realtime
    ) {
        const GameRequestPtr               request = ProtoFace::MakeRequest( );
        SC2APIProtocol::RequestCreateGame *request_create_game =
            request->mutable_create_game( );
        ResolveMap ( map_name, request_create_game );
        for ( const PlayerSetup &setup : players ) {
            SC2APIProtocol::PlayerSetup *playerSetup =
                request_create_game->add_player_setup( );
            playerSetup->set_type (
                static_cast<SC2APIProtocol::PlayerType> ( setup.type )
            );
            playerSetup->set_race (
                static_cast<SC2APIProtocol::Race> (
                    static_cast<int> ( setup.race ) + 1
                )
            );
            playerSetup->set_player_name ( setup.player_name );
            playerSetup->set_difficulty (
                static_cast<SC2APIProtocol::Difficulty> ( setup.difficulty )
            );
            playerSetup->set_ai_build (
                static_cast<SC2APIProtocol::AIBuild> ( setup.ai_build )
            );
        }

        request_create_game->set_realtime ( realtime );

        if ( !ProtoFace::SendRequest ( request ) ) {
            return false;
        }

        const GameResponsePtr response = WaitForResponse( );
        if ( !response.get( ) ) {
            return false;
        }

        if ( !response->has_create_game( ) ) {
            cerr << "Error in ResponseCreateGame" << endl;
            return false;
        }

        const SC2APIProtocol::ResponseCreateGame &response_create_game =
            response->create_game( );

        bool success { true };
        if ( response_create_game.has_error( ) ) {
            string errorCode;
            switch ( response_create_game.error( ) ) {
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
                    // case
                    // SC2APIProtocol::ResponseCreateGame::MultiplayerUnsupported
                    // : {
                    //     errorCode = "Multiplayer Unsupported";
                    //     break;
                    // }

                default :
                    errorCode = "Unknown";
                    { break; }
            }

            cerr << "CreateGame request returned an error code: " << errorCode
                 << endl;
            success = false;
        }

        if ( response_create_game.has_error_details( ) &&
             response_create_game.error_details( ).length( ) > 0 )
        {
            cerr << "CreateGame request returned error details: "
                 << response_create_game.error_details( ) << endl;
            success = false;
        }

        return success;
    }

    virtual bool RequestJoinGame (
        PlayerSetup              setup,
        const InterfaceSettings &settings,
        const Ports             &ports,
        const bool               raw_affects_selection
    ) {
        observation_face_->ClearFlags( );

        is_multiplayer_ = ports.IsValid( );

        const GameRequestPtr             request = ProtoFace::MakeRequest( );
        SC2APIProtocol::RequestJoinGame *request_join_game =
            request->mutable_join_game( );

        request_join_game->set_race (
            static_cast<SC2APIProtocol::Race> (
                static_cast<int> ( setup.race ) + 1
            )
        );
        request_join_game->set_player_name ( setup.player_name );

        if ( is_multiplayer_ ) {
            // Set shared port.
            request_join_game->set_shared_port ( ports.shared_port );

            // Set server ports.
            SC2APIProtocol::PortSet *server_ports =
                request_join_game->mutable_server_ports( );
            server_ports->set_game_port ( ports.server_ports.game_port );
            server_ports->set_base_port ( ports.server_ports.base_port );

            // Set client ports. Right now only 1v1 is supported.
            for ( const PortSet &client_ports : ports.client_ports ) {
                SC2APIProtocol::PortSet *client_port =
                    request_join_game->add_client_ports( );
                client_port->set_game_port ( client_ports.game_port );
                client_port->set_base_port ( client_ports.base_port );
            }
        }

        SC2APIProtocol::InterfaceOptions *options =
            request_join_game->mutable_options( );

        options->set_raw ( true );
        options->set_score ( true );
        options->set_show_cloaked ( true );
        options->set_show_burrowed_shadows ( true );
        options->set_show_placeholders ( true );

        // If raw_affects_selection == true, will not generate a deselect
        // command after sending a command to a unit
        options->set_raw_affects_selection ( raw_affects_selection );

        if ( settings.use_feature_layers ) {
            SC2APIProtocol::SpatialCameraSetup *setupProto =
                options->mutable_feature_layer( );
            setupProto->set_width (
                settings.feature_layer_settings.camera_width
            );
            SC2APIProtocol::Size2DI *resolution =
                setupProto->mutable_resolution( );
            resolution->set_x ( settings.feature_layer_settings.map_x );
            resolution->set_y ( settings.feature_layer_settings.map_y );
            SC2APIProtocol::Size2DI *minimap_resolution =
                setupProto->mutable_minimap_resolution( );
            minimap_resolution->set_x (
                settings.feature_layer_settings.minimap_x
            );
            minimap_resolution->set_y (
                settings.feature_layer_settings.minimap_y
            );
        }
        if ( settings.use_render ) {
            SC2APIProtocol::SpatialCameraSetup *setupProto =
                options->mutable_render( );
            SC2APIProtocol::Size2DI *resolution =
                setupProto->mutable_resolution( );
            resolution->set_x ( settings.render_settings.map_x );
            resolution->set_y ( settings.render_settings.map_y );
            SC2APIProtocol::Size2DI *minimap_resolution =
                setupProto->mutable_minimap_resolution( );
            minimap_resolution->set_x ( settings.render_settings.minimap_x );
            minimap_resolution->set_y ( settings.render_settings.minimap_y );
        }

        return ProtoFace::SendRequest ( request );
    }

    virtual bool WaitJoinGame ( ) {
        cout << "Waiting for the JoinGame response." << '\n';
        const GameResponsePtr response = WaitForResponse( );
        if ( !response.get( ) ) {
            cout << "Did not get a JoinGame response." << '\n';
            return false;
        }
        if ( !response->has_join_game( ) ) {
            cout << "Response received is not JoinGame response." << '\n';
            return false;
        }

        if ( response->error_size( ) > 0 ) {
            cout << "Error in joining the game." << '\n';
            assert ( 0 );
            return false;
        }

        observation_face_->player_id_ = response->join_game( ).player_id( );

        cout << "WaitJoinGame finished successfully." << '\n';
        return true;
    }

    virtual bool RequestLeaveGame ( ) {
        if ( !is_multiplayer_ ) {
            return false;
        }

        const GameRequestPtr request = ProtoFace::MakeRequest( );
        request->mutable_leave_game( );
        return ProtoFace::SendRequest ( request );
    }

    virtual bool PollLeaveGame ( ) {
        if ( !is_multiplayer_ ) {
            return false;
        }

        if ( ProtoFace::GetResponsePending( ) !=
             SC2APIProtocol::Response::kLeaveGame )
        {
            /* If not in a game, then it is in the end state trying to leave the
             * game. */
            if ( HasResponsePending( ) )
                Error::Log ( ClientError::ResponseNotConsumed );
            return !IsInGame( );
        }

        // React to receiving a leave response.
        if ( !PollResponse( ) ) {
            return true;
        }

        // Wait for the end response to be received before proceeding.
        // TODO (?): Add error handling.
        WaitForResponse( );
        return true;
    }

    virtual bool Step ( const int count ) {
        if ( app_state != AppState::Normal ) {
            return false;
        }

        const GameRequestPtr         request = ProtoFace::MakeRequest( );
        SC2APIProtocol::RequestStep *step    = request->mutable_step( );
        step->set_count ( count );
        return ProtoFace::SendRequest ( request );
    }

    virtual bool WaitStep ( ) {
        const GameResponsePtr response = WaitForResponse( );
        if ( !response.get( ) || !response->has_step( ) ||
             response->error_size( ) > 0 )
        {
            return false;
        }

        return GetObservation( );
    } // Step

    virtual bool SaveReplay ( const string &path ) {
        const GameRequestPtr request = ProtoFace::MakeRequest( );
        request->mutable_save_replay( );
        if ( !ProtoFace::SendRequest ( request ) ) {
            return false;
        }

        const GameResponsePtr response = WaitForResponse( );
        if ( !response.get( ) || !response->has_save_replay( ) ||
             response->error_size( ) > 0 )
        {
            return false;
        }

        const SC2APIProtocol::ResponseSaveReplay &response_replay =
            response->save_replay( );

        if ( response_replay.data( ).empty( ) ) {
            return false;
        }

        ofstream file;
        file.open ( path, fstream::binary );
        if ( !file.is_open( ) ) {
            return false;
        }

        file.write (
            &response_replay.data( )[0],
            response_replay.data( ).size( )
        );
        return true;
    }

    virtual bool Ping ( ) {
        return ProtoFace::PingGame( );
    }

    // General.
    virtual GameResponsePtr WaitForResponse ( ) {
        assert ( app_state == AppState::Normal );

        GameResponsePtr response = ProtoFace::WaitForResponseInternal( );

        if ( response.get( ) && response->error_size( ) < 1 ) {
            // Everything is good. No need for any error handling.
            return response;
        }

        if ( response.get( ) && response->error_size( ) > 0 ) {
            vector<string> errors;
            for ( int i = 0; i < response->error_size( ); ++i ) {
                errors.push_back ( response->error ( i ) );
            }

            Error::Log ( ClientError::SC2ProtocolError, errors );
            return response;
        }
        assert ( !response.get( ) );

        // The game application did not responded, the previous request was
        // either not sent or the app is non-responsive.

        // Step 1: distinguish between a hang and a crash. Lots of time has
        // elapsed, so if there was a crash it should have finished by now.
        assert ( ProtoFace::pi_.process_id );
        if ( !IsProcessRunning ( ProtoFace::pi_.process_id ) ) {
            app_state = AppState::Crashed;
            cout << "Game application has terminated unexpectedly." << '\n';
            Error::Log ( ClientError::SC2AppFailure );
            return response;
        }

        // Step 2: distinguish between a non-responsive app and a failure to
        // deliver a valid request.
        {
            const GameRequestPtr ping_request = ProtoFace::MakeRequest( );
            ping_request->mutable_ping( );

            if ( !ProtoFace::SendRequest ( ping_request, true ) ) {
                // Mark the game app as unresponsive.
                app_state = AppState::Timeout;
                Error::Log ( ClientError::SC2ProtocolTimeout );
            } else {
                // Wait for a ping response. If this fails, the game is
                // unresponsive.
                // TODO (?): Implement a timeout parameter for this wait.
                const GameResponsePtr response_ping =
                    ProtoFace::WaitForResponseInternal( );
                if ( response_ping ) {
                    if ( ProtoFace::GetLastStatus( ) ==
                         SC2APIProtocol::Status::unknown )
                    {
                        Error::Log ( ClientError::SC2UnknownStatus );
                    }

                    // The game is responsive, but there was another problem.
                    // This isn't the right place to handle another type of
                    // problem. Just return the nullptr.
                    Error::Log ( ClientError::SC2UnknownStatus );
                    return response;
                }

                app_state = AppState::Timeout;
                Error::Log ( ClientError::SC2ProtocolTimeout );
            }
        }

        // The game application has hanged. Try and terminate it.
        app_state = AppState::Timeout;
        for ( int i = 0;
              i < 10 && IsProcessRunning ( ProtoFace::pi_.process_id );
              ++i )
        {
            TerminateProcess ( ProtoFace::pi_.process_id );
            SleepFor ( 2'000 );
        }

        if ( IsProcessRunning ( ProtoFace::pi_.process_id ) ) {
            // Failed to kill the running process.
            app_state = AppState::Timeout_Zombie;
        }

        cout << "Game application has been terminated due to unresponsiveness."
             << '\n';
        Error::Log ( ClientError::SC2AppFailure );
        return response;
    }

    virtual void SetProcessInfo ( const ProcessInfo &pi ) {
        ProtoFace::pi_ = pi;
    }

    virtual const ProcessInfo &GetProcessInfo ( ) const {
        return ProtoFace::pi_;
    }

    // Game status.
    virtual SC2APIProtocol::Status GetLastStatus ( ) const {
        return ProtoFace::GetLastStatus( );
    }

    virtual AppState GetAppState ( ) const {
        return app_state;
    }

    virtual bool IsInGame ( ) const {
        if ( app_state != AppState::Normal ) {
            return false;
        }

        return GetLastStatus( ) == SC2APIProtocol::Status::in_game ||
               GetLastStatus( ) == SC2APIProtocol::Status::in_replay;
    }

    virtual bool IsFinishedGame ( ) const {
        if ( app_state != AppState::Normal ) {
            return true;
        }

        if ( IsInGame( ) ) {
            return false;
        }

        if ( HasResponsePending( ) ) {
            return false;
        }

        return true;
    }

    virtual bool IsReadyForCreateGame ( ) const {
        if ( app_state != AppState::Normal ) {
            return false;
        }

        // Make sure the pipes are clear first.
        if ( HasResponsePending( ) ) {
            return false;
        }

        // TODO (?): For multiplayer, it may be possible to be in the ended
        // state but not yet left the game. Must leave the game before create
        // game can be ready again.
        return GetLastStatus( ) == SC2APIProtocol::Status::launched ||
               GetLastStatus( ) == SC2APIProtocol::Status::ended;
    }

    virtual bool HasResponsePending ( ) const {
        return ProtoFace::HasResponsePending( );
    }

    virtual bool GetObservation ( ) {
        if ( app_state != AppState::Normal ) {
            return false;
        }

        const GameRequestPtr request = ProtoFace::MakeRequest( );
        request->mutable_observation( );
        if ( !ProtoFace::SendRequest ( request ) ) {
            return false;
        }

        const GameResponsePtr  response = WaitForResponse( );
        ResponseObservationPtr response_observation;
        SET_MESSAGE_RESPONSE ( response_observation, response, observation );
        if ( response_observation.HasErrors( ) ) {
            cerr << '\n' << "Error in returning observation:" << '\n';
            cerr << "The main response is of type: "
                 << std::to_string ( response->response_case( ) ) << '\n';
            if ( response_observation.HasResponse( ) ) {
                cerr << "There is no ResponseObservation/message!" << '\n';
            }
            if ( response->error_size( ) > 0 ) {
                for ( int i = 0; i < response->error_size( ); ++i ) {
                    cerr << "Error string: " << response->error ( i ) << '\n';
                }
            } else {
                cerr << "No error strings in result." << '\n';
            }
            cerr << endl;
            return false;
        }

        ObservationPtr observation;
        SET_SUBMESSAGE_RESPONSE (
            observation,
            response_observation,
            observation
        );
        if ( observation.HasErrors( ) ) {
            return false;
        }

        observation_ = observation;
        response_    = response_observation;

        observation_face_->UpdateObservation( );

        return true;
    }

    virtual bool PollResponse ( ) {
        return ProtoFace::PollResponse( );
    }

    virtual bool ConsumeResponse ( ) {
        const GameResponsePtr response = WaitForResponse( );
        return response.get( );
    }

    virtual bool IssueEvents ( const Tags &commands = { } ) {
        if ( observation_face_->current_game_loop_ ==
             observation_face_->previous_game_loop )
        {
            return false;
        }

        IssueUnitDestroyedEvents( );
        IssueUnitAddedEvents( );
        IssueBuildingCompletedEvents( );
        IssueIdleEvents ( commands );
        IssueUpgradeEvents( );
        IssueAlertEvents( );
        IssueUnitDamagedEvents( );

        // Run the users OnStep function after events have been issued.
        OnStep( );

        return true;
    }

    void IssueUnitDestroyedEvents ( ) {
        if ( !observation_->has_raw_data( ) ) {
            return;
        }

        if ( const SC2APIProtocol::ObservationRaw &raw =
                 observation_->raw_data( );
             raw.has_event( ) )
        {
            for ( const SC2APIProtocol::Event &event = raw.event( );
                  const uint64_t              &tag : event.dead_units( ) )
            {
                const Unit *unit =
                    observation_face_->unit_pool_.GetUnit ( tag );

                if ( !unit ) {
                    continue;
                }

                observation_face_->unit_pool_.MarkDead ( tag );
                OnUnitDestroyed ( unit );
            }
        }
    }

    void IssueUnitAddedEvents ( ) {
        for ( const Unit *unit : observation_face_->unit_pool_.GetNewUnits( ) )
        {
            if ( unit->alliance == Unit::Alliance::Self ) {
                OnUnitCreated ( unit );
            } else if (
                unit->alliance == Unit::Alliance::Neutral &&
                unit->display_type == Unit::DisplayType::Visible
            )
            {
                OnNeutralUnitCreated ( unit );
            }
        }

        for ( const Unit *unit :
              observation_face_->unit_pool_.GetUnitsEnteringVision( ) )
        {
            if ( unit->alliance == Unit::Alliance::Enemy &&
                 unit->display_type == Unit::DisplayType::Visible )
            {
                OnUnitEnterVision ( unit );
            }
        }
    }

    void IssueIdleEvents ( const Tags &commands ) {
        auto &unit_pool = observation_face_->unit_pool_;
        // identify idled units where commands were issued last step, but units
        // have no orders now (maybe failed, maybe executed instantly)
        for ( const auto tag : commands ) {
            if ( const auto *unit = unit_pool.GetExistingUnit ( tag );
                 unit && unit->orders.empty( ) )
            {
                unit_pool.AddUnitIdled ( unit );
            }
        }

        // add newly created units (if they are completed)
        for ( const auto *u : unit_pool.GetNewUnits( ) ) {
            if ( u->build_progress >= 1.0F && u->orders.empty( ) ) {
                unit_pool.AddUnitIdled ( u );
            }
        }

        // send only one idle event for any unit in any frame
        for ( const auto *u : unit_pool.GetIdledUnits( ) ) {
            OnUnitIdle ( u );
        }
    }

    void IssueBuildingCompletedEvents ( ) {
        for ( const Unit *unit :
              observation_face_->unit_pool_.GetCompletedBuildings( ) )
        {
            if ( unit->alliance == Unit::Alliance::Self ) {
                OnBuildingConstructionComplete ( unit );
            }
        }
    }

    void IssueUnitDamagedEvents ( ) {
        for ( const auto &[unit, health, shields] :
              observation_face_->unit_pool_.GetDamagedUnits( ) )
        {
            OnUnitDamaged ( unit, health, shields );
        }
    }

    void IssueAlertEvents ( ) {
        // Iterate the alerts and issue relevant events.
        for ( const auto alert : observation_->alerts( ) ) {
            switch ( alert ) {
                case SC2APIProtocol::Alert::NuclearLaunchDetected : {
                    OnNuclearLaunchDetected( );
                    break;
                }
                case SC2APIProtocol::Alert::NydusWormDetected : {
                    OnNydusDetected( );
                    break;
                }
                default : {
                    break;
                }
            }
        }
    }

    void IssueUpgradeEvents ( ) {
        set<uint32_t> previous;
        for ( UpgradeID upgrade : observation_face_->upgrades_previous_ ) {
            previous.insert ( upgrade );
        }

        for ( UpgradeID upgrade : observation_face_->upgrades_ ) {
            if ( !previous.contains ( upgrade ) ) {
                OnUpgradeCompleted ( upgrade );
            }
        }
    }

    // Diagnostic.
    static void DumpProtoUsage ( ) {
        const vector<uint32_t> &stats = ProtoFace::GetStats( );
        cout << "******************************************************"
             << '\n';
        cout << "Protocol use by message type:" << '\n';
        for ( size_t i = 0; i < stats.size( ); ++i ) {
            if ( stats[i] == 0 ) {
                continue;
            }

            cout << std::to_string ( i ) << ": " << std::to_string ( stats[i] )
                 << '\n';
        }

        cout << "******************************************************"
             << '\n';
    }

    const vector<ClientError> &GetClientErrors ( ) const {
        return client_errors_;
    }

    vector<string> GetProtocolErrors ( ) const {
        return protocol_errors_;
    }

    void ClearClientErrors ( ) {
        client_errors_.clear( );
    }

    void ClearProtocolErrors ( ) {
        protocol_errors_.clear( );
    }

    void UseGeneralizedAbility ( const bool value ) const {
        observation_face_->use_generalized_ability_ = value;
    }

    // Save/Load.
    void Save ( ) {
        const GameRequestPtr request = ProtoFace::MakeRequest( );
        request->mutable_quick_save( );
        if ( !ProtoFace::SendRequest ( request ) ) {
            return;
        }
        WaitForResponse( );
    }

    void Load ( ) {
        const GameRequestPtr request = ProtoFace::MakeRequest( );
        request->mutable_quick_load( );
        if ( !ProtoFace::SendRequest ( request ) ) {
            return;
        }
        WaitForResponse( );
    }

}; // Class Client

} // namespace sc2
