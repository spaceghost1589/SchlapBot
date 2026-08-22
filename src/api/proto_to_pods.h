#pragma once

#include <s2clientprotocol/query.pb.h>
#include <s2clientprotocol/raw.pb.h>
#include <s2clientprotocol/sc2api.pb.h>
#include <s2clientprotocol/spatial.pb.h>

#include "api/unit.h"
#include "lib/action.h"

import map_info;
// import protocol_interface;
import score;

using std::uint32_t;



namespace sc2 {

using ResponseObservationPtr = MessageResponsePtr<SC2APIProtocol::ResponseObservation>;
using ObservationPtr = MessageResponsePtr<SC2APIProtocol::Observation>;
using ObservationRawPtr = MessageResponsePtr<SC2APIProtocol::ObservationRaw>;
using ObservationRenderPtr = MessageResponsePtr<SC2APIProtocol::ObservationRender>;
using ResponsePingPtr = MessageResponsePtr<SC2APIProtocol::ResponsePing>;
using ResponseGameInfoPtr = MessageResponsePtr<SC2APIProtocol::ResponseGameInfo>;
using ResponseQueryPtr = MessageResponsePtr<SC2APIProtocol::ResponseQuery>;

bool Convert(const ObservationPtr& observation_ptr, Score& score);
bool Convert(const ObservationRawPtr& observation_raw, UnitPool& unit_pool, uint32_t game_loop,
             uint32_t prev_game_loop);
bool Convert(const ObservationPtr& observation_ptr, RenderedFrame& render);
bool Convert(const ResponseGameInfoPtr& response_game_info_ptr, GameInfo& game_info);
bool Convert(const SC2APIProtocol::DisplayType& type_proto, Unit::DisplayType& type);
bool Convert(const SC2APIProtocol::Alliance& alliance_proto, Unit::Alliance& alliance);
bool Convert(const SC2APIProtocol::CloakState& cloak_proto, Unit::CloakState& cloak);

void ConvertRawActions(const ResponseObservationPtr& response_observation_ptr, RawActions& actions);
void ConvertFeatureLayerActions(const ResponseObservationPtr& response_observation_ptr, SpatialActions& actions);
void ConvertRenderedActions(const ResponseObservationPtr& response_observation_ptr, SpatialActions& actions);

Race ConvertRaceFromProto(SC2APIProtocol::Race race);
GameResult ConvertGameResultFromProto(SC2APIProtocol::Result result);
PlayerType ConvertPlayerTypeFromProto(SC2APIProtocol::PlayerType type);
Difficulty ConvertDifficultyFromProto(SC2APIProtocol::Difficulty difficulty);
AIBuild ConvertAIBuildFromProto(SC2APIProtocol::AIBuild ai_build);

}  // namespace sc2
