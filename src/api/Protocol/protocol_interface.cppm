module;
#include <functional>
#include <iostream>
#include <memory>
#include <string>

#include <s2clientprotocol/sc2api.pb.h>

#include "utils/manage_process.h"
export module protocol_interface;
import connection;
import enum_db;
import error_handler;
import game_settings;


using Response = SC2APIProtocol::Response::ResponseCase;
using Request  = SC2APIProtocol::Request::RequestCase;

//! Helper to produce a string for the protocol type.
const char* RequestResponseIDToName ( int type ) {
    switch ( type ) {
        case 1  : return "CreateGame";
        case 2  : return "JoinGame";
        case 3  : return "RestartGame";
        case 4  : return "StartReplay";
        case 5  : return "LeaveGame";
        case 6  : return "QuickSave";
        case 7  : return "QuickLoad";
        case 8  : return "Quit";
        case 9  : return "GameInfo";
        case 10 : return "Observation";
        case 11 : return "Action";
        case 12 : return "Step";
        case 13 : return "Data";
        case 14 : return "Query";
        case 15 : return "SaveReplay";
        case 16 : return "ReplayInfo";
        case 17 : return "AvailableMaps";
        case 18 : return "SaveMap";
        case 19 : return "Ping";
        case 20 : return "Debug";
        case 21 : return "kObsAction";
        case 22 : return "kMapCommand";
        default : return "RESPONSE_NOT_SET";
    }
}

