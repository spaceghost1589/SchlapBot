module;
#include <atomic>
#include <cassert>
#include <chrono>
#include <civetweb.h>
#include <condition_variable>
#include <deque>
#include <functional>
#include <iostream>
#include <malloc.h>
#include <mutex>
#include <source_location> // IWYU pragma: keep
#include <string>

#include <s2clientprotocol/sc2api.pb.h>
export module connection;
import error_handler;

namespace {

using std::cerr;
using std::cout;
using std::deque;
using std::mutex;

} // namespace

namespace {

bool StartCivetweb ( ) {
    static bool is_initialized = false;

    if ( is_initialized ) {
        return true;
    }

    const char *options[] = { "request_timeout_ms",
                              "5000",
                              "websocket_timeout_ms",
                              "1200000",
                              "num_threads",
                              "4",
                              "tcp_nodelay",
                              "1",
                              nullptr };

    constexpr mg_callbacks callbacks { };

    mg_init_data mg_start_init_data { };
    mg_start_init_data.callbacks             = &callbacks;
    mg_start_init_data.configuration_options = options;

    mg_error_data mg_start_error_data    = { };
    char          ebuff[256]             = { };
    mg_start_error_data.text             = ebuff;
    mg_start_error_data.text_buffer_size = sizeof ( ebuff );

    if (
      const auto *ctx = mg_start2 ( &mg_start_init_data, &mg_start_error_data );
      !ctx
    )
    {
        cerr << "Failed to start civetweb server: " << ebuff << '\n';
        return false;
    }

    is_initialized = true;
    return true;
}

} // anonymous namespace

namespace sc2 {

/*! This class acts as a wrapper around a websocket connection and queue
    responsible for both sending out and receiving protobuf messages.*/
export class Connection {
    //! A queue that contains responses received off the socket.
    deque<SC2APIProtocol::Response *> queue_;

    //! Mutex used in conjunction with the condition.
    mutex mutex_;

    /*! A condition that is signaled when a message has been received off the
     * socket.*/
    condition_variable condition_ { };

    /*! Thread safe bool to check whether the queue is not empty.*/
    atomic_bool has_response_ { false };
    /*! Will print extra information to console if enabled.*/
    bool        verbose_ { false };

    //! A pointer to the civetweb connection object.
    mg_connection *connection_;

public:
    Connection ( )
      : connection_ ( nullptr ) { }

    ~Connection ( ) {
        Disconnect( );
    }

    /*! @brief Sends a request via the websocket connection. This function
     * assumes Connect has been called and returned success. It will assert in
     * debug if that's not the case and will early out in a build that doesn't
     * have asserts built in. This function also allocates a byte buffer to
     * accommodate the request, it frees that buffer before returning.
     * @param request A pointer to the Request object.*/
    void Send ( const SC2APIProtocol::Request *request ) const {
        if ( !request ) {
            return;
        }
        // Connection must be established before sending.
        assert ( connection_ );
        if ( !connection_ ) {
            return;
        }
        const size_t size   = request->ByteSizeLong( );
        void        *buffer = malloc ( size );
        if ( !request->SerializeToArray ( buffer, static_cast<int> ( size ) ) )
            cout << "`Send` failed due to serialization exceeding maximum "
                    "protobuf size of 2GB:"
                 << size << '\n';
        mg_websocket_write (
          connection_,
          MG_WEBSOCKET_OPCODE_BINARY,
          static_cast<const char *> ( buffer ),
          size
        );

        free ( buffer );

        if ( verbose_ ) {
            cout << "Sending: " << request->DebugString( );
        }
    }

    /*! @brief Receive will block until a message is received from its websocket
     * connection. If a message is not received within the timeout it will set
     * response to null and return false, it also calls a timeout callback that
     * can be used if a user has any timeout logic.
     * @param response The response pointer to be filled out.
     * @param timeout_ms The max time, in milliseconds, the function will wait
     * to receive a message.
     * @return Returns true if a message is received, false otherwise.*/
    bool Receive (
      SC2APIProtocol::Response *&response,
      unsigned int               timeout_ms
    ) {
        unique_lock<mutex> lock ( mutex_ );
        // Block until a message is received.
        if ( verbose_ ) {
            cout << "Waiting for response..." << '\n';
        }
        if (
          const auto now = chrono::system_clock::now( ); condition_.wait_until (
            lock,
            now + chrono::milliseconds ( timeout_ms ),
            [&] {
            return queue_.size( ) != 0;
        }
          )
        )
        {
            lock.unlock( );
            PopResponse ( response );
            return true;
        }

        lock.unlock( );
        response = nullptr;
        Disconnect( );
        queue_.clear( );

        // Execute the timeout callback if it exists.
        if ( timeout_callback_ ) {
            timeout_callback_( );
        }

        return false;
    }

