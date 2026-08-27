module;
#include "api/unit.h"
export module Agent;
import Client;

/*! @brief The base class for user defined bots.
 *
 *  The Agent class provides a user with most access into SC2 state and unit
 * manipulation. A user will issue actions to units via the ActionInterface,
 * examine game state with the ObservationInterface, issue blocking commands
 * (such as pathing queries) via the UnitQueryInterface and override library
 * provided events in ClientEvents.
 */

namespace {

class AgentControlImp;
class ActionInterface;
class ActionFeatureLayerInterface;
class AgentControlInterface;

}

export namespace sc2 {

//------------------------------------------------------------------------------

// ActionInterface.

//------------------------------------------------------------------------------

//! Interface for issuing actions to units. Actions should be batched via the
//! UnitCommand functions then eventually dispatched with SendActions. If you
//! are stepping the simulation yourself the Step will automatically call
//! SendActions. If your bot is running in real time you must call SendActions
//! yourself.
//! @return The raw (basic) action interface.
class ActionInterface
{
public:
    ProtoInterface&   proto_;
    GameRequestPtr    request_actions_;
    ControlInterface& control_;

    ActionImp::ActionImp ( ProtoInterface& proto, ControlInterface& control ):
        proto_ ( proto ), control_ ( control ) {}

    SC2APIProtocol::RequestAction* GetRequestAction ( );

    void UnitCommand (
        const Unit* unit, AbilityID ability, bool queued_command = false
    ) {
        if ( !unit ) return;
        UnitCommand ( unit->tag, ability, queued_command );
    }

    void ActionImp::UnitCommand (
        const Unit*    unit,
        AbilityID      ability,
        const Point2D& point,
        bool           queued_command = false
    ) {
        if ( !unit ) return;
        UnitCommand ( unit->tag, ability, point, queued_command );
    }

    void UnitCommand (
        const Unit* unit,
        AbilityID   ability,
        const Unit* target,
        bool        queued_command = false
    ) {
        if ( !unit || !target ) return;
        UnitCommand ( unit->tag, ability, target->tag, queued_command );
    }

    void UnitCommand (
        const Units& units, AbilityID ability, bool queued_command = false
    ) {
        Tags tags = sc2::ConvertToTags ( units );
        UnitCommand ( tags, ability, queued_command );
    }

    void UnitCommand (
        const Units&   units,
        AbilityID      ability,
        const Point2D& point,
        bool           queued_command = false
    ) {
        Tags tags = sc2::ConvertToTags ( units );
        UnitCommand ( tags, ability, point, queued_command );
    }

    void UnitCommand (
        const Units& units,
        AbilityID    ability,
        const Unit*  target,
        bool         queued_command = false
    ) {
        Tags tags = sc2::ConvertToTags ( units );
        UnitCommand ( tags, ability, target->tag, queued_command );
    }

    void UnitCommand (
        Tag tag, AbilityID ability, bool queued_command = false
    ) {
        SC2APIProtocol::RequestAction* request_action = GetRequestAction( );
        SC2APIProtocol::Action*        action = request_action->add_actions( );
        SC2APIProtocol::ActionRaw* action_raw = action->mutable_action_raw( );
        SC2APIProtocol::ActionRawUnitCommand* tag_command =
            action_raw->mutable_unit_command( );

        tag_command->set_ability_id ( ability );
        tag_command->set_queue_command ( queued_command );
        tag_command->add_unit_tags ( tag );
    }

    void UnitCommand (
        Tag            tag,
        AbilityID      ability,
        const Point2D& point,
        bool           queued_command = false
    ) {
        SC2APIProtocol::RequestAction* request_action = GetRequestAction( );
        SC2APIProtocol::Action*        action = request_action->add_actions( );
        SC2APIProtocol::ActionRaw* action_raw = action->mutable_action_raw( );
        SC2APIProtocol::ActionRawUnitCommand* tag_command =
            action_raw->mutable_unit_command( );

        tag_command->set_ability_id ( ability );
        SC2APIProtocol::Point2D* target_point =
            tag_command->mutable_target_world_space_pos( );
        target_point->set_x ( point.x );
        target_point->set_y ( point.y );
        tag_command->set_queue_command ( queued_command );
        tag_command->add_unit_tags ( tag );
    }

