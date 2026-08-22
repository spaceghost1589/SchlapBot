module;

export module Agent;

/* \file sc2_agent.h
   \brief The base class for user defined bots.

The Agent class provides a user with most access into SC2 state and unit manipulation.
A user will issue actions to units via the ActionInterface, examine game state with the
ObservationInterface, issue blocking commands (such as pathing queries) via the UnitQueryInterface
and override library provided events in ClientEvents.
*/

import client;
namespace sc2 {

class AgentControlImpl;
class ActionInterface;
class ActionFeatureLayerInterface;
class AgentControlInterface;

//! The base class for user defined bots.
class Agent : public Client {
public:

    Agent::Agent() : agent_control_impl_(new AgentControlImpl(this, Control())) {}

    Agent::~Agent() {
        delete agent_control_impl_;
    }

	//! Interface for issuing actions to units. Actions should be batched via the UnitCommand functions
	//! then eventually dispatched with SendActions. If you are stepping the simulation yourself the Step
	//! will automatically call SendActions. If your bot is running in real time you must call SendActions yourself.
	//!< \return The raw (basic) action interface.
    ActionInterface* Agent::Actions() const {
        return agent_control_impl_->actions_.get();
    }

	//! Interface for issuing actions in feature layers.
	//!< \return The feature layer action interface.
    ActionFeatureLayerInterface* Agent::ActionsFeatureLayer() const {
        return agent_control_impl_->actions_feature_layer_.get();
    }

	//! The AgentControlInterface is only currently used for restarting a game.
	//! For internal use.
	//!< \return The agent control interface.
    AgentControlInterface* Agent::AgentControl() const {
        return agent_control_impl_;
    }

private:
	AgentControlImpl* agent_control_impl_;
};

}  // namespace sc2

