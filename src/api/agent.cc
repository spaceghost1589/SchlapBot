#include "api/unit.h"
#include "lib/gametypes.h"
#include "lib/typeids/5.0.14_typeenums.h"

import common;
import protocol_interface;

namespace sc2 {
//------------------------------------------------------------------------------

// ActionInterface.

//------------------------------------------------------------------------------

class ActionImpl : public ActionInterface {
public:
    GameRequestPtr     request_actions_;
    ControlInterface&  control_;

    ActionImpl(ProtocolInterface& proto, ControlInterface& control);

    SC2APIProtocol::RequestAction* GetRequestAction();

    void UnitCommand(const Unit* unit, AbilityID ability, bool queued_command = false) override;
    void UnitCommand(const Unit* unit, AbilityID ability, const Point2D& point, bool queued_command = false) override;
    void UnitCommand(const Unit* unit, AbilityID ability, const Unit* target, bool queued_command = false) override;
    void UnitCommand(const Units& units, AbilityID ability, bool queued_command = false) override;
    void UnitCommand(const Units& units, AbilityID ability, const Point2D& point, bool queued_command = false) override;
    void UnitCommand(const Units& units, AbilityID ability, const Unit* target, bool queued_command = false) override;
    void UnitCommand(Tag tag, AbilityID ability, bool queued_command = false) override;
    void UnitCommand(Tag tag, AbilityID ability, const Point2D& point, bool queued_command = false) override;
    void UnitCommand(Tag tag, AbilityID ability, const Tag target_tag, bool queued_command = false) override;
    void UnitCommand(const Tags& tags, AbilityID ability, bool queued_command = false) override;
    void UnitCommand(const Tags& tags, AbilityID ability, const Point2D& point, bool queued_command = false) override;
    void UnitCommand(const Tags& tags, AbilityID ability, const Tag target_tag, bool queued_command = false) override;

    void ToggleAutocast(Tag unit_tag, AbilityID ability) override;
    void ToggleAutocast(const Tags& unit_tags, AbilityID ability) override;

    void SendChat(const std::string& message, ChatChannel channel) override;

    const Tags& Commands() const override;

    void SendActions() override;