    void UnitCommand (
        Tag       tag,
        AbilityID ability,
        const Tag target_tag,
        bool      queued_command = false
    ) {
        SC2APIProtocol::RequestAction* request_action = GetRequestAction( );
        SC2APIProtocol::Action*        action = request_action->add_actions( );
        SC2APIProtocol::ActionRaw* action_raw = action->mutable_action_raw( );
        SC2APIProtocol::ActionRawUnitCommand* tag_command =
            action_raw->mutable_unit_command( );

        tag_command->set_ability_id ( ability );
        tag_command->set_target_unit_tag ( target_tag );
        tag_command->set_queue_command ( queued_command );
        tag_command->add_unit_tags ( tag );
    }

    void UnitCommand (
        const Tags& tags, AbilityID ability, bool queued_command = false
    ) {
        SC2APIProtocol::RequestAction* request_action = GetRequestAction( );
        SC2APIProtocol::Action*        action = request_action->add_actions( );
        SC2APIProtocol::ActionRaw* action_raw = action->mutable_action_raw( );
        SC2APIProtocol::ActionRawUnitCommand* tag_command =
            action_raw->mutable_unit_command( );

        tag_command->set_ability_id ( ability );
        tag_command->set_queue_command ( queued_command );

        for ( auto tag : tags )
            tag_command->add_unit_tags ( tag );
    }

    void UnitCommand (
        const Tags&    tags,
        AbilityID      ability,
        const Point2D& point,
        bool           queued_command = false
    ) {
        SC2APIProtocol::RequestAction* request_action = GetRequestAction( );
        SC2APIProtocol::Action*        action = request_action->add_actions( );
        SC2APIProtocol::ActionRaw* action_raw = action->mutable_action_raw( );
        SC2APIProtocol::ActionRawUnitCommand* tag_command =
            action_raw->mutable_unit_command( );

        tag_command->set_ability_id ( ability );
        SC2APIProtocol::Point2D* target_point =
            tag_command->mutable_target_world_space_pos( );
        target_point->set_x ( point.x );
        target_point->set_y ( point.y );
        tag_command->set_queue_command ( queued_command );

        for ( auto tag : tags )
            tag_command->add_unit_tags ( tag );
    }

    void UnitCommand (
        const Tags& tags,
        AbilityID   ability,
        const Tag   target_tag,
        bool        queued_command = false
    ) {
        SC2APIProtocol::RequestAction* request_action = GetRequestAction( );
        SC2APIProtocol::Action*        action = request_action->add_actions( );
        SC2APIProtocol::ActionRaw* action_raw = action->mutable_action_raw( );
        SC2APIProtocol::ActionRawUnitCommand* tag_command =
            action_raw->mutable_unit_command( );

        tag_command->set_ability_id ( ability );
        tag_command->set_target_unit_tag ( target_tag );
        tag_command->set_queue_command ( queued_command );

        for ( auto tag : tags )
        {
            tag_command->add_unit_tags ( tag );
        }
    }

    void ActionImp::ToggleAutocast ( Tag unit_tag, AbilityID ability ) {
        Tags tags = { unit_tag };
        ToggleAutocast ( tags, ability );
    }

    void ActionImp::ToggleAutocast (
        const Tags& unit_tags, AbilityID ability
    ) {
        SC2APIProtocol::RequestAction* request_action = GetRequestAction( );
        SC2APIProtocol::Action*        action = request_action->add_actions( );
        SC2APIProtocol::ActionRaw* action_raw = action->mutable_action_raw( );
        SC2APIProtocol::ActionRawToggleAutocast* autocast =
            action_raw->mutable_toggle_autocast( );
        for ( const auto& u : unit_tags )
        {
            autocast->add_unit_tags ( u );
        }
        autocast->set_ability_id ( ability );
    }

