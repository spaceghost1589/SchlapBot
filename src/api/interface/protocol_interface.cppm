module;
#include <functional>
#include <iostream>
#include <memory>
#include <string>

#include <s2clientprotocol/sc2api.pb.h>

#include "api/connection.h"
// #include "api/control_interfaces.h"
export module protocol_interface;
import control_interface;
import enum_db;

using std::cerr, std::function, std::make_shared, std::shared_ptr, std::string,
        std::vector;

using Response = SC2APIProtocol::Response::ResponseCase;
using Request  = SC2APIProtocol::Request::RequestCase;

static_assert (
    int {Response::RESPONSE_NOT_SET} == int {Request::REQUEST_NOT_SET} &&
    int {Response::kCreateGame} == int {Request::kCreateGame} &&
    int {Response::kJoinGame} == int {Request::kJoinGame} &&
    int {Response::kRestartGame} == int {Request::kRestartGame} &&
    int {Response::kStartReplay} == int {Request::kStartReplay} &&
    int {Response::kLeaveGame} == int {Request::kLeaveGame} &&
    int {Response::kQuickSave} == int {Request::kQuickSave} &&
    int {Response::kQuickLoad} == int {Request::kQuickLoad} &&
    int {Response::kQuit} == int {Request::kQuit} &&
    int {Response::kGameInfo} == int {Request::kGameInfo} &&
    int {Response::kObservation} == int {Request::kObservation} &&
    int {Response::kAction} == int {Request::kAction} &&
    int {Response::kStep} == int {Request::kStep} &&
    int {Response::kData} == int {Request::kData} &&
    int {Response::kQuery} == int {Request::kQuery} &&
    int {Response::kSaveReplay} == int {Request::kSaveReplay} &&
    int {Response::kReplayInfo} == int {Request::kReplayInfo} &&
    int {Response::kAvailableMaps} == int {Request::kAvailableMaps} &&
    int {Response::kSaveMap} == int {Request::kSaveMap} &&
    int {Response::kPing} == int {Request::kPing} &&
    int {Response::kDebug} == int {Request::kDebug} &&
    int {Response::kObsAction} == int {Request::kObsAction} &&
    int {Response::kMapCommand} == int {Request::kMapCommand},
    "Requests and responses should be of the exact same size and in the "
    "exact order."
);

const char* RequestResponseIDToName (int type) {
    switch ( type ) {
        case 0 : return "RESPONSE_NOT_SET";
        case 1 : return "CreateGame";
        case 2 : return "JoinGame";
        case 3 : return "RestartGame";
        case 4 : return "StartReplay";
        case 5 : return "LeaveGame";
        case 6 : return "QuickSave";
        case 7 : return "QuickLoad";
        case 8 : return "Quit";
        case 9 : return "GameInfo";
        case 10: return "Observation";
        case 11: return "Action";
        case 12: return "Step";
        case 13: return "Data";
        case 14: return "Query";
        case 15: return "SaveReplay";
        case 16: return "ReplayInfo";
        case 17: return "AvailableMaps";
        case 18: return "SaveMap";
        case 19: return "Ping";
        case 20: return "Debug";
        case 21: return "kObsAction";
        case 22: return "kMapCommand";
    }
    return "RESPONSE_NOT_SET";
}

namespace {

class ControlInterface;

} // namespace