    Tags commands_;
};

ActionImpl::ActionImpl(ControlInterface& control) : control_(control) {}

SC2APIProtocol::RequestAction* ActionImpl::GetRequestAction() {
    if (request_actions_ == nullptr) {
        request_actions_ = ProtoFace::.MakeRequest();
    }
    return request_actions_->mutable_action();
}

const Tags& ActionImpl::Commands() const {
    return commands_;
}

void ActionImpl::SendActions() {
    commands_.clear();

    if (request_actions_ == nullptr) {
        return;
    }

    if (!ProtoFace::.SendRequest(request_actions_)) {
        return;
    }

    if (const SC2APIProtocol::RequestAction* request_action = GetRequestAction()) {
        for (int i = 0, e = request_action->actions_size(); i < e; ++i) {
            const SC2APIProtocol::Action& action = request_action->actions(i);
            for (auto tag : action.action_raw().unit_command().unit_tags()) {
                commands_.push_back(tag);
            };
        }
    }

    request_actions_ = nullptr;
    control_.WaitForResponse();
}

void ActionImpl::ToggleAutocast(Tag unit_tag, AbilityID ability) {
    const Tags tags = {unit_tag};
    ToggleAutocast(tags, ability);
}

void ActionImpl::ToggleAutocast(const Tags& unit_tags, AbilityID ability) {
    SC2APIProtocol::RequestAction*           request_action = GetRequestAction();
    SC2APIProtocol::Action*                  action         = request_action->add_actions();
    SC2APIProtocol::ActionRaw*               action_raw     = action->mutable_action_raw();
    SC2APIProtocol::ActionRawToggleAutocast* autocast       = action_raw->mutable_toggle_autocast();
    for (const auto& u : unit_tags) {
        autocast->add_unit_tags(u);
    }
    autocast->set_ability_id(ability);
}

bool Convert(ChatChannel channel, SC2APIProtocol::ActionChat::Channel& channel_proto) {
    switch (channel) {
        case ChatChannel::All:
            channel_proto = SC2APIProtocol::ActionChat_Channel_Broadcast;
            return true;
        case ChatChannel::Team:
            channel_proto = SC2APIProtocol::ActionChat_Channel_Team;
            return true;
    }
    return false;
}

void ActionImpl::SendChat(const std::string& message, ChatChannel channel) {
    SC2APIProtocol::RequestAction* request_action = GetRequestAction();
    SC2APIProtocol::Action*        action         = request_action->add_actions();
    SC2APIProtocol::ActionChat*    action_chat    = action->mutable_action_chat();
    action_chat->set_message(message);

    SC2APIProtocol::ActionChat::Channel channel_proto;
    if (Convert(channel, channel_proto)) {
        action_chat->set_channel(channel_proto);
    }
}

void ActionImpl::UnitCommand(const Unit* unit, AbilityID ability, bool queued_command) {
    if (!unit)
        return;
    UnitCommand(unit->tag, ability, queued_command);
}

void ActionImpl::UnitCommand(const Unit* unit, AbilityID ability, const Point2D& point, bool queued_command) {
    if (!unit)
        return;
    UnitCommand(unit->tag, ability, point, queued_command);
}

void ActionImpl::UnitCommand(const Unit* unit, AbilityID ability, const Unit* target, bool queued_command) {
    if (!unit || !target)
        return;
    UnitCommand(unit->tag, ability, target->tag, queued_command);
}

void ActionImpl::UnitCommand(const Units& units, AbilityID ability, bool queued_command) {
    Tags tags = sc2::ConvertToTags(units);
    UnitCommand(tags, ability, queued_command);
}

void ActionImpl::UnitCommand(const Units& units, AbilityID ability, const Point2D& point, bool queued_command) {
    Tags tags = sc2::ConvertToTags(units);
    UnitCommand(tags, ability, point, queued_command);
}

void ActionImpl::UnitCommand(const Units& units, AbilityID ability, const Unit* target, bool queued_command) {
    Tags tags = sc2::ConvertToTags(units);
    UnitCommand(tags, ability, target->tag, queued_command);
}

void ActionImpl::UnitCommand(Tag tag, AbilityID ability, bool queued_command) {
    SC2APIProtocol::RequestAction*        request_action = GetRequestAction();
    SC2APIProtocol::Action*               action         = request_action->add_actions();
    SC2APIProtocol::ActionRaw*            action_raw     = action->mutable_action_raw();
    SC2APIProtocol::ActionRawUnitCommand* tag_command    = action_raw->mutable_unit_command();

    tag_command->set_ability_id(ability);
    tag_command->set_queue_command(queued_command);
    tag_command->add_unit_tags(tag);
}

void ActionImpl::UnitCommand(Tag tag, AbilityID ability, const Point2D& point, bool queued_command) {
    SC2APIProtocol::RequestAction*        request_action = GetRequestAction();
    SC2APIProtocol::Action*               action         = request_action->add_actions();
    SC2APIProtocol::ActionRaw*            action_raw     = action->mutable_action_raw();
    SC2APIProtocol::ActionRawUnitCommand* tag_command    = action_raw->mutable_unit_command();

    tag_command->set_ability_id(ability);
    SC2APIProtocol::Point2D* target_point = tag_command->mutable_target_world_space_pos();
    target_point->set_x(point.x);
    target_point->set_y(point.y);
    tag_command->set_queue_command(queued_command);
    tag_command->add_unit_tags(tag);
}

void ActionImpl::UnitCommand(Tag tag, AbilityID ability, const Tag target_tag, bool queued_command) {
    SC2APIProtocol::RequestAction*        request_action = GetRequestAction();
    SC2APIProtocol::Action*               action         = request_action->add_actions();
    SC2APIProtocol::ActionRaw*            action_raw     = action->mutable_action_raw();
    SC2APIProtocol::ActionRawUnitCommand* tag_command    = action_raw->mutable_unit_command();

    tag_command->set_ability_id(ability);
    tag_command->set_target_unit_tag(target_tag);
    tag_command->set_queue_command(queued_command);
    tag_command->add_unit_tags(tag);
}

void ActionImpl::UnitCommand(const Tags& tags, AbilityID ability, bool queued_command) {
    SC2APIProtocol::RequestAction*        request_action = GetRequestAction();
    SC2APIProtocol::Action*               action         = request_action->add_actions();
    SC2APIProtocol::ActionRaw*            action_raw     = action->mutable_action_raw();
    SC2APIProtocol::ActionRawUnitCommand* tag_command    = action_raw->mutable_unit_command();

    tag_command->set_ability_id(ability);
    tag_command->set_queue_command(queued_command);

    for (auto tag : tags)
        tag_command->add_unit_tags(tag);
}

void ActionImpl::UnitCommand(const Tags& tags, AbilityID ability, const Point2D& point, bool queued_command) {
    SC2APIProtocol::RequestAction*        request_action = GetRequestAction();
    SC2APIProtocol::Action*               action         = request_action->add_actions();
    SC2APIProtocol::ActionRaw*            action_raw     = action->mutable_action_raw();
    SC2APIProtocol::ActionRawUnitCommand* tag_command    = action_raw->mutable_unit_command();

    tag_command->set_ability_id(ability);
    SC2APIProtocol::Point2D* target_point = tag_command->mutable_target_world_space_pos();
    target_point->set_x(point.x);
    target_point->set_y(point.y);
    tag_command->set_queue_command(queued_command);

    for (auto tag : tags)
        tag_command->add_unit_tags(tag);
}

void ActionImpl::UnitCommand(const Tags& tags, AbilityID ability, const Tag target_tag, bool queued_command) {
    SC2APIProtocol::RequestAction*        request_action = GetRequestAction();
    SC2APIProtocol::Action*               action         = request_action->add_actions();
    SC2APIProtocol::ActionRaw*            action_raw     = action->mutable_action_raw();
    SC2APIProtocol::ActionRawUnitCommand* tag_command    = action_raw->mutable_unit_command();

    tag_command->set_ability_id(ability);
    tag_command->set_target_unit_tag(target_tag);
    tag_command->set_queue_command(queued_command);

    for (auto tag : tags) {
        tag_command->add_unit_tags(tag);
    }
}

//------------------------------------------------------------------------------

// ActionFeatureLayerInterface.

//------------------------------------------------------------------------------

//! The ActionFeatureLayerInterface emulates UI actions in feature layer. Not
//! available in replays. Guaranteed to be valid when the OnStep event is
//! called.
class ActionFeatureLayerInterface {
public:
    ControlInterface& control_;
    GameRequestPtr    request_actions_;

