module;
// #include <fstream>
// #include <iostream>
// #include <memory>
// #include <mutex>
// #include <queue> // IWYU pragma: keep
// #include <source_location>
// #include <sstream>
// #include <string>
// #include <vector>
export module error_handler;
import std;
import enum_db;

export namespace sc2 {
using namespace std;

/*! @brief Errors that the api can encounter, if the OnError event in
 * ClientEvents is overwritten it will contain a list of errors encountered. */
enum class ClientError {
    ConnectionClosed, /*! The websocket connection has prematurely closed, this
                         could mean StarCraft II crashed or a websocket timeout
                         has occurred.*/
    InvalidAbilityRemap, /*! An ability was improperly mapped to an ability id
                            that doesn't exist.*/
    InvalidResponse,     /*! The response does not contain a field that was
                            expected.*/
    NoAbilitiesForTag,   /*! The unit does not have any abilities.*/
    ResponseMismatch,    /*! The response received from SC2 does not match the
                            request.*/
    ResponseNotConsumed, /*! A request was made without consuming the response
                            from the previous request, that puts this library in
                            an illegal state.*/
    SC2AppFailure,    /*! SC2 has either crashed or been forcibly terminated by
                         this library because it was not responding to requests.*/
    SC2ProtocolError, /*! The response from SC2 contains errors, most likely
                         meaning the API was not used in a correct way.*/
    SC2ProtocolTimeout, /*! A request was made and a response was not received
                           in the amount of time given by the timeout.*/
    WrongGameVersion, /*! A replay was attempted to be loaded in the wrong game
                         version.*/
    SC2UnknownStatus,
    ErrorSC2,
    NULL_ERROR, /*! Placeholder value; not an error.*/
};

/*! @brief Parses the code location of an error.
 * @result Outputs code location and custom error message.
 * @note "[file:line.column::function]: err_msg" */
void SRC_LocationOut (
    const char*     err_msg = "NO ERROR MESSAGE PROVIDED",
    source_location srcLoc  = source_location::current( )
) {
    // Strip the absolute directory path down to just the filename
    string_view file_path = srcLoc.file_name();
    if ( const auto last_slash = file_path.find_last_of("/\\"); last_slash != string_view::npos) {
        file_path.remove_prefix(last_slash + 1);
    }

    // clang-format off
    cerr << "[" << srcLoc.file_name( )
         << ":" << srcLoc.line( )
         << "." << srcLoc.column( )
         << "::" << srcLoc.function_name( )
         << "]: " << err_msg << endl;
    // clang-format on
}

//! @brief Custom assert
inline bool Assert (
    bool            bool_,
    const char*     msg = "",
    source_location loc = source_location::current( )
) {
    if ( bool_ )
        return true;
    else
        SRC_LocationOut ( msg, loc );
#if !BUILD_FOR_LADDER
    abort( );
#endif
    return false;
}

struct ClientConnectionError : runtime_error
{
    ClientConnectionError ( const string& net_address_, int port_ )
          : runtime_error (
                "Failed connect to client " + net_address_ + ":" +
                to_string ( port_ )
            ) {}
};

} // namespace sc2

/*! @brief Error handling namespace to implement a "static class".\n
 * Handles errors that may have occurred during calls to the various
 * interfaces.*/
export namespace sc2::Error {

// TODO figure out something to do with errors in real-time.
// TODO Consider changing to `deque` or `queue`.

vector<ClientError> client_errors_;
vector<string>      protocol_errors_;

mutex error_mutex_;

inline void Log (
    const ClientError client_error = ClientError::NULL_ERROR,
    [[maybe_unused]] const vector<string>& protocol_errors = { }
) {
    // A ConnectionClosed error can come off a civetweb worker thread.
    const lock_guard guard ( error_mutex_ );

    // Cache client errors
    if ( client_error != ClientError::NULL_ERROR )
        client_errors_.push_back ( client_error );

    // Cache protocol errors
    for ( const string& err : protocol_errors ) {
        protocol_errors_.push_back ( err );
    }

    // TODO Refactor this for LADDER_BUILD and custom assert
    // #ifdef SC2API_ASSERT_ON_ERROR
    //     assert(0);
    // #endif
}

inline vector<ClientError>& GetClientErrors ( ) {
    return client_errors_;
}

inline vector<string>& GetProtocolErrors ( ) {
    return protocol_errors_;
}

inline void ClearClientErrors ( ) {
    client_errors_.clear( );
}

inline void ClearProtocolErrors ( ) {
    protocol_errors_.clear( );
}

} // namespace sc2::Error
