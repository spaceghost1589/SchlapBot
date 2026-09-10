module;
#include <variant>

#include <s2clientprotocol/sc2api.pb.h>
export module action_interface;
import protocol_interface;
import point;
import game_types;
import type_enums;
import unit;

export namespace sc2 {

using namespace std;

/*! @brief The ActionInterface issues actions to units in a game. Not available
 * in replays.
 * \n\n Guaranteed to be valid when the OnStep event is called. */
class ActionInterface final {
public:
    Tags commands_;

    GameRequestPtr request_actions_;

    // ControlInterface& control_;

    ActionInterface ( ) { }

    // TODO missing comment
    static bool Convert (
        const ChatChannel                    channel,
        SC2APIProtocol::ActionChat::Channel &channel_proto
    ) {
        switch ( channel ) {
            case ChatChannel::All :
                channel_proto = SC2APIProtocol::ActionChat_Channel_Broadcast;
                return true;
            case ChatChannel::Team :
                channel_proto = SC2APIProtocol::ActionChat_Channel_Team;
                return true;
        }
        return false;
    }

    /*! @brief Sends a message to the game chat.
     * @param message Text of message to send.
     * @param channel Which players will see the message. */
    void SendChat ( const string &message, const ChatChannel channel ) {
        SC2APIProtocol::RequestAction *request_action = GetRequestAction( );
        SC2APIProtocol::Action        *action = request_action->add_actions( );
        SC2APIProtocol::ActionChat    *action_chat =
            action->mutable_action_chat( );
        action_chat->set_message ( message );

        if ( SC2APIProtocol::ActionChat::Channel channel_proto;
             Convert ( channel, channel_proto ) )
        {
            action_chat->set_channel ( channel_proto );
        }
    }

    SC2APIProtocol::RequestAction *GetRequestAction ( ) {
        if ( request_actions_ == nullptr ) {
            request_actions_ = ProtoFace::MakeRequest( );
        }
        return request_actions_->mutable_action( );
    }

    inline SC2APIProtocol::ActionRaw *ActionRawGenerate ( ) {
        return GetRequestAction( )->add_actions( )->mutable_action_raw( );
    }

    /*! @brief Issues a command to a unit. Self targeting.
     * @param unit The unit to send the command to.
     * @param ability The ability id of the command.
     * @param queued_command (false) Whether the command will be queued */
    void UnitCommand (
        const Unit     *unit,
        const AbilityID ability,
        const bool      queued_command = false
    ) {
        if ( !unit )
            return;
        UnitCommand ( unit->tag, ability, queued_command );
    }

    /*! @brief Issues a command to multiple units (prefer this where possible).
     * @see UnitCommand(Unit, AbilityID). */
    void UnitCommand (
        const Units    &units,
        const AbilityID ability,
        const bool      queued_command = false
    ) {
        const Tags tags = ConvertToTags ( units );
        UnitCommand ( tags, ability, queued_command );
    }

    /*! @brief Issues a command to a unit. Self targeting.
     * @param tag Tag of unit.
     * @param ability The ability id of the command.
     * @param queued_command (false) Whether the command will be queued */
    void UnitCommand (
        const Tag       tag,
        const AbilityID ability,
        const bool      queued_command = false
    ) {
        SC2APIProtocol::ActionRaw            *action_raw = ActionRawGenerate( );
        SC2APIProtocol::ActionRawUnitCommand *tag_command =
            action_raw->mutable_unit_command( );

        tag_command->set_ability_id ( ability );
        tag_command->set_queue_command ( queued_command );
        tag_command->add_unit_tags ( tag );
    }

    /*! @brief Issues a command to multiple units (prefer this where possible).
     * Same as UnitCommand(Tag, AbilityID).
     * @param tags Tags of units.
     * @param ability The ability id of the command.
     * @param queued_command (false) Whether the command will be queued */
    void UnitCommand (
        const Tags     &tags,
        const AbilityID ability,
        const bool      queued_command = false
    ) {
        SC2APIProtocol::ActionRaw            *action_raw = ActionRawGenerate( );
        SC2APIProtocol::ActionRawUnitCommand *tag_command =
            action_raw->mutable_unit_command( );

        tag_command->set_ability_id ( ability );
        tag_command->set_queue_command ( queued_command );

        for ( const auto tag : tags )
            tag_command->add_unit_tags ( tag );
    }

    //------------------------------------------------------------------------------