export namespace sc2 {


// A generous 120 seconds.
constexpr unsigned int kDefaultProtoInterfaceTimeout = 120000;

using GameRequestPtr  = shared_ptr<SC2APIProtocol::Request>;
using GameResponsePtr = shared_ptr<SC2APIProtocol::Response>;

template<class MessageType> class MessageResponsePtr {
public:
    MessageResponsePtr ( ):
        message_ (nullptr) {}

    void Set (const GameResponsePtr& response, const MessageType* message) {
        response_ = response;
        message_  = message;
    }

    bool HasErrors ( ) const {
        if ( !HasResponse( ) ) return true;
        if ( response_->error_size( ) > 0 ) return true;
        if ( !HasMessage( ) ) return true;
        return false;
    }

    void Clear ( ) {
        message_  = nullptr;
        response_ = nullptr;
    }

    const MessageType* operator ->( ) const {
        assert (message_);
        return message_;
    }

    const MessageType* get ( ) const {
        assert (message_);
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

// Wraps protocol and connections.
class ProtocolInterface {
public:
    ProtocolInterface ( ):
        address_ ("127.0.0.1"),
        port_ (5000),
        default_timeout_ms_ (kDefaultProtoInterfaceTimeout),
        latest_status_ (SC2APIProtocol::Status::unknown),
        response_pending_ (SC2APIProtocol::Response::RESPONSE_NOT_SET) {}

    bool ConnectToGame (const string& address, int port, int timeout_ms) {
        latest_status_      = SC2APIProtocol::Status::unknown;
        address_            = address;
        port_               = port;
        default_timeout_ms_ = timeout_ms;
        if ( !connection_.Connect (address, port, false) ) {
            return false;
        }
        connection_.SetConnectionClosedCallback ([&] {
            control_->Error (ClientError::ConnectionClosed);
        });
        return PingGame( );
    }

    static GameRequestPtr MakeRequest ( ) {
        return make_shared<SC2APIProtocol::Request> (
                SC2APIProtocol::Request( )
        );
    }

    bool SendRequest (
            const GameRequestPtr& request, bool ignore_pending_requests = false
    ) {
        const uint32_t request_type = (request->request_case( ));
        if ( request_type >= count_uses_.size( ) ) {
            const uint32_t current =
                    static_cast<uint32_t> (count_uses_.size( ));
            count_uses_.resize (request_type + 1);
            for ( uint32_t i = current; i < request_type + 1; ++i ) {
                count_uses_[i] = 0;
            }
        }
        ++count_uses_[request_type];

        // If there is no connection, try rebuilding the connection.
        if ( !connection_.HasConnection( ) ) {
            if ( !connection_.Connect (address_, port_, false) ) {
                return false;
            }
        }

        // If there is still no connection, give up.
        if ( !connection_.HasConnection( ) ) {
            return false;
        }

        // Technically there can be new requests while responses are pending,
        // but this library is not written for that. For now, make everything
        // purely sequential.
        // TODO allow for message queue
        if ( !ignore_pending_requests && HasResponsePending( ) ) {
            control_->Error (ClientError::ResponseNotConsumed);
            return false;
        }

        connection_.Send (request.get( ));

        // Expect a certain response.
        response_pending_ = static_cast<Response> (request->request_case( ));
        return true;
    }

    GameResponsePtr WaitForResponseInternal ( ) {
        latest_status_                     = SC2APIProtocol::Status::unknown;
        SC2APIProtocol::Response* response = nullptr;
        if ( !connection_.Receive (response, default_timeout_ms_) ) {
            // If the receive fails, it means a timeout has occurred.
            return nullptr;
        }

        for ( int i = 0;
              error_callback_ && response && i < response->error_size( );
              ++i ) {
            error_callback_ (response->error (i));
        }

        if ( response ) {
            if ( response->has_status( ) ) {
                latest_status_ = response->status( );
            }
            if ( response->error_size( ) > 0 ) {
                cerr << "While waiting for Response"
                     << RequestResponseIDToName (response_pending_)
                     << " received an error." << '\n';
                for ( int i = 0; i < response->error_size( ); ++i ) {
                    cerr << "Error: " << response->error (i) << '\n';
                }
            } else {
                if ( const Response actual_response =
                             response->response_case( );
                     response_pending_ != actual_response ) {
                    // This is bad, it means we did not get the response that
                    // matches the last request.
                    control_->Error (ClientError::ResponseMismatch);
                }
            }
        }

        // No longer expecting a specific response.
        response_pending_ = SC2APIProtocol::Response::RESPONSE_NOT_SET;
        return GameResponsePtr (response);
    }

    bool PingGame ( ) {
        // Send the request.
        const GameRequestPtr request = MakeRequest( );
        request->mutable_ping( );
        if ( !SendRequest (request, true) ) {
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

    void Quit ( ) {
        // Tell the game to close
        const GameRequestPtr request = MakeRequest( );
        request->mutable_quit( );
        SendRequest (request);

        // Immediately tear down connection. The callbacks may try to call into
        // objects who are in the process of being destroyed.
        connection_.Disconnect( );
    }

    void SetErrorCallback (
            const function<void (const string& error_str)>& error_callback
    ) {
        error_callback_ = error_callback;
    }

    bool PollResponse ( ) {
        return connection_.PollResponse( );
    }

    SC2APIProtocol::Status GetLastStatus ( ) const {
        return latest_status_;
    }

    bool HasResponsePending ( ) const {
        return response_pending_ != Response::RESPONSE_NOT_SET;
    }

    SC2APIProtocol::Response::ResponseCase GetResponsePending ( ) const {
        return response_pending_;
    }

    int GetAssignedPort ( ) const {
        return port_;
    }

    const vector<uint32_t>& GetStats ( ) const {
        return count_uses_;
    }

    void SetControl (ControlInterface* control) {
        control_ = control;
    }

    uint32_t GetBaseBuild ( ) const {
        return base_build_;
    }

    const string& GetDataVersion ( ) const {
        return data_version_;
    }

protected:
    Connection                               connection_;
    string                                   address_;
    int                                      port_;
    unsigned int                             default_timeout_ms_;
    function<void (const string& error_str)> error_callback_;
    SC2APIProtocol::Status                   latest_status_;
    SC2APIProtocol::Response::ResponseCase   response_pending_;
    vector<uint32_t>                         count_uses_;
    ControlInterface*                        control_;
    uint32_t                                 base_build_ {0};
    string                                   data_version_;
};

// Helper to produce a string for the proto type.
const char* RequestResponseIDToName (int type);

using ResponseDataPtr = MessageResponsePtr<SC2APIProtocol::ResponseData>;
using ResponseGameInfoPtr =
        MessageResponsePtr<SC2APIProtocol::ResponseGameInfo>;
using ResponseObservationPtr =
        MessageResponsePtr<SC2APIProtocol::ResponseObservation>;
using ResponsePingPtr   = MessageResponsePtr<SC2APIProtocol::ResponsePing>;
using ResponseQueryPtr  = MessageResponsePtr<SC2APIProtocol::ResponseQuery>;
using ObservationPtr    = MessageResponsePtr<SC2APIProtocol::Observation>;
using ObservationRawPtr = MessageResponsePtr<SC2APIProtocol::ObservationRaw>;
using ObservationRenderPtr =
        MessageResponsePtr<SC2APIProtocol::ObservationRender>;
using ScorePtr        = MessageResponsePtr<SC2APIProtocol::Score>;
using ScoreDetailsPtr = MessageResponsePtr<SC2APIProtocol::ScoreDetails>;

using SharedProtocolInterface = shared_ptr<ProtocolInterface>;

} // namespace sc2
