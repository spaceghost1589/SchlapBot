export module enum_db;

export namespace sc2 {

//! Errors that the api can encounter, if the OnError event in ClientEvents is
//! overwritten it will contain a list of errors encountered.
enum class ClientError {
    ErrorSC2,
    //! An ability was improperly mapped to an ability id that doesn't exist.
    InvalidAbilityRemap,
    //! The response does not contain a field that was expected.
    InvalidResponse,
    //! The unit does not have any abilities.
    NoAbilitiesForTag,
    //! A request was made without consuming the response from the previous
    //! request, that puts this library in an illegal state.
    ResponseNotConsumed,
    //! The response received from SC2 does not match the request.
    ResponseMismatch,
    //! The websocket connection has prematurely closed, this could mean
    //! starcraft crashed or a websocket timeout has occurred.
    ConnectionClosed,
    SC2UnknownStatus,
    //! SC2 has either crashed or been forcibly terminated by this library
    //! because it was not responding to requests.
    SC2AppFailure,
    //! The response from SC2 contains errors, most likely meaning the API was
    //! not used in a correct way.
    SC2ProtocolError,
    //! A request was made and a response was not received in the amount of time
    //! given by the timeout.
    SC2ProtocolTimeout,
    //! A replay was attempted to be loaded in the wrong game version.
    WrongGameVersion,
};

enum class AppTest { hang = 0, crash = 1, exit = 2 };



// using UnitTypeID = SC2Type<UNIT_TYPEID>;
// using AbilityID = SC2Type<ABILITY_ID>;
// using UpgradeID = SC2Type<UPGRADE_ID>;
// using BuffID = SC2Type<BUFF_ID>;
// using EffectID = SC2Type<EFFECT_ID>;

// //! Converts a UNIT_TYPEID into a string of the same name.
// const char* UnitTypeToName(UnitTypeID id);
//
// //! Converts a ABILITY_ID into a string of the same name.
// const char* AbilityTypeToName(AbilityID id);
//
// //! Converts a UPGRADE_ID into a string of the same name.
// const char* UpgradeIDToName(UpgradeID id);
//
// //! Converts a BUFF_ID into a string of the same name.
// const char* BuffIDToName(BuffID id);
//
// //! Converts a EFFECT_ID into a string of the same name.
// const char* EffectIDToName(EffectID id);

} // namespace sc2
