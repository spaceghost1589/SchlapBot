/*! \file sc2_replay_observer.h
    \brief A client running a replay.
*/
#pragma once

#include <string>

#include "sc2_client.h"

namespace sc2 {

class ReplayControlImpl;
class ReplayControlInterface;
class ObserverActionImpl;
class ObserverActionInterface;
class ControlInterface;
struct ReplayInfo;

//! A client for running a replay.
class ReplayObserver : public Client {
public:
    ReplayObserver();
    ~ReplayObserver() override;

    //! Obtains the replay control interface.
    //!< \return The replay control interface.
    ReplayControlInterface* ReplayControl() const;

    //! Obtains the observer action interface.
    //!< \return The observer action interface.
    ObserverActionInterface* ObserverAction() const;

    //! Determines if the replay should be filtered out.
    //! \param replay_info Replay information used to decide if the replay should be filtered.
    //!< \return If 'true', the replay will be rejected and not analyzed.
    virtual bool IgnoreReplay(const ReplayInfo& replay_info, uint32_t player_id);

    virtual void Reset();

private:
    ReplayControlImpl* replay_control_impl_;
    ObserverActionImpl* observer_action_impl_;
};

}  // namespace sc2
