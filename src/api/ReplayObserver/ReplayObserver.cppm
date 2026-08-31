module;
#include <iostream>
#include <string>

#include <s2clientprotocol/sc2api.pb.h>
export module ReplayObserver;
import Client;
import observer_action_interface;
import protocol_interface;
import common;
import error_handler;
import game_settings;
import game_types;
import proto_to_pods;


export namespace sc2 {
using namespace std;


//! A client for running a replay.
class ReplayObserver : public Client {
public:
    ReplayInfo replay_info_;

    ReplayObserver ( )
          : observer_action_interface_ ( new ObserverActionInterface( ) ) {}

    ~ReplayObserver ( ) override {
        delete observer_action_interface_;
    }

    /*! @brief Obtains the observer action interface.
     * @return The observer action interface. */
    ObserverActionInterface* ObserverAction ( ) const {
        return observer_action_interface_;
    }

    /*! @brief Determines if the replay should be filtered out.
     * @param replay_info Replay information used to decide if the replay should
     * be filtered.
     * @param player_id
     * @returns If TRUE, the replay will be rejected and not analyzed. */
    static bool
        IgnoreReplay ( const ReplayInfo& replay_info, uint32_t /*player_id*/ ) {
        // Ignore games less than 30 seconds.
        return replay_info.duration < 30.0f;
    }

    void Reset ( ) override {
        Client::Reset( );
        delete observer_action_interface_;
        observer_action_interface_ = new ObserverActionInterface( );
    }

    bool GatherReplayInfo ( const string& path, bool download_data = false ) {
        replay_info_.num_players = 0;

        // Request the replay info.
        const GameRequestPtr               request = ProtoFace::MakeRequest( );
        SC2APIProtocol::RequestReplayInfo* request_replay_info =
            request->mutable_replay_info( );
        request_replay_info->set_replay_path ( path );
        request_replay_info->set_download_data ( download_data );
        if ( !ProtoFace::SendRequest ( request ) ) {
            return false;
        }

        // Check that the response is properly filled out.
        const GameResponsePtr response = ProtoFace::WaitForResponse( );
        if ( !response ) {
            cerr << "No response to replay info query!" << '\n';
            return false;
        }

        if ( !response->has_replay_info( ) ) {
            for ( auto e : response->error( ) ) {
                cout << e << '\n';
            }
            cerr << "Replay info expected and not returned: "
                 << response->DebugString( ) << '\n';
            return false;
        }

        const SC2APIProtocol::ResponseReplayInfo& proto_replay_info =
            response->replay_info( );

        if ( proto_replay_info.has_error( ) ) {
            const SC2APIProtocol::ResponseReplayInfo_Error err =
                proto_replay_info.error( );
            cerr << "ResponseReplayInfo: replay info contains an error: "
                 << to_string ( err ) << '\n';

            if ( proto_replay_info.has_error_details( ) ) {
                cerr << "ResponseReplayInfo: error details: "
                     << proto_replay_info.error_details( ) << '\n';
            }

            return false;
        }

        const string map_name     = proto_replay_info.map_name( );
        const string map_path     = proto_replay_info.local_map_path( );
        const string version      = proto_replay_info.game_version( );
        const string data_version = proto_replay_info.data_version( );

        if ( map_name.length( ) >= max_path_size ) {
            cerr << "Map name is too long: " << map_name << '\n';
            return false;
        }
        if ( map_path.length( ) >= max_path_size ) {
            cerr << "Map path is too long: " << map_path << '\n';
            return false;
        }
        if ( version.length( ) >= max_version_size ) {
            cerr << "Version string is too long: " << version << '\n';
            return false;
        }

        replay_info_.map_name     = map_name.c_str( );
        replay_info_.map_path     = map_path.c_str( );
        replay_info_.replay_path  = path.c_str( );
        replay_info_.version      = version.c_str( );
        replay_info_.data_version = data_version.c_str( );

        replay_info_.duration = proto_replay_info.game_duration_seconds( );
        replay_info_.duration_gameloops =
            proto_replay_info.game_duration_loops( );

        replay_info_.data_build = proto_replay_info.data_build( );
        replay_info_.base_build = proto_replay_info.base_build( );

        for ( int i = 0; i < proto_replay_info.player_info_size( ); ++i ) {
            const SC2APIProtocol::PlayerInfoExtra& player_info_extra_proto =
                proto_replay_info.player_info ( i );
            ReplayPlayerInfo player_info;

            if ( player_info_extra_proto.has_player_info( ) ) {
                const SC2APIProtocol::PlayerInfo& player_info_proto =
                    player_info_extra_proto.player_info( );
                player_info.player_id = player_info_proto.player_id( );
                if ( player_info_proto.has_race_actual( ) ) {
                    player_info.race = ConvertRaceFromProto (
                        player_info_proto.race_actual( )
                    );
                }
                if ( player_info_proto.has_race_requested( ) ) {
                    player_info.race_selected = ConvertRaceFromProto (
                        player_info_proto.race_requested( )
                    );
                }
            }

            player_info.mmr = player_info_extra_proto.player_mmr( );
            player_info.apm = player_info_extra_proto.player_apm( );

            if ( player_info_extra_proto.has_player_result( ) ) {
                if ( const SC2APIProtocol::PlayerResult& player_result_proto =
                         player_info_extra_proto.player_result( );
                     player_result_proto.has_result( ) )
                {
                    player_info.game_result = ConvertGameResultFromProto (
                        player_result_proto.result( )
                    );
                }
            }

            if ( replay_info_.num_players >= max_num_players ) {
                // Something went wrong, too many players.
                return false;
            }

            replay_info_.players[replay_info_.num_players] = player_info;
            ++replay_info_.num_players;
        }

        return true;
    }