    void ActionImp::SendChat (
        const std::string& message, ChatChannel channel
    ) {
        SC2APIProtocol::RequestAction* request_action = GetRequestAction( );
        SC2APIProtocol::Action*        action = request_action->add_actions( );
        SC2APIProtocol::ActionChat*    action_chat =
            action->mutable_action_chat( );
        action_chat->set_message ( message );

        SC2APIProtocol::ActionChat::Channel channel_proto;
        if ( Convert ( channel, channel_proto ) )
        {
            action_chat->set_channel ( channel_proto );
        }
    }

    const Tags& ActionImp::Commands ( ) const {
        return commands_;
    }

    void ActionImp::SendActions ( ) {
        commands_.clear( );

        if ( request_actions_ == nullptr )
        {
            return;
        }

        if ( !proto_.SendRequest ( request_actions_ ) )
        {
            return;
        }

        SC2APIProtocol::RequestAction* request_action = GetRequestAction( );
        if ( request_action )
        {
            for ( int i = 0, e = request_action->actions_size( ); i < e; ++i )
            {
                const SC2APIProtocol::Action& action =
                    request_action->actions ( i );
                for ( auto tag :
                      action.action_raw( ).unit_command( ).unit_tags( ) )
                {
                    commands_.push_back ( tag );
                };
            }
        }

        request_actions_ = nullptr;
        control_.WaitForResponse( );
    }

    request_actions_ = nullptr;
    control_.WaitForResponse( );
} Tags commands_;

};

bool Convert (
    ChatChannel channel, SC2APIProtocol::ActionChat::Channel& channel_proto
) {
    switch ( channel )
    {
        case ChatChannel::All :
            channel_proto = SC2APIProtocol::ActionChat_Channel_Broadcast;
            return true;
        case ChatChannel::Team :
            channel_proto = SC2APIProtocol::ActionChat_Channel_Team;
            return true;
    }
    return false;
}

//------------------------------------------------------------------------------

// ActionFeatureLayerInterface.

//------------------------------------------------------------------------------


//! The ActionFeatureLayerInterface emulates UI actions in feature layer. Not
//! available in replays. Guaranteed to be valid when the OnStep event is
//! called.
//!
//! Interface for issuing actions in feature layers.
//! @return The feature layer action interface.
class ActionFeatureLayerInterface
{
public:
    ProtoInterface&   proto_;
    ControlInterface& control_;
    GameRequestPtr    request_actions_;

    ActionFeatureLayerImp::ActionFeatureLayerImp (
        ProtoInterface& proto, ControlInterface& control
    ):
        proto_ ( proto ), control_ ( control ) {}

    SC2APIProtocol::RequestAction* ActionFeatureLayerImp::GetRequestAction ( ) {
        if ( request_actions_ == nullptr )
        {
            request_actions_ = proto_.MakeRequest( );
        }
        return request_actions_->mutable_action( );
    }

    //! Issues a command to whatever is selected. Self targeting.
    //! @param ability The ability id of the command.
    void ActionFeatureLayerImp::UnitCommand ( AbilityID ability ) {
        SC2APIProtocol::RequestAction* request_action = GetRequestAction( );
        SC2APIProtocol::Action*        action = request_action->add_actions( );
        SC2APIProtocol::ActionSpatial* action_feature_layer =
            action->mutable_action_feature_layer( );
        SC2APIProtocol::ActionSpatialUnitCommand* unit_command =
            action_feature_layer->mutable_unit_command( );
        unit_command->set_ability_id ( ability );
    }

