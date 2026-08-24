#pragma once

#include <cassert>

#include "s2clientprotocol/sc2api.pb.h"

#include "data.h"
#include "interfaces.h"
#include "proto_to_pods.h"

// TODO: Fill out the log functions
using std::string, std::to_string;

namespace sc2 {
AbilityData::AbilityData( ):
    ability_id ( 0 ),
    target ( Target::None ),
    available ( false ),
    is_structure ( false ),
    is_instant_placement ( false ) {}

void AbilityData::ReadFromProto(const SC2APIProtocol::AbilityData& ability_data) {
    // ability_id_
    if (ability_data.has_ability_id()) {
        ability_id = ability_data.ability_id();
    }

    // available_
    available = false;
    if (ability_data.has_available()) {
        available = ability_data.available();
    }

    // target_
    if (ability_data.has_target()) {
        switch (ability_data.target()) {
            case SC2APIProtocol::AbilityData_Target_Point: {
                target = Target::Point;
                break;
            }
            case SC2APIProtocol::AbilityData_Target_Unit: {
                target = Target::Unit;
                break;
            }
            case SC2APIProtocol::AbilityData_Target_PointOrUnit: {
                target = Target::PointOrUnit;
                break;
            }
            case SC2APIProtocol::AbilityData_Target_PointOrNone: {
                target = Target::PointOrNone;
                break;
            }
            case SC2APIProtocol::AbilityData_Target_None:
            default: {
                target = Target::None;
                break;
            }
        }
    }

    // is_building_
    is_structure = false;
    if (ability_data.has_is_building()) {
        is_structure = ability_data.is_building();
    }

    // footprint_radius_
    footprint_radius = 0.0f;
    if (ability_data.has_footprint_radius()) {
        footprint_radius = ability_data.footprint_radius();
    }

    is_instant_placement = false;
    if (ability_data.has_is_instant_placement()) {
        is_instant_placement = ability_data.is_instant_placement();
    }

    cast_range = 0.0f;
    if (ability_data.has_cast_range()) {
        cast_range = ability_data.cast_range();
    }
}

string AbilityData::Log() const {
    std::string str_out;

    str_out = ability_id.to_string() + ":\n";
    str_out += std::format("  Available: {}\n", available ? "true" : "false");
    str_out += "  Link Name: " + link_name + "\n";
    str_out += "  Link Index: " + std::to_string(link_index) + "\n";
    str_out += "  Button: " + button_name + "\n";
    str_out += "  Friendly Name: " + friendly_name + "\n";
    str_out += "  Hotkey: " + hotkey + "\n";
    str_out += "  General: " + std::to_string(remaps_to_ability_id) + "\n";
    str_out += "  Target: " + TargetToName(target) + "\n";
    str_out += std::format("  Minimap: {}\n", allow_minimap ? "true" : "false");
    str_out += std::format("  Autocast: {}\n", allow_autocast ? "true" : "false");
    str_out += std::format("  Building: {}\n", is_building ? "true" : "false");
    str_out += "  Radius: " + std::to_string(footprint_radius) + "\n";
    str_out += std::format("  Instant Placement: {}\n", is_instant_placement ? "true" : "false");
    str_out += "  Cast Range: " + std::to_string(cast_range) + "\n";

    return str_out;
}

static Attribute ConvertAttributeEnum(SC2APIProtocol::Attribute attribute) {
    switch (attribute) {
        case SC2APIProtocol::Attribute::Light:
            return Attribute::Light;
        case SC2APIProtocol::Attribute::Armored:
            return Attribute::Armored;
        case SC2APIProtocol::Attribute::Biological:
            return Attribute::Biological;
        case SC2APIProtocol::Attribute::Mechanical:
            return Attribute::Mechanical;
        case SC2APIProtocol::Attribute::Robotic:
            return Attribute::Robotic;
        case SC2APIProtocol::Attribute::Psionic:
            return Attribute::Psionic;
        case SC2APIProtocol::Attribute::Massive:
            return Attribute::Massive;
        case SC2APIProtocol::Attribute::Structure:
            return Attribute::Structure;
        case SC2APIProtocol::Attribute::Hover:
            return Attribute::Hover;
        case SC2APIProtocol::Attribute::Heroic:
            return Attribute::Heroic;
        case SC2APIProtocol::Attribute::Summoned:
            return Attribute::Summoned;
        default:
            return Attribute::Invalid;
    }
}

DamageBonus::DamageBonus() : attribute(), bonus(0) {
}

void DamageBonus::ReadFromProto(const SC2APIProtocol::DamageBonus& damage_bonus) {
    // attribute_
    attribute = ConvertAttributeEnum(damage_bonus.attribute());

    // bonus_
    bonus = damage_bonus.bonus();
}

static Weapon::TargetType ConvertTargetTypeEnum(SC2APIProtocol::Weapon::TargetType type) {
    switch (type) {
        case SC2APIProtocol::Weapon::Ground:
            return Weapon::TargetType::Ground;
        case SC2APIProtocol::Weapon::Air:
            return Weapon::TargetType::Air;
        case SC2APIProtocol::Weapon::Any:
            return Weapon::TargetType::Any;
        default:
            return Weapon::TargetType::Invalid;
    }
}

Weapon::Weapon() : type{4}, damage_{0}, attacks{0}, range{0}, speed{0} {
}

void Weapon::ReadFromProto(const SC2APIProtocol::Weapon& weapon) {
    // type_
    type = ConvertTargetTypeEnum(weapon.type());

    // damage_
    damage_ = weapon.damage();

    // damage_bonus_
    for (int i = 0; i < weapon.damage_bonus_size(); ++i) {
        DamageBonus bonus;
        bonus.ReadFromProto(weapon.damage_bonus(i));
        damage_bonus.push_back(bonus);
    }

    // attacks_
    attacks = weapon.attacks();

    // range_
    range = weapon.range();

    // speed_
    speed = weapon.speed();
}

UnitTypeData::UnitTypeData()
    : available{false},
      cargo_size{0},
      mineral_cost{0},
      vespene_cost{0},
      movement_speed{0},
      armor{0},
      supply_required{0},
      supply_provided{0},
      race{0},
      build_time{0},
      has_minerals{false},
      has_vespene{false},
      sight_range{0},
      require_attached{false} {
}

void UnitTypeData::ReadFromProto(const SC2APIProtocol::UnitTypeData& unit_data) {
    // unit_type_id_
    unit_type_id = unit_data.unit_id();

    // name_
    name = unit_data.name();

    // available_
    available = unit_data.available();

    // cargo_size_
    cargo_size = unit_data.cargo_size();

    // mineral_cost_
    mineral_cost = unit_data.mineral_cost();

    // vespene_cost_
    vespene_cost = unit_data.vespene_cost();

    // attribute_
    for (int i = 0; i < unit_data.attributes_size(); ++i) {
        attributes.push_back(ConvertAttributeEnum(unit_data.attributes(i)));
    }

    // movement_speed_
    movement_speed = unit_data.movement_speed();

    // armor_
    armor = unit_data.armor();

    // weapons_
    for (int i = 0; i < unit_data.weapons_size(); ++i) {
        Weapon weapon;
        weapon.ReadFromProto(unit_data.weapons(i));
        weapons.push_back(weapon);
    }

    supply_provided = unit_data.food_provided();

    supply_required = unit_data.food_required();

    ability_id = unit_data.ability_id();

    race = ConvertRaceFromProto(unit_data.race());

    build_time = unit_data.build_time();

    has_minerals = unit_data.has_minerals();

    has_vespene = unit_data.has_vespene();

    sight_range = unit_data.sight_range();

    for (int i = 0; i < unit_data.tech_alias_size(); ++i) {
        tech_alias.push_back(unit_data.tech_alias(i));
    }

    unit_alias = unit_data.unit_alias();

    tech_requirement = unit_data.tech_requirement();

    require_attached = unit_data.require_attached();
}

string UnitTypeData::Log() const {
    string str_out = unit_type_id.to_string() + ":\n";
    str_out += "  " + (name.length() > 0 ? name : "Null") + "\n";

    return str_out;
}

UpgradeData::UpgradeData() : upgrade_id{0}, mineral_cost{0}, vespene_cost{0}, research_time{0} {
}

void UpgradeData::ReadFromProto(const SC2APIProtocol::UpgradeData& upgrade_data) {
    upgrade_id = upgrade_data.upgrade_id();
    name = upgrade_data.name();
    mineral_cost = upgrade_data.mineral_cost();
    vespene_cost = upgrade_data.vespene_cost();
    ability_id = upgrade_data.ability_id();
    research_time = upgrade_data.research_time();
}

string UpgradeData::Log() {
    string str_out;
    // TODO Incomplete
    return str_out;
}

BuffData::BuffData() : buff_id{0} {
}

void BuffData::ReadFromProto(const SC2APIProtocol::BuffData& buff_data) {
    // upgrade_id_
    buff_id = buff_data.buff_id();

    // name_
    name = buff_data.name();
}

string BuffData::Log() {
    string str_out;
    // TODO Incomplete
    return str_out;
}

void EffectData::ReadFromProto(const SC2APIProtocol::EffectData& effect_data) {
    effect_id = effect_data.effect_id();
    name = effect_data.name();
    friendly_name = effect_data.friendly_name();
    radius = effect_data.radius();
}

string EffectData::Log() const {
    string str_out;
    // TODO Incomplete
    return str_out;
}

void Effect::ReadFromProto(const SC2APIProtocol::Effect& effect) {
    effect_id = effect.effect_id();
    for (int i = 0; i < effect.pos_size(); ++i) {
        const SC2APIProtocol::Point2D& pos = effect.pos(i);
        positions.push_back(Point2D(pos.x(), pos.y()));
    }
}

}  // namespace sc2