    /*! @brief Issues a command to a unit. Targets a point.
     * @param unit The unit to send the command to.
     * @param ability The ability id of the command.
     * @param point The 2D world position to target.
     * @param queued_command (false) Whether the command will be queued */
    void UnitCommand (
        const Unit     *unit,
        const AbilityID ability,
        const Point2D  &point,
        const bool      queued_command = false
    ) {
        if ( !unit )
            return;
        UnitCommand ( unit->tag, ability, point, queued_command );
    }

    /*! @brief Issues a command to multiple units (prefer this where possible).
     * Same as UnitCommand(Unit, AbilityID, Point2D). */
    void UnitCommand (
        const Units    &units,
        const AbilityID ability,
        const Point2D  &point,
        const bool      queued_command = false
    ) {
        const Tags tags = ConvertToTags ( units );
        UnitCommand ( tags, ability, point, queued_command );
    }

    /*! @brief Issues a command to a unit. Targets a point.
     * @param tag Tag of unit.
     * @param ability The ability id of the command.
     * @param point The 2D world position to target.
     * @param queued_command (false) Whether the command will be queued */
    void UnitCommand (
        const Tag       tag,
        const AbilityID ability,
        const Point2D  &point,
        const bool      queued_command = false
    ) {
        SC2APIProtocol::ActionRaw            *action_raw = ActionRawGenerate( );
        SC2APIProtocol::ActionRawUnitCommand *tag_command =
            action_raw->mutable_unit_command( );

        tag_command->set_ability_id ( ability );
        SC2APIProtocol::Point2D *target_point =
            tag_command->mutable_target_world_space_pos( );
        target_point->set_x ( point.x );
        target_point->set_y ( point.y );
        tag_command->set_queue_command ( queued_command );
        tag_command->add_unit_tags ( tag );
    }

    /*! @brief Issues a command to multiple units (prefer this where possible).
     * Same as UnitCommand(Tag, AbilityID, Point2D).
     * @param tags Tags of units.
     * @param ability The ability id of the command.
     * @param point The 2D world position to target.
     * @param queued_command (false) Whether the command will be queued */
    void UnitCommand (
        const Tags     &tags,
        const AbilityID ability,
        const Point2D  &point,
        const bool      queued_command = false
    ) {
        SC2APIProtocol::ActionRaw            *action_raw = ActionRawGenerate( );
        SC2APIProtocol::ActionRawUnitCommand *tag_command =
            action_raw->mutable_unit_command( );

        tag_command->set_ability_id ( ability );
        SC2APIProtocol::Point2D *target_point =
            tag_command->mutable_target_world_space_pos( );
        target_point->set_x ( point.x );
        target_point->set_y ( point.y );
        tag_command->set_queue_command ( queued_command );

        for ( const auto tag : tags )
            tag_command->add_unit_tags ( tag );
    }

    //--------------------------------------------------------------------------


    /*! @brief Issues a command to a unit. Targets another unit.
     * @param unit The unit to send the command to.
     * @param ability The ability id of the command.
     * @param target The unit that is a target of the unit getting the command.
     * @param queued_command (false) Whether the command will be queued */
    void UnitCommand (
        const Unit     *unit,
        const AbilityID ability,
        const Unit     *target,
        const bool      queued_command = false
    ) {
        if ( !unit || !target )
            return;
        UnitCommand ( unit->tag, ability, target->tag, queued_command );
    }

    /*! @brief Issues a command to multiple units (prefer this where
     * possible).\n\n Same as UnitCommand(Unit, AbilityID, Unit). */
    void UnitCommand (
        const Units    &units,
        const AbilityID ability,
        const Unit     *target,
        const bool      queued_command = false
    ) {
        const Tags tags = ConvertToTags ( units );
        UnitCommand ( tags, ability, target->tag, queued_command );
    }

    /*! @brief Issues a command to a unit. Targets another unit.
     * @param tag Tag of unit.
     * @param ability The ability id of the command.
     * @param target_tag Tag of unit that is a target of the unit getting the
     * command.
     * @param queued_command (false) Whether the command will be queued */
    void UnitCommand (
        const Tag       tag,
        const AbilityID ability,
        const Tag       target_tag,
        const bool      queued_command = false
    ) {
        SC2APIProtocol::ActionRaw            *action_raw = ActionRawGenerate( );
        SC2APIProtocol::ActionRawUnitCommand *tag_command =
            action_raw->mutable_unit_command( );

        tag_command->set_ability_id ( ability );
        tag_command->set_target_unit_tag ( target_tag );
        tag_command->set_queue_command ( queued_command );
        tag_command->add_unit_tags ( tag );
    }

