//
// Created by Sean on 20-Aug-26.
//

export module action_interface;

//! The ActionInterface issues actions to units in a game. Not available in
//! replays. Guaranteed to be valid when the OnStep event is called.
class ActionInterface {
public:
    virtual ~ActionInterface() = default;

    /*!fn virtual void UnitCommand(Tag unit_tag, uint32_t ability)
     * brief Batches a UnitCommand that will be dispatched when SendActions() is
     * called. UnitCommand has many overloaded functions, you can call it with
     * most combinations of Unit types (the Unit object or tag), ability types
     * (the enum or uint32_t) and targets (a 2D position or tag). param unit_tag
     * The unique id that represents the unit. param * ability The unique id
     * that represents the ability, see ABILITY_ID for ids. sa ABILITY_ID Unit
     * Point2D SendActions()
     */

    //! Issues a command to a unit. Self targeting.
    //! \param unit The unit to send the command to.
    //! \param ability The ability id of the command.
    //! \param queued_command
    virtual void UnitCommand(const Unit* unit,
                             AbilityID   ability,
                             bool        queued_command = false) = 0;

    //! Issues a command to a unit. Targets a point.
    //! \param unit The unit to send the command to.
    //! \param ability The ability id of the command.
    //! \param point The 2D world position to target.
    //! \param queued_command
    virtual void UnitCommand(const Unit*    unit,
                             AbilityID      ability,
                             const Point2D& point,
                             bool           queued_command = false) = 0;

    //! Issues a command to a unit. Targets another unit.
    //! \param unit The unit to send the command to.
    //! \param ability The ability id of the command.
    //! \param target The unit that is a target of the unit getting the command.
    //! \param queued_command
    virtual void UnitCommand(const Unit* unit,
                             AbilityID   ability,
                             const Unit* target,
                             bool        queued_command = false) = 0;

    //! Issues a command to multiple units (prefer this where possible). Same as
    //! UnitCommand(Unit, AbilityID).
    virtual void UnitCommand(const Units& units,
                             AbilityID    ability,
                             bool         queued_move = false) = 0;

    //! Issues a command to multiple units (prefer this where possible). Same as
    //! UnitCommand(Unit, AbilityID, Point2D).
    virtual void UnitCommand(const Units&   units,
                             AbilityID      ability,
                             const Point2D& point,
                             bool           queued_command = false) = 0;

    //! Issues a command to multiple units (prefer this where possible). Same as
    //! UnitCommand(Unit, AbilityID, Unit).
    virtual void UnitCommand(const Units& units,
                             AbilityID    ability,
                             const Unit*  target,
                             bool         queued_command = false) = 0;

    //! Issues a command to a unit. Self targeting.
    //! \param tag Tag of unit.
    //! \param ability The ability id of the command.
    //! \param queued_command
    virtual void UnitCommand(Tag       tag,
                             AbilityID ability,
                             bool      queued_command = false) = 0;

    //! Issues a command to a unit. Targets a point.
    //! \param tag Tag of unit.
    //! \param ability The ability id of the command.
    //! \param point The 2D world position to target.
    //! \param queued_command
    virtual void UnitCommand(Tag            tag,
                             AbilityID      ability,
                             const Point2D& point,
                             bool           queued_command = false) = 0;

    //! Issues a command to a unit. Targets another unit.
    //! \param tag Tag of unit.
    //! \param ability The ability id of the command.
    //! \param target_tag Tag of unit that is a target of the unit getting the
    //! command.
    //! \param queued_command
    virtual void UnitCommand(Tag       tag,
                             AbilityID ability,
                             Tag       target_tag,
                             bool      queued_command = false) = 0;

    //! Issues a command to multiple units (prefer this where possible). Same as
    //! UnitCommand(Tag, AbilityID).
    //! \param tags Tags of units.
    //! \param ability
    //! \param queued_move
    virtual void UnitCommand(const Tags& tags,
                             AbilityID   ability,
                             bool        queued_move = false) = 0;

    //! Issues a command to multiple units (prefer this where possible). Same as
    //! UnitCommand(Tag, AbilityID, Point2D).
    //! \param tags Tags of units.
    //! \param ability
    //! \param point
    //! \param queued_command
    virtual void UnitCommand(const Tags&    tags,
                             AbilityID      ability,
                             const Point2D& point,
                             bool           queued_command = false) = 0;

    //! Issues a command to multiple units (prefer this where possible). Same as
    //! UnitCommand(Tag, AbilityID, Tag).
    //! \param tags Tags of units.
    //! \param ability
    //! \param target_tag
    //! \param queued_command
    virtual void UnitCommand(const Tags& tags,
                             AbilityID   ability,
                             Tag         target_tag,
                             bool        queued_command = false) = 0;

    //! Returns a list of unit tags that have sent commands out in the last call
    //! to SendActions. This will be used to determine if a unit actually has a
    //! command when the observation is received.
    //! \return Array of units that have sent commands.
    virtual const Tags& Commands() const = 0;

    //! Enables or disables autocast of an ability on a unit.
    //! \param unit_tag The unit to toggle the ability on.
    //! \param ability The ability to be toggled.
    virtual void ToggleAutocast(Tag unit_tag, AbilityID ability) = 0;

    //! Enables or disables autocast of an ability on a list of units.
    //! \param unit_tags The units to toggle the ability on.
    //! \param ability The ability to be toggled.
    virtual void ToggleAutocast(const Tags& unit_tags, AbilityID ability) = 0;

    //! Sends a message to the game chat.
    //! \param message Text of message to send.
    //! \param channel Which players will see the message.
    virtual void SendChat(const std::string& message,
                          ChatChannel        channel = ChatChannel::All) = 0;

    //! This function sends out all batched unit commands. You DO NOT need to
    //! call this function in non real time simulations since it is
    //! automatically called when stepping the simulation forward. You only need
    //! to call this function in a real time simulation. For example, if you
    //! wanted to move 20 marines to some position on the map you'd want to
    //! batch all of those unit commands and send them at once.
    virtual void SendActions() = 0;
};