    //! Issues a command to whatever is selected. Uses a point as a target for
    //! the command.
    //! @param ability The ability id of the command.
    //! @param point The 2D world position to target.
    //! @param minimap Target in the minimap instead of the map.
    void ActionFeatureLayerImp::UnitCommand (
        AbilityID ability, const Point2DI& point, bool minimap = false
    ) {
        SC2APIProtocol::RequestAction* request_action = GetRequestAction( );
        SC2APIProtocol::Action*        action = request_action->add_actions( );
        SC2APIProtocol::ActionSpatial* action_feature_layer =
            action->mutable_action_feature_layer( );
        SC2APIProtocol::ActionSpatialUnitCommand* unit_command =
            action_feature_layer->mutable_unit_command( );

        SC2APIProtocol::PointI* pt;
        if ( minimap )
        {
            pt = unit_command->mutable_target_minimap_coord( );
        }
        else
        {
            pt = unit_command->mutable_target_screen_coord( );
        }
        pt->set_x ( point.x );
        pt->set_y ( point.y );
        unit_command->set_ability_id ( ability );
    }

    //! Moves the camera to be centered around a position. Coordinate is
    //! position on minimap feature layer.
    void ActionFeatureLayerImp::CameraMove ( const Point2DI& center ) {
        SC2APIProtocol::RequestAction* request_action = GetRequestAction( );
        SC2APIProtocol::Action*        action = request_action->add_actions( );
        SC2APIProtocol::ActionSpatial* action_feature_layer =
            action->mutable_action_feature_layer( );
        SC2APIProtocol::ActionSpatialCameraMove* camera_move =
            action_feature_layer->mutable_camera_move( );

        SC2APIProtocol::PointI* center_proto =
            camera_move->mutable_center_minimap( );
        center_proto->set_x ( center.x );
        center_proto->set_y ( center.y );
    }

    //! Selection of a point, equivalent to clicking the mouse on a unit.
    //! @param center The feature layer 'pixel' being clicked on.
    //! @param selection_type Any modifier keys, for example if 'shift-click' is
    //! desired.
    void ActionFeatureLayerImp::Select (
        const Point2DI& center, PointSelectionType selection_type
    ) {
        SC2APIProtocol::RequestAction* request_action = GetRequestAction( );
        SC2APIProtocol::Action*        action = request_action->add_actions( );
        SC2APIProtocol::ActionSpatial* action_feature_layer =
            action->mutable_action_feature_layer( );
        SC2APIProtocol::ActionSpatialUnitSelectionPoint* select_pt =
            action_feature_layer->mutable_unit_selection_point( );

        SC2APIProtocol::PointI* center_proto =
            select_pt->mutable_selection_screen_coord( );
        center_proto->set_x ( center.x );
        center_proto->set_y ( center.y );
        select_pt->set_type (
            static_cast<SC2APIProtocol::ActionSpatialUnitSelectionPoint_Type> (
                selection_type
            )
        );
    }

    //! Selection of an area, equivalent to click-dragging the mouse over an
    //! area of the screen.
    //! @param p0 The feature layer pixel where the first click occurs (mouse
    //! button down).
    //! @param p1 The feature layer pixel where the drag release occurs (mouse
    //! button up).
    //! @param add_to_selection Will add newly selected units to an existing
    //! selection.
    void ActionFeatureLayerImp::Select (
        const Point2DI& p0, const Point2DI& p1, bool add_to_selection = false
    ) {
        SC2APIProtocol::RequestAction* request_action = GetRequestAction( );
        SC2APIProtocol::Action*        action = request_action->add_actions( );
        SC2APIProtocol::ActionSpatial* action_feature_layer =
            action->mutable_action_feature_layer( );
        SC2APIProtocol::ActionSpatialUnitSelectionRect* select_rect =
            action_feature_layer->mutable_unit_selection_rect( );
        SC2APIProtocol::RectangleI* selection_screen_coord =
            select_rect->add_selection_screen_coord( );
        SC2APIProtocol::PointI* selection_p0 =
            selection_screen_coord->mutable_p0( );
        selection_p0->set_x ( p0.x );
        selection_p0->set_y ( p0.y );
        SC2APIProtocol::PointI* selection_p1 =
            selection_screen_coord->mutable_p1( );
        selection_p1->set_x ( p1.x );
        selection_p1->set_y ( p1.y );
    }