    ActionFeatureLayerInterface (
        ProtocolInterface& proto, ControlInterface& control
    );

    virtual ~ActionFeatureLayerInterface ( ) = default;

    SC2APIProtocol::RequestAction* ActionImp::GetRequestAction() {
        if (request_actions_ == nullptr) {
            request_actions_ = proto_.MakeRequest();
        }
        return request_actions_->mutable_action();
    }

    //! Issues a command to whatever is selected. Self targeting.
    //! @param ability The ability id of the command.
    virtual void UnitCommand ( AbilityID ability ) = 0;

    //! Issues a command to whatever is selected. Uses a point as a target for
    //! the command.
    //! @param ability The ability id of the command.
    //! @param point The 2D world position to target.
    //! @param minimap Target in the minimap instead of the map.
    virtual void UnitCommand (
        AbilityID ability, const Point2DI& point, bool minimap = false
    ) = 0;

    //! Moves the camera to be centered around a position. Coordinate is
    //! position on minimap feature layer.
    virtual void CameraMove ( const Point2DI& center ) = 0;

    v//! Selection of a point, equivalent to clicking the mouse on a unit.
    //! @param center The feature layer 'pixel' being clicked on.
    //! @param selection_type Any modifier keys, for example if 'shift-click'
    //! is desired.
    virtual void Select (
        const Point2DI& center, PointSelectionType selection_type
    ) = 0;

    //! Selection of an area, equivalent to click-dragging the mouse over an
    //! area of the screen.
    //! @param p0 The feature layer pixel where the first click occurs (mouse
    //! button down).
    //! @param p1 The feature layer pixel where the drag release occurs (mouse
    //! button up).
    //! @param add_to_selection Will add newly selected units to an existing
    //! selection.
    virtual void Select (
        const Point2DI& p0, const Point2DI& p1, bool add_to_selection = false
    ) = 0;

    //! This function sends out all batched selection and unit commands. You DO
    //! NOT need to call this function in non real time simulations since it is
    //! automatically called when stepping the simulation forward. You only need
    //! to call this function in a real time simulation.
    virtual void SendActions ( ) = 0;
};




}

void SendActions() {
    if (request_actions_ == nullptr) {
        return;
    }

    if (!ProtoFace::.SendRequest(request_actions_)) {
        return;
    }

    request_actions_ = nullptr;
    control_.WaitForResponse();
}

void UnitCommand(AbilityID ability) {
    SC2APIProtocol::RequestAction*            request_action       = GetRequestAction();
    SC2APIProtocol::Action*                   action               = request_action->add_actions();
    SC2APIProtocol::ActionSpatial*            action_feature_layer = action->mutable_action_feature_layer();
    SC2APIProtocol::ActionSpatialUnitCommand* unit_command         = action_feature_layer->mutable_unit_command();
    unit_command->set_ability_id(ability);
}

void UnitCommand(AbilityID ability, const Point2DI& point, bool minimap) {
    SC2APIProtocol::RequestAction*            request_action       = GetRequestAction();
    SC2APIProtocol::Action*                   action               = request_action->add_actions();
    SC2APIProtocol::ActionSpatial*            action_feature_layer = action->mutable_action_feature_layer();
    SC2APIProtocol::ActionSpatialUnitCommand* unit_command         = action_feature_layer->mutable_unit_command();

    SC2APIProtocol::PointI* pt;
    if (minimap) {
        pt = unit_command->mutable_target_minimap_coord();
    }
    else {
        pt = unit_command->mutable_target_screen_coord();
    }
    pt->set_x(point.x);
    pt->set_y(point.y);
    unit_command->set_ability_id(ability);
}

