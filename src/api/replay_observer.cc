#include <iostream>

#include "replay_observer.h"
#include "control_interfaces.h"
#include "interfaces.h"
#include "proto_to_pods.h"
#include "lib/game_settings.h"

namespace sc2 {
//-------------------------------------------------------------------------------------------------
// ReplayObserver: An implementation of ReplayControlInterface.
//-------------------------------------------------------------------------------------------------

class ReplayControlImpl : public ReplayControlInterface {
    public:
        ReplayInfo replay_info_;
        ControlInterface* control_interface_;
        ReplayObserver* replay_observer_;

        ReplayControlImpl(ControlInterface* control_interface, ReplayObserver* replay_observer);

        virtual bool GatherReplayInfo(const std::string& path, bool download_data);
        virtual bool LoadReplay(const std::string& replay_path, const InterfaceSettings& settings, uint32_t player_id,
                                bool realtime = false);
        virtual bool WaitForReplay();
        virtual void UseGeneralizedAbility(bool value);

        virtual const ReplayInfo& GetReplayInfo() const;
};

ReplayControlImpl::ReplayControlImpl(ControlInterface* control_interface, ReplayObserver* replay_observer)
    : control_interface_(control_interface), replay_observer_(replay_observer) {}

bool ReplayControlImpl::GatherReplayInfo(const std::string& path, bool download_data) {
    replay_info_.num_players = 0;

    // Request the replay info.
    const GameRequestPtr request = control_interface_->Proto().MakeRequest();
    SC2APIProtocol::RequestReplayInfo* request_replay_info = request->mutable_replay_info();
    request_replay_info->set_replay_path(path);
    request_replay_info->set_download_data(download_data);
    if (!control_interface_->Proto().SendRequest(request))
    {
        return false;
    }

    // Check that the response is properly filled out.
    const GameResponsePtr response = control_interface_->WaitForResponse();
    if (!response)
    {
        std::cerr << "No response to replay info query!" << '\n';
        return false;
    }

    if (!response->has_replay_info())
    {
        for (auto e : response->error())
        {
            std::cout << e << '\n';
        }
        std::cerr << "Replay info expected and not returned: " << response->DebugString() << '\n';
        return false;
    }

    const SC2APIProtocol::ResponseReplayInfo& proto_replay_info = response->replay_info();

    if (proto_replay_info.has_error())
    {
        const SC2APIProtocol::ResponseReplayInfo_Error err = proto_replay_info.error();
        std::cerr << "ResponseReplayInfo: replay info contains an error: " << std::to_string(err)
                << '\n';

        if (proto_replay_info.has_error_details())
        {
            std::cerr << "ResponseReplayInfo: error details: " << proto_replay_info.error_details() << '\n';
        }

        return false;
    }

    const std::string map_name = proto_replay_info.map_name();
    const std::string map_path = proto_replay_info.local_map_path();
    const std::string version = proto_replay_info.game_version();
    const std::string data_version = proto_replay_info.data_version();

    if (map_name.length() >= max_path_size)
    {
        std::cerr << "Map name is too long: " << map_name << '\n';
        return false;
    }
    if (map_path.length() >= max_path_size)
    {
        std::cerr << "Map path is too long: " << map_path << '\n';
        return false;
    }
    if (version.length() >= max_version_size)
    {
        std::cerr << "Version string is too long: " << version << '\n';
        return false;
    }

    replay_info_.map_name = map_name.c_str();
    replay_info_.map_path = map_path.c_str();
    replay_info_.replay_path = path.c_str();
    replay_info_.version = version.c_str();
    replay_info_.data_version = data_version.c_str();

    replay_info_.duration = proto_replay_info.game_duration_seconds();
    replay_info_.duration_gameloops = proto_replay_info.game_duration_loops();

    replay_info_.data_build = proto_replay_info.data_build();
    replay_info_.base_build = proto_replay_info.base_build();

    for (int i = 0; i < proto_replay_info.player_info_size(); ++i)
    {
        const SC2APIProtocol::PlayerInfoExtra& player_info_extra_proto = proto_replay_info.player_info(i);
        ReplayPlayerInfo player_info;

        if (player_info_extra_proto.has_player_info())
        {
            const SC2APIProtocol::PlayerInfo& player_info_proto = player_info_extra_proto.player_info();
            player_info.player_id = player_info_proto.player_id();
            if (player_info_proto.has_race_actual())
            {
                player_info.race = ConvertRaceFromProto(player_info_proto.race_actual());
            }
            if (player_info_proto.has_race_requested())
            {
                player_info.race_selected = ConvertRaceFromProto(player_info_proto.race_requested());
            }
        }

        player_info.mmr = player_info_extra_proto.player_mmr();
        player_info.apm = player_info_extra_proto.player_apm();

        if (player_info_extra_proto.has_player_result())
        {
            if (const SC2APIProtocol::PlayerResult& player_result_proto = player_info_extra_proto.player_result();
                player_result_proto.has_result())
            {
                player_info.game_result = ConvertGameResultFromProto(player_result_proto.result());
            }
        }

        if (replay_info_.num_players >= max_num_players)
        {
            // Something went wrong, too many players.
            return false;
        }

        replay_info_.players[replay_info_.num_players] = player_info;
        ++replay_info_.num_players;
    }

    return true;
}

bool ReplayControlImpl::LoadReplay(const std::string& replay_path, const InterfaceSettings& settings,
                                   uint32_t player_id,
                                   bool realtime) {
    // Send the request.
    const GameRequestPtr request = control_interface_->Proto().MakeRequest();
    SC2APIProtocol::RequestStartReplay* start_replay_request = request->mutable_start_replay();
    start_replay_request->set_replay_path(replay_path);
    start_replay_request->set_observed_player_id(player_id);
    start_replay_request->set_realtime(realtime);

    SC2APIProtocol::InterfaceOptions* options = start_replay_request->mutable_options();

    options->set_raw(true);
    options->set_score(true);
    options->set_show_cloaked(true);
    options->set_show_burrowed_shadows(true);
    options->set_show_placeholders(true);
    options->set_raw_affects_selection(false);

    if (settings.use_feature_layers)
    {
        SC2APIProtocol::SpatialCameraSetup* setupProto = options->mutable_feature_layer();
        setupProto->set_width(settings.feature_layer_settings.camera_width);
        SC2APIProtocol::Size2DI* resolution = setupProto->mutable_resolution();
        resolution->set_x(settings.feature_layer_settings.map_x);
        resolution->set_y(settings.feature_layer_settings.map_y);
        SC2APIProtocol::Size2DI* minimap_resolution = setupProto->mutable_minimap_resolution();
        minimap_resolution->set_x(settings.feature_layer_settings.minimap_x);
        minimap_resolution->set_y(settings.feature_layer_settings.minimap_y);
    }
    if (settings.use_render)
    {
        SC2APIProtocol::SpatialCameraSetup* setupProto = options->mutable_render();
        SC2APIProtocol::Size2DI* resolution = setupProto->mutable_resolution();
        resolution->set_x(settings.render_settings.map_x);
        resolution->set_y(settings.render_settings.map_y);
        SC2APIProtocol::Size2DI* minimap_resolution = setupProto->mutable_minimap_resolution();
        minimap_resolution->set_x(settings.render_settings.minimap_x);
        minimap_resolution->set_y(settings.render_settings.minimap_y);
    }

    if (!control_interface_->Proto().SendRequest(request))
    {
        std::cerr << "LoadReplay: load replay request failed." << '\n';
        assert(0);
        return false;
    }

    return true;
}

bool ReplayControlImpl::WaitForReplay() {
    // Wait for a response.
    const GameResponsePtr response = control_interface_->WaitForResponse();
    if (!response.get())
    {
        std::cerr << "WaitForReplay: timed out, did not receive any response." << '\n';
        assert(0);
        return false;
    }

    if (!response->has_start_replay())
    {
        std::cerr << "WaitForReplay: received the wrong type of response: "
                << std::to_string(static_cast<int>(response->response_case())) << '\n';
        assert(0);
        return false;
    }

    if (const SC2APIProtocol::ResponseStartReplay& response_replay = response->start_replay();
        response_replay.has_error())
    {
        const SC2APIProtocol::ResponseStartReplay_Error err = response_replay.error();
        std::cerr << "WaitForReplay: start replay contains an error: " << std::to_string(err) << '\n';
        if (response_replay.has_error_details())
            std::cerr << "WaitForReplay: error details: " << response_replay.error_details() << '\n';
        return false;
    }

    assert(control_interface_->IsInGame());
    if (!control_interface_->IsInGame())
    {
        std::cerr << "WaitForReplay: not in a game." << '\n';
        return false;
    }

    if (replay_info_.replay_path.empty())
    {
        assert(0);
        std::cout << "WaitForReplay: new replay loaded, replay path unknown" << '\n';
        return true;
    }

    control_interface_->GetObservation();
    replay_observer_->Control()->OnGameStart();
    replay_observer_->OnGameStart();

    std::cout << "Replaying: '" << replay_info_.replay_path << "'" << '\n';
    return true;
}

void ReplayControlImpl::UseGeneralizedAbility(bool value) {
    control_interface_->UseGeneralizedAbility(value);
}

const ReplayInfo& ReplayControlImpl::GetReplayInfo() const {
    return replay_info_;
}

//-------------------------------------------------------------------------------------------------
// ObserverActionImp: an implementation of an ObserverActionInterface.
//-------------------------------------------------------------------------------------------------

class ObserverActionImpl : public ObserverActionInterface {
    public:
        ControlInterface* control_;
        GameRequestPtr request_;

