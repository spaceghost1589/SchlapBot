// The MIT License (MIT)
//
// Copyright (c) 2021-2024 Alexander Kurbatov

#include "SchlapBot.h"

#include <sc2api/sc2_common.h>
#include <sc2api/sc2_unit.h>

#include <iostream>

void SchlapBot::OnGameStart()
{
    std::cout << "New game started!" << '\n';
}

void SchlapBot::OnBuildingConstructionComplete(const sc2::Unit* building_)
{
    std::cout << sc2::UnitTypeToName(building_->unit_type) <<
        "(" << building_->tag << ") constructed" << '\n';
}

void SchlapBot::OnStep()
{
    std::cout << "OnStep" << '\n';
}

void SchlapBot::OnUnitCreated(const sc2::Unit* unit_)
{
    std::cout << sc2::UnitTypeToName(unit_->unit_type) <<
        "(" << unit_->tag << ") was created" << '\n';
}

void SchlapBot::OnUnitIdle(const sc2::Unit* unit_)
{
    std::cout << sc2::UnitTypeToName(unit_->unit_type) <<
         "(" << unit_->tag << ") is idle" << '\n';
}

void SchlapBot::OnUnitDestroyed(const sc2::Unit* unit_)
{
    std::cout << sc2::UnitTypeToName(unit_->unit_type) <<
         "(" << unit_->tag << ") was destroyed" << '\n';
}

void SchlapBot::OnUpgradeCompleted(sc2::UpgradeID id_)
{
    std::cout << sc2::UpgradeIDToName(id_) << " completed" << '\n';
}

void SchlapBot::OnError(const std::vector<sc2::ClientError>& client_errors,
        const std::vector<std::string>& protocol_errors)
{
    for (const auto i : client_errors) {
        std::cerr << "Encountered client error: " <<
            static_cast<int>(i) << '\n';
    }

    for (const auto& i : protocol_errors)
        std::cerr << "Encountered protocol error: " << i << '\n';
}

void SchlapBot::OnGameEnd()
{
    std::cout << "Game over!" << "/n";
}