void CameraMove(const Point2DI& center) {
    SC2APIProtocol::RequestAction*           request_action       = GetRequestAction();
    SC2APIProtocol::Action*                  action               = request_action->add_actions();
    SC2APIProtocol::ActionSpatial*           action_feature_layer = action->mutable_action_feature_layer();
    SC2APIProtocol::ActionSpatialCameraMove* camera_move          = action_feature_layer->mutable_camera_move();

    SC2APIProtocol::PointI* center_proto = camera_move->mutable_center_minimap();
    center_proto->set_x(center.x);
    center_proto->set_y(center.y);
}

void Select(const Point2DI& center, PointSelectionType selection_type) {
    SC2APIProtocol::RequestAction*                   request_action = GetRequestAction();
    SC2APIProtocol::Action*                          action = request_action->add_actions();
    SC2APIProtocol::ActionSpatial*                   action_feature_layer = action->mutable_action_feature_layer();
    SC2APIProtocol::ActionSpatialUnitSelectionPoint* select_pt = action_feature_layer->mutable_unit_selection_point();

    SC2APIProtocol::PointI* center_proto = select_pt->mutable_selection_screen_coord();
    center_proto->set_x(center.x);
    center_proto->set_y(center.y);
    select_pt->set_type(static_cast<SC2APIProtocol::ActionSpatialUnitSelectionPoint_Type>(selection_type));
}

void Select(const Point2DI& p0, const Point2DI& p1, bool /*add_to_selection*/) {
    SC2APIProtocol::RequestAction*                  request_action = GetRequestAction();
    SC2APIProtocol::Action*                         action = request_action->add_actions();
    SC2APIProtocol::ActionSpatial*                  action_feature_layer = action->mutable_action_feature_layer();
    SC2APIProtocol::ActionSpatialUnitSelectionRect* select_rect = action_feature_layer->mutable_unit_selection_rect();
    SC2APIProtocol::RectangleI*                     selection_screen_coord = select_rect->add_selection_screen_coord();
    SC2APIProtocol::PointI*                         selection_p0 = selection_screen_coord->mutable_p0();
    selection_p0->set_x(p0.x);
    selection_p0->set_y(p0.y);
    SC2APIProtocol::PointI* selection_p1 = selection_screen_coord->mutable_p1();
    selection_p1->set_x(p1.x);
    selection_p1->set_y(p1.y);
}

//------------------------------------------------------------------------------

// AgentControlInterface.

//------------------------------------------------------------------------------

class AgentControlInterface {
public:
    ControlInterface*                       control_interface_;
    std::unique_ptr<ActionImpl>             actions_;
    std::unique_ptr<ActionFeatureLayerImpl> actions_feature_layer_;
    Agent*                                  agent_;

    AgentControlImpl(Agent* agent, ControlInterface* control_interface);
    virtual ~AgentControlInterface ( ) = default;

    virtual bool Restart ( ) = 0;
};

AgentControlImpl::AgentControlImpl(Agent* agent, ControlInterface* control_interface)
    : control_interface_(control_interface), actions_(nullptr), agent_(agent) {
    actions_               = std::make_unique<ActionImpl>(control_interface_->Proto(), *control_interface);
    actions_feature_layer_ = std::make_unique<ActionFeatureLayerImpl>(control_interface_->Proto(), *control_interface);
}

bool AgentControlImpl::Restart() {
    GameRequestPtr request = control_interface_->Proto().MakeRequest();
    request->mutable_restart_game();
    if (!control_interface_->Proto().SendRequest(request)) {
        return false;
    }

    GameResponsePtr response = control_interface_->WaitForResponse();
    if (!response.get()) {
        assert(0);
        return false;
    }
    if (!response->has_restart_game()) {
        assert(0);
        return false;
    }
    const SC2APIProtocol::ResponseRestartGame& response_restart_game = response->restart_game();
    if (response_restart_game.has_error()) {
        // TODO: Output the error.
        assert(0);
        return false;
    }

    agent_->Control()->GetObservation();
    agent_->OnGameStart();

    return control_interface_->IsInGame();
}

//------------------------------------------------------------------------------

// Agent implementation.

//------------------------------------------------------------------------------

Agent::Agent() : agent_control_impl_(new AgentControlImpl(this, Control())) {}

Agent::~Agent() {
    delete agent_control_impl_;
}

ActionInterface* Agent::Actions() const {
    return agent_control_impl_->actions_.get();
}

ActionFeatureLayerInterface* Agent::ActionsFeatureLayer() const {
    return agent_control_impl_->actions_feature_layer_.get();
}

AgentControlInterface* Agent::AgentControl() const {
    return agent_control_impl_;
}
} // namespace sc2
