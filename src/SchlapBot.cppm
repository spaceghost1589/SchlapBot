module;
#include <iostream>
#include <string>
#include <vector>

#include "sc2api/sc2_agent.h"
#include "sc2api/sc2_client.h"
#include "sc2api/sc2_common.h"
#include "sc2api/sc2_search.h"
#include "sc2api/sc2_unit.h"
#include "sc2lib/typeids/sc2_5.0.14_typeenums.h"
export module SchlapBot;

import map_info;
import map_data;

using enum sc2::Unit::Alliance;

using sc2::Agent,
    sc2::ClientError,
    sc2::GameInfo,
    sc2::MapData,
    sc2::Point3D,
    sc2::search::CalculateExpansionLocations,
    sc2::Unit,
    sc2::UpgradeID,
    sc2::UpgradeIDToName,
    std::cerr,
    std::cout,
    std::string,
    std::vector;

namespace sc2 {
// The main bot class.
export struct SchlapBot : Agent
{
    SchlapBot() = default;

    GameInfo        game_info{};
    MapData         map_data{};
    Point3D         starting_location_;
    vector<Point3D> expansions{};

    void OnGameStart() override
    {
        game_info = Observation()->GetGameInfo();
        cout << "game started." << '\n';

        starting_location_ = Observation()->GetStartLocation();

        vector<Point3D> expansions = CalculateExpansionLocations(Observation(), Query());
    }

    void OnStep() override
    {
        // uint32_t game_loop = Observation()->GetGameLoop();

        // Units units = Observation()->GetUnits(Self);
    }

    void OnGameEnd() override
    {
        cout << "Game over!" << '\n';
    }

    void OnBuildingConstructionComplete(const Unit* building_) override
    {
        cout << UnitTypeToName(building_->unit_type) <<
            "(" << building_->tag << ") constructed" << '\n';
    }

    void OnUnitCreated(const Unit* unit_) override
    {
        cout << UnitTypeToName(unit_->unit_type) <<
            "(" << unit_->tag << ") was created" << '\n';
    }

    void OnUnitIdle(const Unit* unit_) override
    {
        cout << UnitTypeToName(unit_->unit_type) <<
             "(" << unit_->tag << ") is idle" << '\n';
    }

    void OnUnitDestroyed(const Unit* unit_) override
    {
        cout << UnitTypeToName(unit_->unit_type) <<
             "(" << unit_->tag << ") was destroyed" << '\n';
    }

    void OnUpgradeCompleted(const UpgradeID id_) override
    {
        cout << UpgradeIDToName(id_) << " completed" << '\n';
    }

    void OnError(const vector<ClientError>& client_errors,
            const vector<string>& protocol_errors) override
    {
        for (const auto err : client_errors) {
            cerr << "Encountered client error: " <<
                static_cast<int>(err) << '\n';
        }

        for (const auto& err : protocol_errors) {
            cerr << "Encountered protocol error: " << err << '\n';
        }
    }
};

} // namespace sc2
