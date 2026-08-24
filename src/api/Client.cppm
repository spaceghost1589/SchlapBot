/*!
*The Client and ClientEvents provides most of the functionality a user would be
interested in for examining game state and scripting bots. A user should prefer
to inherit from either Agent or ReplayObserver, those classes both inherit from
Client.
*/
module;
#include <string>
#include <vector>

#include <s2clientprotocol/debug.pb.h>

#include "api/data.h"
#include "api/proto_to_pods.h"
#include "api/unit.h"
#include "lib/action.h"
#include "lib/type_enums.h"
export module Client;
import :control_interface;
import :debug_interface;
import :observation_interface;
import :query_interface;
import enum_db;
import points;
import renderer;
import score;
import map_info;
import error_handler;

// enum class UPGRADE_ID;} using UpgradeID = sc2::SC2Type<sc2::UPGRADE_ID>;

namespace {

using std::function, std::numeric_limits;

class ControlInterface;
class QueryInterface;
class DebugInterface;

} // namespace

export namespace sc2 {

// Client  -  Client  -  Client  -  Client  -  Client  -  Client  -  Client  -

//! The base class for Agent and ReplayObserver.
//! A set of common events a user can override in their derived bot or replay
//! observer class.
class Client : ObservationImplementation
{
public:
    Client::Client ( ):
        Control_Interface_ ( nullptr ) {
        Control_Interface_ = new ControlImp ( *this );
    }

    virtual Client::~Client ( ) {
        delete Control_Interface_;
    }

    const ObservationInterface* Observation_Interface ( ) const {
        // TODO (?): Should this return a nullptr if the interface is not valid
        // (e.g., before a game is started)?
        return Control_Interface_->observation_impl_.get( );
    }

    //! The UnitQuery interface is used to issue commands to units.
    QueryInterface* Query_Interface ( ) const {
        // TODO (?): Should this return a nullptr if the interface is not valid
        // (e.g., before a game is started)?
        return Control_Interface_->query_impl_.get( );
    }

    //! The ControlInterface is only meant to be used by the Coordinator as it
    //! provides functionality for connecting to Starcraft2, setting up a
    //! websocket connection and issuing blocking commands via SC2's protocol.
    ControlInterface* Control_Interface ( ) {
        return Control_Interface_;
    }

    const ControlInterface* Control_Interface ( ) const {
        return Control_Interface_;
    }

    //! The DebugInterface allows a derived class to print text, draw primitive
    //! shapes and spawn/destroy units.
    DebugInterface* Debug_Interface ( ) const {
        return Control_Interface_->debug_impl_.get( );
    }

    const ObservationInterface* Client::Observation ( ) const {
        // TODO (?): Should this return a nullptr if the interface is not valid
        // (e.g., before a game is started)?
        return Control_Interface_->observation_imp_.get( );
    }

    QueryInterface* Client::Query ( ) {
        // TODO (?): Should this return a nullptr if the interface is not valid
        // (e.g., before a game is started)?
        return Control_Interface_->query_imp_.get( );
    }

    DebugInterface* Client::Debug ( ) {
        return Control_Interface_->debug_imp_.get( );
    }

    ControlInterface* Client::Control ( ) {
        return Control_Interface_;
    }

    const ControlInterface* Client::Control ( ) const {
        return Control_Interface_;
    }

    void Client::Reset ( ) {
        delete Control_Interface_;
        Control_Interface_ = new ControlInterface ( *this );
    }

    //! Called when a game is started after a load. Fast restarting will not
    //! call this.
    virtual void OnGameFullStart ( ) {}

    //! Called when a game is started or restarted.
    virtual void OnGameStart ( ) {}

    //! In non realtime games this function gets called after each step as
    //! indicated by step size. In realtime this function gets called as often
    //! as possible after request/responses are received from the game gathering
    //! observation state.
    virtual void OnStep ( ) {}

    //! Called when a game has ended.
    virtual void OnGameEnd ( ) {}

    //! Called whenever one of the player's units has been destroyed.
    //! \param unit The destroyed unit.
    virtual void OnUnitDestroyed ( const Unit* unit ) {}

    //! Called when a neutral unit is created. For example, mineral fields
    //! observed for the first time
    //! \param unit The observed unit.
    virtual void OnNeutralUnitCreated ( const Unit* unit ) {}

    //! Called when a Unit has been created by the player.
    //! \param unit The created unit.
    virtual void OnUnitCreated ( const Unit* unit ) {}

    //! Called when a unit becomes idle, this will only occur as an event so
    //! will only be called when the unit becomes idle and not a second time.
    //! Being idle is defined by having orders in the previous step and not
    //! currently having orders or if it did not exist in the previous step and
    //! now does, a unit being created, for instance, will call both
    //! OnUnitCreated and OnUnitIdle if it does not have a rally set.
    //!< \param unit The idle unit.
    virtual void OnUnitIdle ( const Unit* unit ) {}

    //! Called when an upgrade is finished, warp gate, ground weapons, baneling
    //! speed, etc.
    //!< \param upID The completed upgrade.
    virtual void OnUpgradeCompleted ( UpgradeID upID ) {}

    //! Called when the unit in the previous step had a build progress less
    //! than 1.0 but is greater than or equal to 1.0 in the current step.
    //! \param unit The constructed unit.
    virtual void OnBuildingConstructionComplete ( const Unit* unit ) {}

    //! Called when the unit in the current observation has lower health or
    //! shields than in the previous observation.
    //! \param unit The damaged unit.
    //! \param health The change in health (damage is positive)
    //! \param shields The change in shields (damage is positive)
    virtual void OnUnitDamaged (
            const Unit* unit, float health, float shields
    ) {}

    //! Called when a nydus is placed.
    virtual void OnNydusDetected ( ) {}

    //! Called when a nuclear launch is detected.
    virtual void OnNuclearLaunchDetected ( ) {}

    //! Called when an enemy unit enters vision from out of fog of war.
    //!< \param unit The unit entering vision.
    virtual void OnUnitEnterVision ( const Unit* unit ) {}

    //! Called for various errors the library can encounter. See ClientError
    //! enum for possible errors.
    virtual void OnError (
            const std::vector<ClientError>& /*client_errors*/,
            const std::vector<std::string>& /*protocol_errors*/ = { }
    ) {}

private:
    //! Pointer to the control interface.
    ControlInterface* Control_Interface_;
};

} // namespace sc2