export namespace sc2 {
using namespace std;

// A generous 120 seconds.
constexpr unsigned int kDefaultProtoInterfaceTimeout = 120000;

using GameRequestPtr  = shared_ptr<SC2APIProtocol::Request>;
using GameResponsePtr = shared_ptr<SC2APIProtocol::Response>;

template<class MessageType> class MessageResponsePtr {
public:
    MessageResponsePtr ( )
          : message_ ( nullptr ) {}

    void Set ( const GameResponsePtr& response, const MessageType* message ) {
        response_ = response;
        message_  = message;
    }

    bool HasErrors ( ) const {
        if ( !HasResponse( ) )
            return true;
        else if ( response_->error_size( ) > 0 )
            return true;
        else if ( !HasMessage( ) )
            return true;

        return false;
    }

    void Clear ( ) {
        message_  = nullptr;
        response_ = nullptr;
    }

    const MessageType* operator ->( ) const {
        Assert ( message_ );
        return message_;
    }

    const MessageType* get ( ) const {
        Assert ( message_ );
        return message_;
    }

    GameResponsePtr GetResponse ( ) const {
        return response_;
    }

    bool HasResponse ( ) const {
        return response_.get( ) != nullptr;
    }

    bool HasMessage ( ) const {
        return message_ != nullptr;
    }

private:
    const MessageType* message_;
    GameResponsePtr    response_;
};

/*! Protocol Interface - Wraps protocol and connections.*/
namespace ProtoFace {

Connection   connection_;
string       address_ { "127.0.0.1" };
int          port_ { 5000 };
unsigned int default_timeout_ms_ ( kDefaultProtoInterfaceTimeout );
function<void ( const string& error_str )> error_callback_;

ProcessInfo pi_;

SC2APIProtocol::Status latest_status_ ( SC2APIProtocol::Status::unknown );
SC2APIProtocol::Response::ResponseCase response_pending_ (
    SC2APIProtocol::Response::RESPONSE_NOT_SET
);

vector<uint32_t> count_uses_;
uint32_t         base_build_ { 0 };
string           data_version_;

//! Creates an empty Request. Needs to be set.
GameRequestPtr MakeRequest ( ) {
    return make_shared<SC2APIProtocol::Request> ( SC2APIProtocol::Request( ) );
}

void SetErrorCallback (
    const function<void ( const string& error_str )>& error_callback
) {
    error_callback_ = error_callback;
}

bool PollResponse ( ) {
    return connection_.PollResponse( );
}

SC2APIProtocol::Status GetLastStatus ( ) {
    return latest_status_;
}

bool HasResponsePending ( ) {
    return response_pending_ != Response::RESPONSE_NOT_SET;
}

SC2APIProtocol::Response::ResponseCase GetResponsePending ( ) {
    return response_pending_;
}

int GetAssignedPort ( ) {
    return port_;
}

const vector<uint32_t>& GetStats ( ) {
    return count_uses_;
}

uint32_t GetBaseBuild ( ) {
    return base_build_;
}

const string& GetDataVersion ( ) {
    return data_version_;
}

/*! @brief
 * @param request
 * @param ignore_pending_requests
 * @returns The success or failure of the SendRequest. */
bool SendRequest (
    const GameRequestPtr& request, bool ignore_pending_requests = false
) {
    const uint32_t request_type = ( request->request_case( ) );
    if ( request_type >= count_uses_.size( ) ) {
        const uint32_t current = static_cast<uint32_t> ( count_uses_.size( ) );
        count_uses_.resize ( request_type + 1 );
        for ( uint32_t i = current; i < request_type + 1; ++i ) {
            count_uses_[i] = 0;
        }
    }
    ++count_uses_[request_type];

    // If there is no connection, try rebuilding the connection.
    if ( !connection_.HasConnection( ) ) {
        if ( !connection_.Connect ( address_, port_, false ) ) {
            return false;
        }
    }

    // If there is still no connection, give up.
    if ( !connection_.HasConnection( ) ) {
        return false;
    }

    /* Technically there can be new requests while responses are pending, but
     * this library is not written for that. For now, make everything purely
     * sequential.*/
    // TODO allow for message queue
    if ( !ignore_pending_requests && HasResponsePending( ) ) {
        Error::Log ( ClientError::ResponseNotConsumed );
        return false;
    }

    connection_.Send ( request.get( ) );

    // Expect a certain response.
    response_pending_ = static_cast<Response> ( request->request_case( ) );
    return true;
}

GameResponsePtr WaitForResponseInternal ( ) {
    latest_status_                     = SC2APIProtocol::Status::unknown;
    SC2APIProtocol::Response* response = nullptr;
    if ( !connection_.Receive ( response, default_timeout_ms_ ) ) {
        // If the receive fails, it means a timeout has occurred.
        return nullptr;
    }

    for ( int i = 0; error_callback_ && response && i < response->error_size( );
          ++i )
    {
        error_callback_ ( response->error ( i ) );
    }

    if ( response ) {
        if ( response->has_status( ) ) {
            latest_status_ = response->status( );
        }
        if ( response->error_size( ) > 0 ) {
            cerr << "While waiting for Response"
                 << RequestResponseIDToName ( response_pending_ )
                 << " received an error." << '\n';
            for ( int i = 0; i < response->error_size( ); ++i ) {
                cerr << "LogError: " << response->error ( i ) << '\n';
            }
        } else {
            if ( const Response actual_response = response->response_case( );
                 response_pending_ != actual_response )
            {
                // This is bad, it means we did not get the response
                // that matches the last request.
                Error::Log ( ClientError::ResponseMismatch );
            }
        }
    }

    // No longer expecting a specific response.
    response_pending_ = SC2APIProtocol::Response::RESPONSE_NOT_SET;
    return GameResponsePtr ( response );
}

GameResponsePtr WaitForResponse ( ) {
    assert ( app_state == AppState::Normal );

    GameResponsePtr response = WaitForResponseInternal( );

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

    /* The game application did not responded, the previous request was either
     * not sent or the app is non-responsive. */

    /* Step 1: distinguish between a hang and a crash. Lots of time has elapsed,
     * so if there was a crash it should have finished by now. */
    assert ( pi_.process_id );
    if ( !IsProcessRunning ( pi_.process_id ) ) {
        app_state = AppState::Crashed;
        cout << "Game application has terminated unexpectedly." << '\n';
        Error::Log ( ClientError::SC2AppFailure );
        return response;
    }

    /* Step 2: distinguish between a non-responsive app and a failure to deliver
     * a valid request. */
    {
        const GameRequestPtr ping_request = MakeRequest( );
        ping_request->mutable_ping( );
        if ( !SendRequest ( ping_request, true ) ) {
            // Mark the game app as unresponsive.
            app_state = AppState::Timeout;
            Error::Log ( ClientError::SC2ProtocolTimeout );
        } else {
            /* Wait for a ping response. If this fails, the game is
             * unresponsive. */
            // TODO (?): Implement a timeout parameter for this wait.
            const GameResponsePtr response_ping = WaitForResponseInternal( );
            if ( response_ping ) {
                if ( GetLastStatus( ) == SC2APIProtocol::Status::unknown ) {
                    Error::Log ( ClientError::SC2UnknownStatus );
                }

                /* The game is responsive, but there was another problem. This
                 * isn't the right place to handle another type of problem. Just
                 * return the nullptr. */
                Error::Log ( ClientError::SC2UnknownStatus );
                return response;
            }

            app_state = AppState::Timeout;
            Error::Log ( ClientError::SC2ProtocolTimeout );
        }
    }

    // The game application has hanged. Try and terminate it.
    app_state = AppState::Timeout;
    for ( int i = 0; i < 10 && IsProcessRunning ( pi_.process_id ); ++i ) {
        TerminateProcess ( pi_.process_id );
        SleepFor ( 2000 );
    }

    if ( IsProcessRunning ( pi_.process_id ) ) {
        // Failed to kill the running process.
        app_state = AppState::Timeout_Zombie;
    }

    cout << "Game application has been terminated due to unresponsiveness."
         << '\n';
    Error::Log ( ClientError::SC2AppFailure );
    return response;
}

inline bool PingGame ( ) {
    // Send the request.
    const GameRequestPtr request = MakeRequest( );
    request->mutable_ping( );
    if ( !SendRequest ( request, true ) ) {
        return false;
    }

    // Wait for the return of the ping.
    // TODO: Implement a time out here.
    const GameResponsePtr response = WaitForResponseInternal( );
    if ( !response.get( ) || !response->has_ping( ) ) {
        return false;
    }

    const auto& response_ping = response->ping( );
    base_build_               = response_ping.base_build( );
    data_version_             = response_ping.data_version( );
    return true;
}

bool ConnectToGame ( const string& address, int port, int timeout_ms ) {
    latest_status_      = SC2APIProtocol::Status::unknown;
    address_            = address;
    port_               = port;
    default_timeout_ms_ = timeout_ms;
    if ( !connection_.Connect ( address, port, false ) ) {
        return false;
    }
    connection_.SetConnectionClosedCallback ( [&] {
        Error::Log ( ClientError::ConnectionClosed );
    } );
    return PingGame( );
}

void DumpProtoUsage ( ) {
    const vector<uint32_t>& stats = GetStats( );
    cout << "******************************************************" << '\n';
    cout << "Protocol use by message type:" << '\n';
    for ( size_t i = 0; i < stats.size( ); ++i ) {
        if ( stats[i] == 0 ) {
            continue;
        }

        cout << to_string ( i ) << ": " << to_string ( stats[i] ) << '\n';
    }

    cout << "******************************************************" << '\n';
}

// Save/Load.
void Save ( ) {
    const GameRequestPtr request = MakeRequest( );
    request->mutable_quick_save( );
    if ( !SendRequest ( request ) ) {
        return;
    }
    WaitForResponse( );
}

void Load ( ) {
    const GameRequestPtr request = MakeRequest( );
    request->mutable_quick_load( );
    if ( !SendRequest ( request ) ) {
        return;
    }
    WaitForResponse( );
}

void Quit ( ) {
    // Tell the game to close
    const GameRequestPtr request = MakeRequest( );
    request->mutable_quit( );
    SendRequest ( request );

    /* Immediately tear down connection. The callbacks may try to call into
     * objects who are in the process of being destroyed. */
    connection_.Disconnect( );
} // Quit()

} // namespace ProtoFace

// clang-format off
using ResponseDataPtr =
    MessageResponsePtr<SC2APIProtocol::ResponseData>;
using ResponseGameInfoPtr =
    MessageResponsePtr<SC2APIProtocol::ResponseGameInfo>;
using ResponseObservationPtr =
    MessageResponsePtr<SC2APIProtocol::ResponseObservation>;
using ResponsePingPtr  =
    MessageResponsePtr<SC2APIProtocol::ResponsePing>;
using ResponseQueryPtr =
    MessageResponsePtr<SC2APIProtocol::ResponseQuery>;
using ObservationPtr =
    MessageResponsePtr<SC2APIProtocol::Observation>;
using ObservationRawPtr =
    MessageResponsePtr<SC2APIProtocol::ObservationRaw>;
using ObservationRenderPtr =
    MessageResponsePtr<SC2APIProtocol::ObservationRender>;
using ScorePtr =
    MessageResponsePtr<SC2APIProtocol::Score>;
using ScoreDetailsPtr =
    MessageResponsePtr<SC2APIProtocol::ScoreDetails>;
// clang-format on

} // namespace sc2