    //! This function sends out all batched selection and unit commands. You DO
    //! NOT need to call this function in non real time simulations since it is
    //! automatically called when stepping the simulation forward. You only need
    //! to call this function in a real time simulation.
    void ActionFeatureLayerImp::SendActions ( ) {
        if ( request_actions_ == nullptr )
        {
            return;
        }

        if ( !proto_.SendRequest ( request_actions_ ) )
        {
            return;
        }

        request_actions_ = nullptr;
        control_.WaitForResponse( );
    }
};

//------------------------------------------------------------------------------

// AgentControlInterface.

//------------------------------------------------------------------------------

//! The AgentControlInterface is only currently used for restarting a game.
//! For internal use.
//! @return The agent control interface.
class AgentControlInterface
{
public:
    ControlInterface*                      control_interface_;
    std::unique_ptr<ActionImp>             actions_;
    std::unique_ptr<ActionFeatureLayerImp> actions_feature_layer_;
    Agent*                                 agent_;

    AgentControlImp ( Agent* agent, ControlInterface* control_interface );
    ~AgentControlImp ( ) = default;

    bool Restart ( ) override;

    AgentControlImp::AgentControlImp (
        Agent* agent, ControlInterface* control_interface
    ):
        control_interface_ ( control_interface ),
        actions_ ( nullptr ),
        agent_ ( agent ) {
        actions_ = std::make_unique<ActionImp> (
            control_interface_->Proto( ),
            *control_interface
        );
        actions_feature_layer_ = std::make_unique<ActionFeatureLayerImp> (
            control_interface_->Proto( ),
            *control_interface
        );
    }

    virtual ~AgentControlInterface() = default;

    virtual bool AgentControlImp::Restart ( ) {
        GameRequestPtr request = control_interface_->Proto( ).MakeRequest( );
        request->mutable_restart_game( );
        if ( !control_interface_->Proto( ).SendRequest ( request ) )
        {
            return false;
        }

        GameResponsePtr response = control_interface_->WaitForResponse( );
        if ( !response.get( ) )
        {
            assert ( 0 );
            return false;
        }
        if ( !response->has_restart_game( ) )
        {
            assert ( 0 );
            return false;
        }
        const SC2APIProtocol::ResponseRestartGame& response_restart_game =
            response->restart_game( );
        if ( response_restart_game.has_error( ) )
        {
            // TODO: Output the error.
            assert ( 0 );
            return false;
        }

        agent_->Control( )->GetObservation( );
        agent_->OnGameStart( );

        return control_interface_->IsInGame( );
    }
};

//------------------------------------------------------------------------------

// Agent implementation.

//------------------------------------------------------------------------------

/*! @brief The base class for user defined bots.\n\n The Agent class provides a
 * user with most access into SC2 state and unit manipulation. A user will issue
 * actions to units via the ActionInterface, examine game state with the
 * ObservationInterface, issue blocking commands (such as pathing queries) via
 * the UnitQueryInterface and override library provided events in ClientEvents.
 */
class Agent : public Client
{
public:
    Agent::Agent ( ):
        agent_control_imp_ ( new AgentControlImp ( this, Control( ) ) ) {}

    Agent::~Agent ( ) {
        delete agent_control_imp_;
    }

    //! Interface for issuing actions to units. Actions should be batched via
    //! the UnitCommand functions then eventually dispatched with SendActions.
    //! If you are stepping the simulation yourself the Step will automatically
    //! call SendActions. If your bot is running in real time you must call
    //! SendActions yourself.
    //! @return The raw (basic) action interface.
    ActionInterface* Agent::Actions ( ) {
        return agent_control_imp_->actions_.get( );
    }

    //! Interface for issuing actions in feature layers.
    //! @return The feature layer action interface.
    ActionFeatureLayerInterface* Agent::ActionsFeatureLayer ( ) {
        return agent_control_imp_->actions_feature_layer_.get( );
    }

    //! The AgentControlInterface is only currently used for restarting a game.
    //! For internal use.
    //! @return The agent control interface.
    AgentControlInterface* Agent::AgentControl ( ) {
        return agent_control_imp_;
    }

private:
    AgentControlImp* agent_control_imp_;
};

} // namespace sc2