    /*! @brief PushResponse is called by a civetweb thread when it receives a
     * message off the socket. Pushing a response triggers a condition and
     * enqueues a message. The condition will cause anyone currently blocking
     * for a response (if Receive is called) to wake up and be able to consume
     * that message.
     * @param response A pointer to the Response to queue.*/
    void PushResponse ( SC2APIProtocol::Response *&response ) {
        lock_guard<mutex> guard ( mutex_ );
        queue_.push_back ( response );
        condition_.notify_one( );
        has_response_ = true;
    }

    /*! @brief PopResponse is called in the Receive function when a message has
     * been received off of the civetweb thread. Alternatively you could poll
     * for responses with PollResponse and consume the message manually with
     * this function.
     * @param response The response pointer to be filled out.*/
    void PopResponse ( SC2APIProtocol::Response *&response ) {
        lock_guard<mutex> guard ( mutex_ );
        if ( queue_.empty( ) )
            return;
        response = queue_.front( );
        queue_.pop_front( );
        if ( queue_.empty( ) ) {
            has_response_ = false;
        }
    }

    /*! @brief An accessor function that a user can bind a timeout function to.
     * @param callback A functor or lambda that represents the callback.*/
    void SetTimeoutCallback ( const function<void( )> &callback ) {
        timeout_callback_ = callback;
    }

    void SetConnectionClosedCallback ( const function<void( )> &callback ) {
        connection_closed_callback_ = callback;
    }

    /*! @brief Whether or not the connection is valid.
     * @return true if the connection is valid, false otherwise.*/
    bool HasConnection ( ) const {
        return connection_ != nullptr;
    }

    /*! @brief Disconnect from the game if currently connected.*/
    void Disconnect ( ) {
        mg_close_connection ( connection_ );
        connection_ = nullptr;
    }

    /*! @brief Polls the queue in a thread safe way to check if a message has
     * been received.
     * @return true if there is a response in the queue, false otherwise.*/
    bool PollResponse ( ) {
        return has_response_;
    }



    function<void( )> timeout_callback_;           //! Timeout callback.
    function<void( )> connection_closed_callback_; //! Timeout callback.

    bool GetClientData ( const mg_connection *connection, Connection *&out ) {
        if ( !connection ) {
            return false;
        }

        const mg_context *context = mg_get_context ( connection );

        if ( !context ) {
            return false;
        }

        out = static_cast<Connection *> ( mg_get_user_data ( context ) );
        return true;
    } // GetClientData

    
    int DataHandler (
      const mg_connection *conn,
      int /*flags*/,
      const char *data,
      size_t      data_len,
      void *
    ) {
        Connection *sc2_connection;
        if ( !GetClientData ( conn, sc2_connection ) ) {
            return 0;
        }

        SC2APIProtocol::Response *response = new SC2APIProtocol::Response( );
        if ( !response->ParseFromArray ( data, static_cast<int> ( data_len ) ) )
        {
            return 1;
        }

        sc2_connection->PushResponse ( response );

        return 1;
    } // DataHandler


    void ConnectionClosedHandler ( const mg_connection *conn, void * ) {
        Connection *sc2_connection;
        if ( !GetClientData ( conn, sc2_connection ) ) {
            return;
        }

        if ( sc2_connection->connection_closed_callback_ ) {
            sc2_connection->connection_closed_callback_( );
        }
    } // ConnectionClosedHandler

    bool Connect ( const string &address, int port, bool verbose );

}; // class Connection

/*! @brief Connects via websocket on a given address/port.
 * @param address The address to connect to, will most commonly be used
 * locally so 127.0.0.1.
 * @param port The port to connect the, the default for s2api is 9168 unless
 * specified otherwise in settings.
 * @param verbose
 * @return Returns true if the connection was successful and false
 * otherwise.*/
// bool Connect ( const string &address, int port, bool verbose = true ) {
//     if ( !StartCivetweb( ) ) {
//         SRC_LocationOut ( "StartCivetweb Failed" );
//         return false;
//     }
//     verbose_ = verbose;
//
//     char ebuff[256] = { };
//
//     connection_ = mg_connect_websocket_client (
//       address.c_str( ),
//       port,
//       0,
//       ebuff,
//       256,
//       "/sc2api",
//       nullptr,
//       reinterpret_cast<mg_websocket_data_handler> ( DataHandler ),
//       ConnectionClosedHandler,
//       this
//     );
//
//     if ( !connection_ ) {
//         cerr << "Failed to establish websocket connection: " << ebuff
//              << '\n';
//         return false;
//     }
//
//     if ( verbose_ ) {
//         cout << "Connected..." << '\n';
//     }
//
//     return true;
// }



} // namespace sc2
