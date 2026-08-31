module;
#include <iostream>
#include <mutex>
#include <queue>
#include <utility>
#include <vector>

#include <s2clientprotocol/sc2api.pb.h>

#include "civetweb.h"
export module server;


export namespace sc2 {
using namespace std;

bool VERBOSE = false;

using RequestData  = pair<mg_connection*, SC2APIProtocol::Request*>;
using ResponseData = pair<mg_connection*, SC2APIProtocol::Response*>;

/*! @brief A basic websocket server for sc2.*/
class Server {
public:
    ~Server ( ) {
        mg_stop ( mg_context_ );
    }

    static bool GetServerData (
        const mg_connection* conn, void* data, Server*& out
    ) {
        if ( !conn ) {
            return false;
        }

        if ( !data ) {
            return false;
        }

        out = static_cast<Server*> ( data );
        return true;
    }

    static int WebSocketConnectHandler (
        const mg_connection* conn, void* websocket_server
    ) {
        if ( VERBOSE )
            std::cout << "Client connected (" << conn << ")" << '\n';
        Server* server;
        if ( !GetServerData ( conn, websocket_server, server ) ) {
            return 0;
        }

        server->connections_.push_back ( conn );

        return 0;
    }

    static int WebSocketDataHandler (
        mg_connection* conn,
        int /*flags*/,
        const char* data,
        size_t      len,
        void*       websocket_server
    ) {
        Server* server;
        if ( !GetServerData ( conn, websocket_server, server ) ) {
            return 0;
        }

        if ( VERBOSE )
            std::cout << "Client data (" << conn << ")" << '\n';

        SC2APIProtocol::Request* request = new SC2APIProtocol::Request( );
        if ( !request->ParseFromArray ( data, static_cast<int> ( len ) ) ) {
            // The server can only receive valid requests off civetweb threads.
            // Otherwise, die.
            return 0;
        }

        server->QueueRequest ( conn, request );

        return 1;
    }

    static void WebSocketCloseHandler (
        const mg_connection* conn, void* websocket_server
    ) {
        Server* server;
        if ( !GetServerData ( conn, websocket_server, server ) ) {
            return;
        }

        // Convert to blz::erase_if
        for ( size_t i = 0; i < server->connections_.size( ); ++i ) {
            if ( const mg_connection* target =
                     const_cast<mg_connection*> ( server->connections_[i] );
                 target == conn )
            {
                server->connections_.erase (
                    server->connections_.begin( ) + i
                );
                break;
            }
        }
    }

    template<class T>
    static void SendMessage (
        mg_connection* conn, std::queue<T>& message_queue
    ) {
        if ( message_queue.empty( ) ) {
            return;
        }

        if ( VERBOSE )
            std::cout << "SendMessage (" << conn << ")" << '\n';

        const google::protobuf::Message* message =
            message_queue.front( ).second;
        const size_t size  = message->ByteSizeLong( );
        char*        bytes = new char[size];
        if ( !message->SerializeToArray ( bytes, static_cast<int> ( size ) ) )
            cout << "`SendMessage` failed due to serialization exceeding "
                    "maximum protobuf size of 2GB:"
                 << size << '\n';
        mg_websocket_write ( conn, MG_WEBSOCKET_OPCODE_BINARY, bytes, size );
        message_queue.pop( );
        delete[] bytes;
        delete message;
    }

    bool Listen (
        const char* listeningPorts,
        const char* requestTimeoutMs,
        const char* websocketTimeoutMs,
        const char* numThreads
    ) {
        const char* options[] = {
            "listening_ports",
            listeningPorts,
            "request_timeout_ms",
            requestTimeoutMs,
            "websocket_timeout_ms",
            websocketTimeoutMs,
            "num_threads",
            numThreads,
            "tcp_nodelay",
            "1",
            nullptr,
        };

        constexpr mg_callbacks callbacks = { };
        mg_context_ = mg_start ( &callbacks, nullptr, options );

        if ( !mg_context_ ) {
            return false;
        }

        mg_set_websocket_handler (
            mg_context_,
            "/sc2api",
            WebSocketConnectHandler,
            nullptr,
            reinterpret_cast<mg_websocket_data_handler> (
                WebSocketDataHandler
            ),
            WebSocketCloseHandler,
            this
        );

        return true;
    }

    void QueueRequest (
        mg_connection* conn, SC2APIProtocol::Request*& request
    ) {
        request_mutex_.lock( );
        requests_.push ( RequestData ( conn, request ) );
        request_mutex_.unlock( );
    }

    void QueueResponse (
        mg_connection* conn, SC2APIProtocol::Response*& response
    ) {
        response_mutex_.lock( );
        responses_.push ( ResponseData ( conn, response ) );
        response_mutex_.unlock( );
    }

    // If no connection is provided send it to the first connection attained.
    void SendRequest ( mg_connection* conn = nullptr ) {
        request_mutex_.lock( );
        SendMessage (
            conn ? conn : const_cast<mg_connection*> ( connections_.front( ) ),
            requests_
        );
        request_mutex_.unlock( );
    }

    void SendResponse ( mg_connection* conn = nullptr ) {
        response_mutex_.lock( );
        SendMessage (
            conn ? conn : const_cast<mg_connection*> ( connections_.front( ) ),
            responses_
        );
        response_mutex_.unlock( );
    }

    bool HasRequest ( ) {
        request_mutex_.lock( );
        const bool empty = requests_.empty( );
        request_mutex_.unlock( );
        return !empty;
    }

    bool HasResponse ( ) {
        response_mutex_.lock( );
        const bool empty = responses_.empty( );
        response_mutex_.unlock( );
        return !empty;
    }

    const RequestData& PeekRequest ( ) {
        return requests_.front( );
    }

    const ResponseData& PeekResponse ( ) {
        return responses_.front( );
    }

    vector<const mg_connection*> connections_;

private:
    mg_context* mg_context_ = nullptr;

    queue<RequestData>  requests_;
    queue<ResponseData> responses_;

    mutex request_mutex_;
    mutex response_mutex_;
};

} // namespace sc2
