#pragma once

#include <string>
#include <vector>

#include "s2clientprotocol/sc2api.pb.h"

#include "lib/game_settings.h"
import enum_db;
// import protocol_interface;


namespace sc2 {

class AgentControlInterface {
public:
    virtual ~AgentControlInterface() = default;

    virtual bool Restart() = 0;
};

}  // namespace sc2