    /*! @brief Issues a command to multiple units (prefer this where possible).
     * Same as UnitCommand(Tag, AbilityID, Tag).
     * @param tags Tags of units.
     * @param ability The ability id of the command.
     * @param target_tag Tag of unit that is a target of the unit getting the
     * command.
     * @param queued_command (false) Whether the command will be queued */
    void UnitCommand (
        const Tags     &tags,
        const AbilityID ability,
        const Tag       target_tag,
        const bool      queued_command = false
    ) {
        SC2APIProtocol::ActionRaw            *action_raw = ActionRawGenerate( );
        SC2APIProtocol::ActionRawUnitCommand *tag_command =
            action_raw->mutable_unit_command( );

        tag_command->set_ability_id ( ability );
        tag_command->set_target_unit_tag ( target_tag );
        tag_command->set_queue_command ( queued_command );

        for ( const auto tag : tags ) {
            tag_command->add_unit_tags ( tag );
        }
    }

    /*! @brief Enables or disables autocast of an ability on a unit.
     * @param unit_tag The unit to toggle the ability on.
     * @param ability The ability to be toggled. */
    void ToggleAutocast ( const Tag unit_tag, const AbilityID ability ) {
        Tags tags = { unit_tag };
        ToggleAutocast ( tags, ability );
    }

    /*! @brief Enables or disables autocast of an ability on a list of units.
     * @param unit_tags The units to toggle the ability on.
     * @param ability The ability to be toggled. */
    void ToggleAutocast (
        const variant<Tag, Tags> &unit_tags,
        const AbilityID           ability
    ) {
        SC2APIProtocol::ActionRaw *action_raw = ActionRawGenerate( );
        SC2APIProtocol::ActionRawToggleAutocast *autocast =
            action_raw->mutable_toggle_autocast( );

        visit ( [autocast]<typename T0> ( T0 &&unit_tags_T0 ) {
            using T = decay_t<T0>;

            if constexpr ( is_same_v<T, Tag> ) {
                autocast->add_unit_tags ( unit_tags_T0 );
            } else if constexpr ( is_same_v<T, Tags> )
                for ( const Tag &tag : unit_tags_T0 ) {
                    autocast->add_unit_tags ( tag );
                }
        }, unit_tags );

        autocast->set_ability_id ( ability );
    }

    /*! @brief Returns a list of unit tags that have sent commands out in the
     * last call to SendActions. This will be used to determine if a unit
     * actually has a command when the observation is received.
     * @return Array of units that have sent commands. */
    const Tags &CommandsLastCall ( ) const {
        return commands_;
    }

    /*! @brief This function sends out all batched unit commands. You DO NOT
     * need to call this function in non real time simulations since it is
     * automatically called when stepping the simulation forward. You only need
     * to call this function in a real time simulation. For example, if you
     * wanted to move 20 marines to some position on the map you'd want to batch
     * all of those unit commands and send them at once. */
    void SendActions ( ) {
        commands_.clear( );

        if ( request_actions_ == nullptr ) {
            return;
        }

        if ( !ProtoFace::SendRequest ( request_actions_ ) ) {
            return;
        }

        if ( const SC2APIProtocol::RequestAction *request_action =
                 GetRequestAction( ) )
        {
            for ( int i = 0, e = request_action->actions_size( ); i < e; ++i ) {
                const SC2APIProtocol::Action &action =
                    request_action->actions ( i );
                for ( auto tag :
                      action.action_raw( ).unit_command( ).unit_tags( ) )
                {
                    commands_.push_back ( tag );
                }
            }
        }

        request_actions_ = nullptr;
        ProtoFace::WaitForResponse( );
    }

}; // class ActionInterface

} // namespace sc2

/*\fn virtual void UnitCommand(Tag unit_tag, uint32_t ability)
 * Batches a UnitCommand that will be dispatched when SendActions() is called.
 * UnitCommand has many overloaded functions, you can call it with most
 * combinations of Unit types (the Unit object or tag), ability types (the enum
 * or uint32_t) and targets (a 2D position or tag). \param unit_tag The unique
 * id that represents the unit. \param ability The unique id that represents the
 * ability, see ABILITY_ID for ids. \sa ABILITY_ID Unit Point2D SendActions()
 */