        explicit ObserverActionImpl(ControlInterface* control);

        SC2APIProtocol::RequestObserverAction* GetRequest();

        virtual void CameraMove(const Point2D& point, float distance = 0.0F) final;

        virtual void CameraFollowPlayer() final;

        virtual void SendActions() final;
};

ObserverActionImpl::ObserverActionImpl(ControlInterface* control) : control_(control) {}

SC2APIProtocol::RequestObserverAction* ObserverActionImpl::GetRequest() {
    if (request_ == nullptr)
    {
        request_ = control_->Proto().MakeRequest();
    }
    return request_->mutable_obs_action();
}

void ObserverActionImpl::CameraMove(const Point2D& point, float distance) {
    SC2APIProtocol::RequestObserverAction* request = GetRequest();
    SC2APIProtocol::ObserverAction* action = request->add_actions();
    SC2APIProtocol::ActionObserverCameraMove* camera_move = action->mutable_camera_move();
    camera_move->set_distance(distance);
    camera_move->mutable_world_pos()->set_x(point.x);
    camera_move->mutable_world_pos()->set_y(point.y);
}

void ObserverActionImpl::CameraFollowPlayer() {
    SC2APIProtocol::RequestObserverAction* request = GetRequest();
    SC2APIProtocol::ObserverAction* action = request->add_actions();
    action->mutable_camera_follow_player();
}

void ObserverActionImpl::SendActions() {
    if (request_ == nullptr)
    {
        return;
    }

    if (!control_->Proto().SendRequest(request_))
    {
        return;
    }

    request_ = nullptr;
    control_->WaitForResponse();
}

//-------------------------------------------------------------------------------------------------
// ReplayObserver.
//-------------------------------------------------------------------------------------------------

ReplayObserver::ReplayObserver()
    : replay_control_impl_(new ReplayControlImpl(Control(), this)),
      observer_action_impl_(new ObserverActionImpl(Control())) {}

ReplayObserver::~ReplayObserver() {
    delete replay_control_impl_;
    delete observer_action_impl_;
}

ReplayControlInterface* ReplayObserver::ReplayControl() const {
    return replay_control_impl_;
}

ObserverActionInterface* ReplayObserver::ObserverAction() const {
    return observer_action_impl_;
}

bool ReplayObserver::IgnoreReplay(const ReplayInfo& replay_info, uint32_t /*player_id*/) {
    // Ignore games less than 30 seconds.
    return replay_info.duration < 30.0F;
}

void ReplayObserver::Reset() {
    Client::Reset();
    replay_control_impl_->control_interface_ = Control();
    observer_action_impl_->control_ = Control();
}
} // namespace sc2