    static bool LoadReplay (
        const string&            replay_path,
        const InterfaceSettings& settings,
        uint32_t                 player_id,
        bool                     realtime = false
    ) {
        // Send the request.
        const GameRequestPtr                request = ProtoFace::MakeRequest( );
        SC2APIProtocol::RequestStartReplay* start_replay_request =
            request->mutable_start_replay( );
        start_replay_request->set_replay_path ( replay_path );
        start_replay_request->set_observed_player_id ( player_id );
        start_replay_request->set_realtime ( realtime );

        SC2APIProtocol::InterfaceOptions* options =
            start_replay_request->mutable_options( );

        options->set_raw ( true );
        options->set_score ( true );
        options->set_show_cloaked ( true );
        options->set_show_burrowed_shadows ( true );
        options->set_show_placeholders ( true );
        options->set_raw_affects_selection ( false );

        if ( settings.use_feature_layers ) {
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
        if ( settings.use_render ) {
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

        if ( !ProtoFace::SendRequest ( request ) ) {
            cerr << "LoadReplay: load replay request failed." << '\n';
            Assert ( false );
            return false;
        }

        return true;
    }

    bool WaitForReplay ( ) {
        // Wait for a response.
        const GameResponsePtr response = ProtoFace::WaitForResponse( );
        if ( !response.get( ) ) {
            cerr << "WaitForReplay: timed out, did not receive any response."
                 << '\n';
            Assert ( false );
            return false;
        }

        if ( !response->has_start_replay( ) ) {
            cerr << "WaitForReplay: received the wrong type of response: "
                 << to_string (
                        static_cast<int> ( response->response_case( ) )
                    )
                 << '\n';
            Assert ( false );
            return false;
        }

        if ( const SC2APIProtocol::ResponseStartReplay& response_replay =
                 response->start_replay( );
             response_replay.has_error( ) )
        {
            const SC2APIProtocol::ResponseStartReplay_Error err =
                response_replay.error( );
            cerr << "WaitForReplay: start replay contains an error: "
                 << to_string ( err ) << '\n';
            if ( response_replay.has_error_details( ) )
                cerr << "WaitForReplay: error details: "
                     << response_replay.error_details( ) << '\n';
            return false;
        }

        Assert ( IsInGame( ) );
        if ( !IsInGame( ) ) {
            cerr << "WaitForReplay: not in a game." << '\n';
            return false;
        }

        if ( replay_info_.replay_path.empty( ) ) {
            Assert ( false );
            cout << "WaitForReplay: new replay loaded, replay path unknown"
                 << '\n';
            return true;
        }

        GetObservation( );
        this->Client::OnGameStart( );
        OnGameStart( );

        cout << "Replaying: '" << replay_info_.replay_path << "'" << '\n';
        return true;
    }

    static void UseGeneralizedAbility ( bool value ) {
        UseGeneralizedAbility ( value );
    }

    const ReplayInfo& GetReplayInfo ( ) const {
        return replay_info_;
    }

private:
    ObserverActionInterface* observer_action_interface_;
}; // ReplayObserver

} // namespace sc2
