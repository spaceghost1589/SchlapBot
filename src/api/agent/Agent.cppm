module;
#include <memory>
#include <cassert>

#include <s2clientprotocol/sc2api.pb.h>
export module Agent;
import Client;
import action_feature_layer_interface;
import action_interface;
import protocol_interface;
// import game_types;

export namespace sc2 {
using namespace std;

/*! @brief The base class for user defined bots.\n\n The Agent class provides a
 * user with most access into SC2 state and unit manipulation. A user will issue
 * actions to units via the ActionInterface, examine game state with the
 * ObservationInterface, issue blocking commands (such as pathing queries) via
 * the UnitQueryInterface and override library provided events in
 * ClientEvents.\n\n Merged with AgentControlInterface
 */
class Agent : public Client {
public:
    unique_ptr<ActionInterface>             actions_;
    unique_ptr<ActionFeatureLayerInterface> actions_feature_layer_;

    Agent ( )
          : actions_ ( nullptr ) {
        actions_               = make_unique<ActionInterface>( );
        actions_feature_layer_ = make_unique<ActionFeatureLayerInterface>( );
    }

    virtual bool Restart ( ) {
        const GameRequestPtr request = ProtoFace::MakeRequest( );
        request->mutable_restart_game( );
        if ( !ProtoFace::SendRequest ( request ) ) {
            return false;
        }

        const GameResponsePtr response = ProtoFace::WaitForResponse( );
        if ( !response.get( ) ) {
            assert ( 0 );
            return false;
        }
        if ( !response->has_restart_game( ) ) {
            assert ( 0 );
            return false;
        }
        const SC2APIProtocol::ResponseRestartGame& response_restart_game =
            response->restart_game( );
        if ( response_restart_game.has_error( ) ) {
            // TODO: Output the error.
            assert ( 0 );
            return false;
        }

        GetObservation( );
        OnGameStart( );

        return IsInGame( );
    }

    /*! @brief Interface for issuing actions to units. Actions should be batched
     * via the UnitCommand functions then eventually dispatched with
     * SendActions. If you are stepping the simulation yourself the Step will
     * automatically call SendActions. If your bot is running in real time you
     * must call SendActions yourself.
     * @return The raw (basic) action interface. */
    ActionInterface* Actions ( ) const {
        return actions_.get( );
    }

    /*! Interface for issuing actions in feature layers.
     * @return The feature layer action interface. */
    ActionFeatureLayerInterface* ActionsFeatureLayer ( ) const {
        return actions_feature_layer_.get( );
    }

    /*! The AgentControlInterface is only currently used for restarting a game.
     * \n\n For internal use.
     * @return The agent control interface. */
    // AgentControlInterface* AgentControl ( ) const {
    //     return agent_control_interface_;
    // }

    // private:
    // AgentControlInterface* agent_control_interface_;
}; // class Agent

} // namespace sc2