// clang-format off
using Response = SC2APIProtocol::Response::ResponseCase;
using Request  = SC2APIProtocol::Request::RequestCase;

static_assert (
     int { Response::RESPONSE_NOT_SET } == int { Request::REQUEST_NOT_SET }
    && int { Response::kCreateGame }    == int { Request::kCreateGame }
    && int { Response::kJoinGame }      == int { Request::kJoinGame }
    && int { Response::kRestartGame }   == int { Request::kRestartGame }
    && int { Response::kStartReplay }   == int { Request::kStartReplay }
    && int { Response::kLeaveGame }     == int { Request::kLeaveGame }
    && int { Response::kQuickSave }     == int { Request::kQuickSave }
    && int { Response::kQuickLoad }     == int { Request::kQuickLoad }
    && int { Response::kQuit }          == int { Request::kQuit }
    && int { Response::kGameInfo }      == int { Request::kGameInfo }
    && int { Response::kObservation }   == int { Request::kObservation }
    && int { Response::kAction }        == int { Request::kAction }
    && int { Response::kStep }          == int { Request::kStep }
    && int { Response::kData }          == int { Request::kData }
    && int { Response::kQuery }         == int { Request::kQuery }
    && int { Response::kSaveReplay }    == int { Request::kSaveReplay }
    && int { Response::kReplayInfo }    == int { Request::kReplayInfo }
    && int { Response::kAvailableMaps } == int { Request::kAvailableMaps }
    && int { Response::kSaveMap }       == int { Request::kSaveMap }
    && int { Response::kPing }          == int { Request::kPing }
    && int { Response::kDebug }         == int { Request::kDebug }
    && int { Response::kObsAction }     == int { Request::kObsAction }
    && int { Response::kMapCommand }    == int { Request::kMapCommand },
    "Requests and responses should be of the exact same size and in the exact order."
); // clang-format on
