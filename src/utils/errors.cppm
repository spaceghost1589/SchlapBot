module;

#include <fstream>
#include <iostream>
#include <queue>
#include <source_location>
#include <sstream>
#include <string>
export module errors;
import enum_db;

using std::cerr, std::endl, std::ofstream, std::ostringstream, std::queue,
        std::source_location, std::string;

export namespace sc2 {

string LocParse (source_location loc) {
    ostringstream err_msg;
    err_msg << "[" << loc.file_name( ) << ":" << loc.line( ) << "."
            << loc.column( ) << "::" << loc.function_name( ) << "]:";
    return err_msg.str( );
}

//! @breif Custom assert
inline bool Assert (
        bool            bool_,
        const char*     msg = "",
        source_location loc = source_location::current( )
) {
    if ( bool_ )
        return true;
    else
        cerr << LocParse(loc) << msg << endl;
    return false;
}

struct ErrorLog {
    queue<ClientError> protocol_error;
    queue<ClientError> client_error;
    queue<ClientError>
};




// inline void Assert(const char* expr, const char* msg, const
// source_location& loc) {
//     // 1. Open a crash log file
//     ofstream crash_file("schlapbot_crash.log", std::ios::app);
//     if (crash_file.is_open()) {
//         crash_file << "[CRITICAL CRASH] " << loc.file_name() << ":" <<
//         loc.line() << "\n"
//                    << "  Failed Expression: " << expr << "\n"
//                    << "  Message: " << msg << "\n\n";
//     }
//
//     // 2. Also dump to stderr just in case someone is watching the
//     console cerr << "[CRITICAL ASSERT FAILED] " << expr << " | " << msg
//     << "\n";
// }

// #ifdef SCHLAP_ENABLE_ASSERTS
// #define SCHLAP_ASSERT(condition, message)                                      \
//     do {                                                                       \
//         if ( !(condition) ) {                                                  \
//             logAssertionFailure (                                              \
//                     #condition,                                                \
//                     message,                                                   \
//                     std::source_location::current( )                           \
//             );                                                                 \
//             std::abort( );                                                     \
//         }                                                                      \
//     } while ( 0 )
// #else
// #define SCHLAP_ASSERT(condition, message) ((void) 0)
// #endif

struct ClientConnectionError : std::runtime_error {
    ClientConnectionError (const std::string& net_address_, int port_):
            std::runtime_error (
                    "Failed connect to client " +
                    net_address_ +
                    ":" +
                    std::to_string (port_)
            ) {}
};

} // namespace sc2
