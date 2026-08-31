module;
#include <flat_map>
#include <stdint.h>
#include <string>
#include <vector>

#include <s2clientprotocol/data.pb.h>
#include <s2clientprotocol/raw.pb.h>
export module data;
import protocol_interface;
import common;
import game_types;
import proto_to_pods;
import type_enums;


// TODO: Fill out the log functions

export namespace sc2 {
using namespace std;

//! Indicates if an ability is available, and if that ability requires a point.
struct AvailableAbility
{
    AvailableAbility ( ) = default;

    //! Ability that is available.
    AbilityID ability_id { ABILITY_ID::INVALID };
    //! Indicates if the ability requires a point to invoke.
    bool      requires_point { false };
};

//! Type of target this ability applies to.
enum class Target : uint8_t {
    //! There is no target, applies to self.
    None        = 1,
    //! Target is a point.
    Point       = 2,
    //! Target is another unit.
    Unit        = 3,
    //! Target can be a point or another unit.
    PointOrUnit = 4,
    //! Target can be a point or no target.
    PointOrNone = 5
};

string TargetToName ( const Target target ) {
    switch ( target ) {
        case Target::None        : return "None";
        case Target::Point       : return "Point";
        case Target::Unit        : return "Unit";
        case Target::PointOrUnit : return "PointOrUnit";
        case Target::PointOrNone : return "PointOrNone";
    }
    return "None";
}

//! Data about an ability.
struct AbilityData
{


    //! Range unit can cast ability without needing to approach target.
    float     cast_range;
    //! This ability id may be represented by the given more generic id.
    uint16_t  remaps_to_ability_id;
    //! Stable ID. For a given ability, this value will be immutable throughout
    //! different patches.
    AbilityID ability_id;
    //! Determines if a point, unit, both or none is required as a target.
    Target    target;
    //! Autocast can be set.
    bool      allow_autocast;
    //! If the ability is placing a building, give the radius of the footprint.
    uint8_t   footprint_diameter;
    //! Placement next to an existing structure, e.g., an add-on like a Tech
    //! Lab.
    bool      is_instant_placement;


    /*

    //! Catalog (game data xml) name of the ability.
    string link_name;
    //! Name of the button for the command card.
    string button_name;
    //! In case the button name is not descriptive.
    string friendly_name;
    //! UI hotkey.
    string hotkey;
    //! Other abilities remapped to this generic ability.
    vector<uint32_t> remaps_from_ability_id;

    //! Catalog (game data xml) index of the ability.
    uint32_t link_index;

    //! If the ability is placing a building, give the radius of the footprint.
    float footprint_radius;

    //! If true, the ability is available to the current mods/map.
    bool available;
    //! Can be cast in the minimap. (Not implemented)
    bool allow_minimap;
    //! Requires placement to construct a building.
    bool is_structure;

    */

    //! AbilityData constructor.
    AbilityData ( ) = default;

    AbilityData (
        AbilityID ability_id,
        uint16_t  remaps_to_ability_id,
        Target    target,
        bool      allow_autocast,
        uint8_t   footprint_diameter,
        bool      is_instant_placement,
        float     cast_range
    ) // ReSharper disable once CppMemberInitializersOrder
          : ability_id ( ability_id ),
            remaps_to_ability_id ( remaps_to_ability_id ),
            target ( target ),
            allow_autocast ( allow_autocast ),
            footprint_diameter ( footprint_diameter ),
            is_instant_placement ( is_instant_placement ),
            cast_range ( cast_range ) {}

    //! Serialize this ability entry from the .proto file (used internally).
    //! @param ability_data The proto entry for this ability.
    void ReadFromProto ( const SC2APIProtocol::AbilityData& ability_data ) {
        // ability_id_
        if ( ability_data.has_ability_id( ) ) {
            ability_id = ability_data.ability_id( );
        }

        // // available_
        // available = false;
        // if ( ability_data.has_available( ) ) {
        //     available = ability_data.available( );
        // }

        // target_
        if ( ability_data.has_target( ) ) {
            switch ( ability_data.target( ) ) {
                case SC2APIProtocol::AbilityData_Target_Point : {
                    target = Target::Point;
                    break;
                }
                case SC2APIProtocol::AbilityData_Target_Unit : {
                    target = Target::Unit;
                    break;
                }
                case SC2APIProtocol::AbilityData_Target_PointOrUnit : {
                    target = Target::PointOrUnit;
                    break;
                }
                case SC2APIProtocol::AbilityData_Target_PointOrNone : {
                    target = Target::PointOrNone;
                    break;
                }
                case SC2APIProtocol::AbilityData_Target_None :
                default                                      : {
                    target = Target::None;
                    break;
                }
            }
        }
    }

    //! Serialize this ability to a string.
    string Log ( ) const {
        std::string str_out = ability_id.to_string( ) + ":\n";
        str_out            += "  Target: " + TargetToName ( target );

        return str_out;
    }
};

/*
void LogStream ( ofstream& DB_file_out, const AbilityData& ability_data ) {
    DB_file_out << boolalpha;

    DB_file_out << "       ability_id: " << ability_data.ability_id << '\n';
    DB_file_out << "        link_name: " << ability_data.link_name << '\n';
    DB_file_out << "       link_index: " << ability_data.link_index << '\n';
    DB_file_out << "      button_name: " << ability_data.button_name << '\n';
    DB_file_out << "    friendly_name: " << ability_data.friendly_name << '\n';
    DB_file_out << "           hotkey: " << ability_data.hotkey << '\n';
    DB_file_out << "     remaps_to_id: " << ability_data.remaps_to_ability_id
                << '\n';
    DB_file_out << "        available: " << ability_data.available << '\n';
    DB_file_out << "           target: " << TargetToName ( ability_data.target )
                << '\n';
    DB_file_out << "    allow_minimap: " << ability_data.allow_minimap << '\n';
    DB_file_out << "   allow_autocast: " << ability_data.allow_autocast << '\n';
    DB_file_out << "      is_structure: " << ability_data.is_structure << '\n';
    DB_file_out << " footprint_radius: " << ability_data.footprint_radius
                << '\n';
    DB_file_out << "instant_placement: " << ability_data.is_instant_placement
                << '\n';
    DB_file_out << "       cast_range: " << ability_data.cast_range << "\n\n";
} */

// void LogFullStream (
//     ofstream& DB_file_out, const AbilityData& ability_data
// ) {
//     DB_file_out << boolalpha;
//
//     DB_file_out << "       ability_id: " << ability_data.ability_id << '\n';
//     DB_file_out << "        link_name: " << ability_data.link_name << '\n';
//     DB_file_out << "       link_index: " << ability_data.link_index << '\n';
//     DB_file_out << "      button_name: " << ability_data.button_name << '\n';
//     DB_file_out << "    friendly_name: " << ability_data.friendly_name <<
//     '\n'; DB_file_out << "           hotkey: " << ability_data.hotkey <<
//     '\n'; DB_file_out << "     remaps_to_id: " <<
//     ability_data.remaps_to_ability_id
//                 << '\n';
//     DB_file_out << "        available: " << ability_data.available << '\n';
//     DB_file_out << "           target: " << TargetToName (
//     ability_data.target )
//                 << '\n';
//     DB_file_out << "    allow_minimap: " << ability_data.allow_minimap <<
//     '\n'; DB_file_out << "   allow_autocast: " << ability_data.allow_autocast
//     << '\n'; DB_file_out << "      is_structure: " << ability_data.is_structure
//     << '\n'; DB_file_out << " footprint_radius: " <<
//     ability_data.footprint_radius
//                 << '\n';
//     DB_file_out << "instant_placement: " << ability_data.is_instant_placement
//                 << '\n';
//     DB_file_out << "       cast_range: " << ability_data.cast_range <<
//     "\n\n";
// }

using Abilities = vector<AbilityData>;

//! All available abilities for a unit.
struct AvailableAbilities
{
    //! The available abilities.
    vector<AvailableAbility> abilities;
    //! The unit.
    Tag                      unit_tag;
    //! The unit type.
    UnitTypeID               unit_type_id;

    //! Returns true if this object refers to a valid unit and unit type.
    //! @return If this object is valid.
    bool IsValid ( ) const {
        return unit_tag && unit_type_id;
    }
};


/*! @brief Attribute of unit.
 * @note Altered to use bitmask */
enum class Attribute : uint8_t {
    Invalid    = 0,
    Light      = 1 << 0, // 1
    Armored    = 1 << 1, // 2
    Biological = 1 << 2, // 4
    Mechanical = 1 << 3, // 8
    Psionic    = 1 << 4, // 16
    Massive    = 1 << 5, // 32
    Structure  = 1 << 6, // 64
    Flying     = 1 << 7  // 128 // formerly Hover
};

uint8_t ConvertAttributeEnum (
    const SC2APIProtocol::Attribute& SC2API_attr, uint8_t bit_mask = 0
) { // clang-format off
    switch ( SC2API_attr ) {
        case SC2APIProtocol::Attribute::Light :
            bit_mask |= static_cast<uint8_t> ( Attribute::Light );
            break;
        case SC2APIProtocol::Attribute::Armored :
            bit_mask |= static_cast<uint8_t> ( Attribute::Armored );
            break;
        case SC2APIProtocol::Attribute::Biological :
            bit_mask |= static_cast<uint8_t> ( Attribute::Biological );
            break;
        case SC2APIProtocol::Attribute::Mechanical :
            bit_mask |= static_cast<uint8_t> ( Attribute::Mechanical );
            break;
        case SC2APIProtocol::Attribute::Psionic :
            bit_mask |= static_cast<uint8_t> ( Attribute::Psionic );
            break;
        case SC2APIProtocol::Attribute::Massive :
            bit_mask |= static_cast<uint8_t> ( Attribute::Massive );
            break;
        case SC2APIProtocol::Attribute::Structure :
            bit_mask |= static_cast<uint8_t> ( Attribute::Structure );
            break;
        case SC2APIProtocol::Attribute::Hover :
            bit_mask |= static_cast<uint8_t> ( Attribute::Flying );
            break;
        default :
            break;
    } // clang-format on
    return bit_mask;
}

//! Damage bonus of unit.
struct DamageBonus
{
    float   bonus { 0.0F };
    uint8_t attribute { };

    DamageBonus ( ) = default;

    void ReadFromProto ( const SC2APIProtocol::DamageBonus& damage_bonus ) {
        // attribute_
        attribute = ConvertAttributeEnum ( damage_bonus.attribute( ) );

        // bonus_
        bonus = damage_bonus.bonus( );
    }
};

//! Unit weapon.
struct Weapon
{
    enum class TargetType : uint8_t {
        Invalid = 0,
        Ground  = 1,
        Air     = 2,
        Any     = 3,
    };

    bool Ground { false };
    bool Air { false };

    TargetType          type { 0 };
    float               damage_ { 0 };
    //! Extra damage when attacking a unit of a certain attribute.
    vector<DamageBonus> damage_bonus;
    //! Number of hits per attack. (eg. Colossus has 2 beams)
    uint32_t            attacks { 1 };
    float               range { 0 };
    float               speed { 0 }; // Time between attacks

    Weapon ( ) = default;

    static TargetType ConvertTargetTypeEnum (
        SC2APIProtocol::Weapon::TargetType type
    ) {
        switch ( type ) {
            case SC2APIProtocol::Weapon::Ground : return TargetType::Ground;
            case SC2APIProtocol::Weapon::Air    : return TargetType::Air;
            case SC2APIProtocol::Weapon::Any    : return TargetType::Any;
            default                             : return TargetType::Invalid;
        }
    }

    void ReadFromProto ( const SC2APIProtocol::Weapon& weapon ) {
        // type_
        type = ConvertTargetTypeEnum ( weapon.type( ) );

        // damage_
        damage_ = weapon.damage( );

        // damage_bonus_
        for ( int i = 0; i < weapon.damage_bonus_size( ); ++i ) {
            DamageBonus bonus;
            bonus.ReadFromProto ( weapon.damage_bonus ( i ) );
            damage_bonus.push_back ( bonus );
        }

        // attacks_
        attacks = weapon.attacks( );

        // range_
        range = weapon.range( );

        // speed_
        speed = weapon.speed( );
    }
};

//! Data about a unit type. This data is derived from the catalog (xml) data of
//! the game and upgrades.
struct UnitTypeData
{
    //! Unit type name, corresponds to the game's catalog.
    string   name;
    //! Number of cargo slots they occupy in a transport.
    uint32_t cargo_size { 0 };
    //! Cost in minerals to build this unit type.
    uint32_t mineral_cost { 0 };
    //! Cost in vespene to build this unit type.
    uint32_t vespene_cost { 0 };

    //! Stable ID. This ID will not change between patches.
    UnitTypeID unit_type_id;


    //! Unit attributes, may change based on upgrades. (BitPacked)
    uint8_t attributes;

    //! Movement speed of unit type.
    float          movement_speed { 0 };
    //! Armor of unit type.
    float          armor { 0 };
    //! Weapons on this unit type.
    vector<Weapon> weapons;
    //! How much supply the unit requires.
    float          supply_required { 0 };
    //! How much supply the unit provides.
    float          supply_provided { 0 };
    //! Which ability id creates the unit.
    AbilityID      ability_id;
    //! The race the unit belongs to.
    Race           race { 0 };
    //! How long the unit takes to build.
    float          build_time { 0 };
    //! Whether the unit can have minerals (mineral patches).
    bool           has_minerals { false };
    //! Whether the unit can have vespene (vespene geysers).
    bool           has_vespene { false };
    //! Range the unit reveals vision.
    float          sight_range { 0 };

    //! Units this is equivalent to in terms of satisfying tech requirements.
    vector<UnitTypeID> tech_alias;
    //! Units that are morphed variants of the same unit.
    UnitTypeID         unit_alias;
    //! Structure required to build this unit. (Or any with the same tech_alias)
    UnitTypeID         tech_requirement;
    //! Whether tech_requirement is an add-on.
    bool               require_attached { false };
    //! If true, the unit is available to the current mods/map.
    bool               available { false };

    //! Constructor.
    UnitTypeData ( ) = default;

    //! Serialize this ability entry from the .proto file (used internally).
    //! @param unit_data The proto entry for this ability.
    void ReadFromProto ( const SC2APIProtocol::UnitTypeData& unit_data ) {
        // unit_type_id_
        unit_type_id = unit_data.unit_id( );

        // name_
        name = unit_data.name( );

        // available_
        available = unit_data.available( );

        // cargo_size_
        cargo_size = unit_data.cargo_size( );

        // mineral_cost_
        mineral_cost = unit_data.mineral_cost( );

        // vespene_cost_
        vespene_cost = unit_data.vespene_cost( );

        // attribute_
        for ( int i = 0; i < unit_data.attributes_size( ); ++i ) {
            attributes = ( ConvertAttributeEnum (
                unit_data.attributes ( i ),
                attributes
            ) );
        }

        // movement_speed_
        movement_speed = unit_data.movement_speed( );

        // armor_
        armor = unit_data.armor( );

        // weapons_
        for ( int i = 0; i < unit_data.weapons_size( ); ++i ) {
            Weapon weapon;
            weapon.ReadFromProto ( unit_data.weapons ( i ) );
            weapons.push_back ( weapon );
        }

        supply_provided = unit_data.food_provided( );

        supply_required = unit_data.food_required( );

        ability_id = unit_data.ability_id( );

        race = ConvertRaceFromProto ( unit_data.race( ) );

        build_time = unit_data.build_time( );

        has_minerals = unit_data.has_minerals( );

        has_vespene = unit_data.has_vespene( );

        sight_range = unit_data.sight_range( );

        for ( int i = 0; i < unit_data.tech_alias_size( ); ++i ) {
            tech_alias.push_back ( unit_data.tech_alias ( i ) );
        }

        unit_alias = unit_data.unit_alias( );

        tech_requirement = unit_data.tech_requirement( );

        require_attached = unit_data.require_attached( );
    }

    //! Serialize this unit type to a string.
    string Log ( ) const {
        string str_out = unit_type_id.to_string( ) + ":\n";
        str_out       += "  " + ( name.length( ) > 0 ? name : "Null" ) + "\n";

        return str_out;
    }
};

using UnitTypes = vector<UnitTypeData>;

//! Upgrade data.
struct UpgradeData
{
    //! Upgrade name, corresponds to the game's catalog.
    string    name;
    //! Stable ID. This ID will not change between patches.
    uint32_t  upgrade_id { 0 };
    //! Time in GameLoops to research this upgrade.
    float     research_time { 0 };
    //! Ability that researches this upgrade.
    AbilityID ability_id;
    //! Mineral cost of researching the upgrade.
    uint8_t   mineral_cost { 0 };
    //! Vespene cost of researching the upgrade.
    uint8_t   vespene_cost { 0 };


    UpgradeData ( ) = default;

    void ReadFromProto ( const SC2APIProtocol::UpgradeData& upgrade_data ) {
        upgrade_id    = upgrade_data.upgrade_id( );
        name          = upgrade_data.name( );
        mineral_cost  = upgrade_data.mineral_cost( );
        vespene_cost  = upgrade_data.vespene_cost( );
        ability_id    = upgrade_data.ability_id( );
        research_time = upgrade_data.research_time( );
    }

    string Log ( ) {
        string str_out;
        // TODO Incomplete
        return str_out;
    }
};

using Upgrades = vector<UpgradeData>;

//! Buff data.
struct BuffData
{
    //! Stable ID. This ID will not change between patches.
    uint32_t buff_id { 0 };
    //! Buff name, corresponds to the game's catalog.
    string   name;

    BuffData ( ) = default;

    void ReadFromProto ( const SC2APIProtocol::BuffData& buff_data ) {
        // upgrade_id_
        buff_id = buff_data.buff_id( );

        // name_
        name = buff_data.name( );
    }

    string Log ( ) {
        string str_out;
        // TODO Incomplete
        return str_out;
    }
};

typedef vector<BuffData> Buffs;

//! Effect data.
struct EffectData
{
    //! Stable ID. This ID will not change between patches.
    uint32_t effect_id;
    //! Effect name, corresponds to the game's catalog.
    string   name;
    //! A more recognizable name of the effect.
    string   friendly_name;
    //! Size of the circle the effect impacts.
    float    radius;

    void ReadFromProto ( const SC2APIProtocol::EffectData& effect_data ) {
        effect_id     = effect_data.effect_id( );
        name          = effect_data.name( );
        friendly_name = effect_data.friendly_name( );
        radius        = effect_data.radius( );
    }

    string Log ( ) const {
        string str_out;
        // TODO Incomplete
        return str_out;
    }
};

using Effects = vector<EffectData>;

//! Power source information for Protoss.
struct PowerSource
{
    PowerSource ( const Point2D in_position, float in_radius, Tag in_tag )
          : position ( in_position ),
            radius ( in_radius ),
            tag ( in_tag ) {}

    //! Power source position.
    Point2D position;
    //! Power source radius.
    float   radius;
    //! Unit tag of the power source.
    Tag     tag;
};

//! The visuals of a persistent ability on the map. (eg. Psistorm)
struct Effect
{
    //! Type of the effect
    uint32_t        effect_id;
    //! All the positions that this effect is impacting on the map.
    //! eg. The Lurker's attack impacts multiple positions in a line.
    vector<Point2D> positions;

    void ReadFromProto ( const SC2APIProtocol::Effect& effect ) {
        effect_id = effect.effect_id( );
        for ( int i = 0; i < effect.pos_size( ); ++i ) {
            const SC2APIProtocol::Point2D& pos = effect.pos ( i );
            positions.push_back ( Point2D ( pos.x( ), pos.y( ) ) );
        }
    }
};

} // namespace sc2

namespace {

using sc2::Target::None;
using sc2::Target::Unit;
using sc2::Target::Point;
using sc2::Target::PointOrNone;
using sc2::Target::PointOrUnit;

} // namespace

namespace sc2 {

const flat_map<AbilityID, AbilityData> AbilityDataDB {
    // clang-format off
    {0,  // INVALID
    AbilityData(0, 0, None, false, 0, false, 0) },
    {1,  // SMART
    AbilityData(1, 0, PointOrUnit, false, 0, false, 0) },
    {2,  // TAUNT
    AbilityData(2, 0, PointOrUnit, false, 0, false, 10) },
    {20,  // MOVE_TURN
    AbilityData(20, 0, PointOrUnit, false, 0, false, 0) },
    {24,  // ATTACK_ATTACKTOWARDS
    AbilityData(24, 0, Point, false, 0, false, 0) },
    {25,  // ATTACK_ATTACKBARRAGE
    AbilityData(25, 0, Point, false, 0, false, 0) },
    {40,  // EFFECT_INFESTEDTERRANS
    AbilityData(40, 0, None, false, 0, false, 0) },
    {42,  // EFFECT_EXPLODE
    AbilityData(42, 0, None, false, 0, false, 0) },
    {44,  // RESEARCH_INTERCEPTORGRAVITONCATAPULT
    AbilityData(44, 0, None, false, 0, false, 0) },
    {45,  // RESEARCH_INTERCEPTORLAUNCHSPEEDUPGRADE
    AbilityData(45, 0, None, false, 0, false, 0) },
    {46,  // RESEARCH_PHOENIXANIONPULSECRYSTALS
    AbilityData(46, 0, None, false, 0, false, 0) },
    {47,  // RESEARCH_TEMPESTRANGEUPGRADE
    AbilityData(47, 0, None, false, 0, false, 0) },
    {48,  // RESEARCH_VOIDRAYSPEEDUPGRADE
    AbilityData(48, 0, None, false, 0, false, 0) },
    {49,  // RESEARCH_TEMPESTRESEARCHGROUNDATTACKUPGRADE
    AbilityData(49, 0, None, false, 0, false, 0) },
    {74,  // EFFECT_FUNGALGROWTH
    AbilityData(74, 0, Point, false, 0, false, 10) },
    {76,  // EFFECT_GUARDIANSHIELD
    AbilityData(76, 0, None, false, 0, false, 0) },
    {110,  // TRAIN_MOTHERSHIP
    AbilityData(110, 0, None, false, 0, false, 0) },
    {140,  // EFFECT_FEEDBACK
    AbilityData(140, 0, Unit, false, 0, false, 10) },
    {146,  // HALLUCINATION_ARCHON
    AbilityData(146, 0, None, false, 0, false, 0) },
    {148,  // HALLUCINATION_COLOSSUS
    AbilityData(148, 0, None, false, 0, false, 0) },
    {150,  // HALLUCINATION_HIGHTEMPLAR
    AbilityData(150, 0, None, false, 0, false, 0) },
    {152,  // HALLUCINATION_IMMORTAL
    AbilityData(152, 0, None, false, 0, false, 0) },
    {154,  // HALLUCINATION_PHOENIX
    AbilityData(154, 0, None, false, 0, false, 0) },
    {156,  // HALLUCINATION_PROBE
    AbilityData(156, 0, None, false, 0, false, 0) },
    {158,  // HALLUCINATION_STALKER
    AbilityData(158, 0, None, false, 0, false, 0) },
    {160,  // HALLUCINATION_VOIDRAY
    AbilityData(160, 0, None, false, 0, false, 0) },
    {162,  // HALLUCINATION_WARPPRISM
    AbilityData(162, 0, None, false, 0, false, 0) },
    {164,  // HALLUCINATION_ZEALOT
    AbilityData(164, 0, None, false, 0, false, 0) },
    {171,  // EFFECT_CALLDOWNMULE
    AbilityData(171, 0, PointOrUnit, false, 0, false, 500) },
    {173,  // EFFECT_GRAVITONBEAM
    AbilityData(173, 0, Unit, false, 0, false, 4) },
    {181,  // EFFECT_SPAWNCHANGELING
    AbilityData(181, 0, None, false, 0, false, 0) },
    {216,  // RESEARCH_GLIALREGENERATION
    AbilityData(216, 0, None, false, 0, false, 0) },
    {217,  // RESEARCH_TUNNELINGCLAWS
    AbilityData(217, 0, None, false, 0, false, 0) },
    {218,  // RESEARCH_ROACHSUPPLY
    AbilityData(218, 0, None, false, 0, false, 0) },
    {245,  // SAPSTRUCTURE
    AbilityData(245, 0, Unit, true, 0, false, 0.25) },
    {249,  // EFFECT_NEURALPARASITE
    AbilityData(249, 0, Unit, false, 0, false, 8) },
    {251,  // EFFECT_INJECTLARVA
    AbilityData(251, 0, Unit, false, 0, false, 0.100098) },
    {255,  // EFFECT_SUPPLYDROP
    AbilityData(255, 0, Unit, false, 0, false, 500) },
    {263,  // RESEARCH_ANABOLICSYNTHESIS
    AbilityData(263, 0, None, false, 0, false, 0) },
    {265,  // RESEARCH_CHITINOUSPLATING
    AbilityData(265, 0, None, false, 0, false, 0) },
    {301,  // ATTACK_ATTACKWARPPRISM
    AbilityData(301, 0, PointOrUnit, false, 0, false, 0) },
    {318,  // BUILD_COMMANDCENTER
    AbilityData(318, 0, Point, false, 5, false, 0) },
    {319,  // BUILD_SUPPLYDEPOT
    AbilityData(319, 0, Point, false, 2, false, 0) },
    {320,  // BUILD_REFINERY
    AbilityData(320, 0, Unit, false, 3, false, 0) },
    {321,  // BUILD_BARRACKS
    AbilityData(321, 0, Point, false, 3, false, 0) },
    {322,  // BUILD_ENGINEERINGBAY
    AbilityData(322, 0, Point, false, 3, false, 0) },
    {323,  // BUILD_MISSILETURRET
    AbilityData(323, 0, Point, false, 2, false, 0) },
    {324,  // BUILD_BUNKER
    AbilityData(324, 0, Point, false, 3, false, 0) },
    {326,  // BUILD_SENSORTOWER
    AbilityData(326, 0, Point, false, 1, false, 0) },
    {327,  // BUILD_GHOSTACADEMY
    AbilityData(327, 0, Point, false, 3, false, 0) },
    {328,  // BUILD_FACTORY
    AbilityData(328, 0, Point, false, 3, false, 0) },
    {329,  // BUILD_STARPORT
    AbilityData(329, 0, Point, false, 3, false, 0) },
    {331,  // BUILD_ARMORY
    AbilityData(331, 0, Point, false, 3, false, 0) },
    {333,  // BUILD_FUSIONCORE
    AbilityData(333, 0, Point, false, 3, false, 0) },
    {386,  // EFFECT_HEAL
    AbilityData(386, 0, Unit, true, 0, false, 4) },
    {388,  // MORPH_SIEGEMODE
    AbilityData(388, 0, None, false, 0, false, 0) },
    {390,  // MORPH_UNSIEGE
    AbilityData(390, 0, None, false, 0, false, 0) },
    {399,  // EFFECT_SCAN
    AbilityData(399, 0, Point, false, 0, false, 500) },
    {401,  // EFFECT_YAMATOGUN
    AbilityData(401, 0, Unit, false, 0, false, 10) },
    {403,  // MORPH_VIKINGASSAULTMODE
    AbilityData(403, 0, None, false, 0, false, 0) },
    {405,  // MORPH_VIKINGFIGHTERMODE
    AbilityData(405, 0, None, false, 0, false, 0) },
    {524,  // TRAIN_SCV
    AbilityData(524, 0, None, false, 0, false, 0) },
    {556,  // MORPH_SUPPLYDEPOT_LOWER
    AbilityData(556, 0, None, false, 0, false, 0) },
    {558,  // MORPH_SUPPLYDEPOT_RAISE
    AbilityData(558, 0, None, false, 0, false, 0) },
    {560,  // TRAIN_MARINE
    AbilityData(560, 0, None, false, 0, false, 0) },
    {561,  // TRAIN_REAPER
    AbilityData(561, 0, None, false, 0, false, 0) },
    {562,  // TRAIN_GHOST
    AbilityData(562, 0, None, false, 0, false, 0) },
    {563,  // TRAIN_MARAUDER
    AbilityData(563, 0, None, false, 0, false, 0) },
    {591,  // TRAIN_SIEGETANK
    AbilityData(591, 0, None, false, 0, false, 0) },
    {594,  // TRAIN_THOR
    AbilityData(594, 0, None, false, 0, false, 0) },
    {595,  // TRAIN_HELLION
    AbilityData(595, 0, None, false, 0, false, 0) },
    {596,  // TRAIN_HELLBAT
    AbilityData(596, 0, None, false, 0, false, 0) },
    {597,  // TRAIN_CYCLONE
    AbilityData(597, 0, None, false, 0, false, 0) },
    {614,  // TRAIN_WIDOWMINE
    AbilityData(614, 0, None, false, 0, false, 0) },
    {620,  // TRAIN_MEDIVAC
    AbilityData(620, 0, None, false, 0, false, 0) },
    {621,  // TRAIN_BANSHEE
    AbilityData(621, 0, None, false, 0, false, 0) },
    {622,  // TRAIN_RAVEN
    AbilityData(622, 0, None, false, 0, false, 0) },
    {623,  // TRAIN_BATTLECRUISER
    AbilityData(623, 0, None, false, 0, false, 0) },
    {624,  // TRAIN_VIKINGFIGHTER
    AbilityData(624, 0, None, false, 0, false, 0) },
    {626,  // TRAIN_LIBERATOR
    AbilityData(626, 0, None, false, 0, false, 0) },
    {650,  // RESEARCH_HISECAUTOTRACKING
    AbilityData(650, 0, None, false, 0, false, 0) },
    {651,  // RESEARCH_TERRANSTRUCTUREARMORUPGRADE
    AbilityData(651, 0, None, false, 0, false, 0) },
    {655,  // RESEARCH_NEOSTEELFRAME
    AbilityData(655, 0, None, false, 0, false, 0) },
    {710,  // BUILD_NUKE
    AbilityData(710, 0, None, false, 0, false, 0) },
    {730,  // RESEARCH_STIMPACK
    AbilityData(730, 0, None, false, 0, false, 0) },
    {731,  // RESEARCH_COMBATSHIELD
    AbilityData(731, 0, None, false, 0, false, 0) },
    {732,  // RESEARCH_CONCUSSIVESHELLS
    AbilityData(732, 0, None, false, 0, false, 0) },
    {761,  // RESEARCH_INFERNALPREIGNITER
    AbilityData(761, 0, None, false, 0, false, 0) },
    {763,  // RESEARCH_TRANSFORMATIONSERVOS
    AbilityData(763, 0, None, false, 0, false, 0) },
    {764,  // RESEARCH_DRILLINGCLAWS
    AbilityData(764, 0, None, false, 0, false, 0) },
    {765,  // RESEARCH_LOCKONRANGEUPGRADE
    AbilityData(765, 0, None, false, 0, false, 0) },
    {766,  // RESEARCH_SMARTSERVOS
    AbilityData(766, 0, None, false, 0, false, 0) },
    {767,  // RESEARCH_ARMORPIERCINGROCKETS
    AbilityData(767, 0, None, false, 0, false, 0) },
    {768,  // RESEARCH_CYCLONERAPIDFIRELAUNCHERS
    AbilityData(768, 0, None, false, 0, false, 0) },
    {769,  // RESEARCH_CYCLONELOCKONDAMAGE
    AbilityData(769, 0, None, false, 0, false, 0) },
    {770,  // RESEARCH_CYCLONERESEARCHHURRICANETHRUSTERS
    AbilityData(770, 0, None, false, 0, false, 0) },
    {790,  // RESEARCH_BANSHEECLOAKINGFIELD
    AbilityData(790, 0, None, false, 0, false, 0) },
    {792,  // RESEARCH_MEDIVACENERGYUPGRADE
    AbilityData(792, 0, None, false, 0, false, 0) },
    {793,  // RESEARCH_RAVENCORVIDREACTOR
    AbilityData(793, 0, None, false, 0, false, 0) },
    {796,  // RESEARCH_SEEKERMISSILE
    AbilityData(796, 0, None, false, 0, false, 0) },
    {797,  // RESEARCH_DURABLEMATERIALS
    AbilityData(797, 0, None, false, 0, false, 0) },
    {799,  // RESEARCH_BANSHEEHYPERFLIGHTROTORS
    AbilityData(799, 0, None, false, 0, false, 0) },
    {800,  // RESEARCH_LIBERATORAGMODE
    AbilityData(800, 0, None, false, 0, false, 0) },
    {802,  // RESEARCH_RAPIDDEPLOYMENT
    AbilityData(802, 0, None, false, 0, false, 0) },
    {803,  // RESEARCH_RAVENRECALIBRATEDEXPLOSIVES
    AbilityData(803, 0, None, false, 0, false, 0) },
    {804,  // RESEARCH_HIGHCAPACITYFUELTANKS
    AbilityData(804, 0, None, false, 0, false, 0) },
    {805,  // RESEARCH_ADVANCEDBALLISTICS
    AbilityData(805, 0, None, false, 0, false, 0) },
    {806,  // RESEARCH_ENHANCEDMUNITIONS
    AbilityData(806, 0, None, false, 0, false, 0) },
    {807,  // RESEARCH_RAVENINTERFERENCEMATRIX
    AbilityData(807, 0, None, false, 0, false, 0) },
    {820,  // RESEARCH_PERSONALCLOAKING
    AbilityData(820, 0, None, false, 0, false, 0) },
    {852,  // RESEARCH_TERRANVEHICLEPLATINGLEVEL1
    AbilityData(852, 0, None, false, 0, false, 0) },
    {853,  // RESEARCH_TERRANVEHICLEPLATINGLEVEL2
    AbilityData(853, 0, None, false, 0, false, 0) },
    {854,  // RESEARCH_TERRANVEHICLEPLATINGLEVEL3
    AbilityData(854, 0, None, false, 0, false, 0) },
    {858,  // RESEARCH_TERRANSHIPPLATINGLEVEL1
    AbilityData(858, 0, None, false, 0, false, 0) },
    {859,  // RESEARCH_TERRANSHIPPLATINGLEVEL2
    AbilityData(859, 0, None, false, 0, false, 0) },
    {860,  // RESEARCH_TERRANSHIPPLATINGLEVEL3
    AbilityData(860, 0, None, false, 0, false, 0) },
    {880,  // BUILD_NEXUS
    AbilityData(880, 0, Point, false, 5, false, 0) },
    {881,  // BUILD_PYLON
    AbilityData(881, 0, Point, false, 2, false, 0) },
    {882,  // BUILD_ASSIMILATOR
    AbilityData(882, 0, Unit, false, 3, false, 0) },
    {883,  // BUILD_GATEWAY
    AbilityData(883, 0, Point, false, 3, false, 0) },
    {884,  // BUILD_FORGE
    AbilityData(884, 0, Point, false, 3, false, 0) },
    {885,  // BUILD_FLEETBEACON
    AbilityData(885, 0, Point, false, 3, false, 0) },
    {886,  // BUILD_TWILIGHTCOUNCIL
    AbilityData(886, 0, Point, false, 3, false, 0) },
    {887,  // BUILD_PHOTONCANNON
    AbilityData(887, 0, Point, false, 2, false, 0) },
    {889,  // BUILD_STARGATE
    AbilityData(889, 0, Point, false, 3, false, 0) },
    {890,  // BUILD_TEMPLARARCHIVE
    AbilityData(890, 0, Point, false, 3, false, 0) },
    {891,  // BUILD_DARKSHRINE
    AbilityData(891, 0, Point, false, 2, false, 0) },
    {892,  // BUILD_ROBOTICSBAY
    AbilityData(892, 0, Point, false, 3, false, 0) },
    {893,  // BUILD_ROBOTICSFACILITY
    AbilityData(893, 0, Point, false, 3, false, 0) },
    {894,  // BUILD_CYBERNETICSCORE
    AbilityData(894, 0, Point, false, 3, false, 0) },
    {895,  // BUILD_SHIELDBATTERY
    AbilityData(895, 0, Point, false, 2, false, 0) },
    {916,  // TRAIN_ZEALOT
    AbilityData(916, 0, None, false, 0, false, 0) },
    {917,  // TRAIN_STALKER
    AbilityData(917, 0, None, false, 0, false, 0) },
    {919,  // TRAIN_HIGHTEMPLAR
    AbilityData(919, 0, None, false, 0, false, 0) },
    {920,  // TRAIN_DARKTEMPLAR
    AbilityData(920, 0, None, false, 0, false, 0) },
    {921,  // TRAIN_SENTRY
    AbilityData(921, 0, None, false, 0, false, 0) },
    {922,  // TRAIN_ADEPT
    AbilityData(922, 0, None, false, 0, false, 0) },
    {946,  // TRAIN_PHOENIX
    AbilityData(946, 0, None, false, 0, false, 0) },
    {948,  // TRAIN_CARRIER
    AbilityData(948, 0, None, false, 0, false, 0) },
    {950,  // TRAIN_VOIDRAY
    AbilityData(950, 0, None, false, 0, false, 0) },
    {954,  // TRAIN_ORACLE
    AbilityData(954, 0, None, false, 0, false, 0) },
    {955,  // TRAIN_TEMPEST
    AbilityData(955, 0, None, false, 0, false, 0) },
    {976,  // TRAIN_WARPPRISM
    AbilityData(976, 0, None, false, 0, false, 0) },
    {977,  // TRAIN_OBSERVER
    AbilityData(977, 0, None, false, 0, false, 0) },
    {978,  // TRAIN_COLOSSUS
    AbilityData(978, 0, None, false, 0, false, 0) },
    {979,  // TRAIN_IMMORTAL
    AbilityData(979, 0, None, false, 0, false, 0) },
    {994,  // TRAIN_DISRUPTOR
    AbilityData(994, 0, None, false, 0, false, 0) },
    {1006,  // TRAIN_PROBE
    AbilityData(1006, 0, None, false, 0, false, 0) },
    {1036,  // EFFECT_PSISTORM
    AbilityData(1036, 0, Point, false, 0, false, 8) },
    {1042,  // BUILD_INTERCEPTORS
    AbilityData(1042, 0, None, true, 0, false, 0) },
    {1093,  // RESEARCH_GRAVITICBOOSTER
    AbilityData(1093, 0, None, false, 0, false, 0) },
    {1094,  // RESEARCH_GRAVITICDRIVE
    AbilityData(1094, 0, None, false, 0, false, 0) },
    {1097,  // RESEARCH_EXTENDEDTHERMALLANCE
    AbilityData(1097, 0, None, false, 0, false, 0) },
    {1099,  // RESEARCH_IMMORTALREVIVE
    AbilityData(1099, 0, None, false, 0, false, 0) },
    {1126,  // RESEARCH_PSISTORM
    AbilityData(1126, 0, None, false, 0, false, 0) },
    {1152,  // BUILD_HATCHERY
    AbilityData(1152, 0, Point, false, 5, false, 0) },
    {1153,  // BUILD_CREEPTUMOR
    AbilityData(1153, 0, Point, false, 1, false, 0) },
    {1154,  // BUILD_EXTRACTOR
    AbilityData(1154, 0, Unit, false, 3, false, 0) },
    {1155,  // BUILD_SPAWNINGPOOL
    AbilityData(1155, 0, Point, false, 3, false, 0) },
    {1156,  // BUILD_EVOLUTIONCHAMBER
    AbilityData(1156, 0, Point, false, 3, false, 0) },
    {1157,  // BUILD_HYDRALISKDEN
    AbilityData(1157, 0, Point, false, 3, false, 0) },
    {1158,  // BUILD_SPIRE
    AbilityData(1158, 0, Point, false, 2, false, 0) },
    {1159,  // BUILD_ULTRALISKCAVERN
    AbilityData(1159, 0, Point, false, 3, false, 0) },
    {1160,  // BUILD_INFESTATIONPIT
    AbilityData(1160, 0, Point, false, 3, false, 0) },
    {1161,  // BUILD_NYDUSNETWORK
    AbilityData(1161, 0, Point, false, 3, false, 0) },
    {1162,  // BUILD_BANELINGNEST
    AbilityData(1162, 0, Point, false, 3, false, 0) },
    {1163,  // BUILD_LURKERDEN
    AbilityData(1163, 0, Point, false, 3, false, 0) },
    {1165,  // BUILD_ROACHWARREN
    AbilityData(1165, 0, Point, false, 3, false, 0) },
    {1166,  // BUILD_SPINECRAWLER
    AbilityData(1166, 0, Point, false, 2, false, 0) },
    {1167,  // BUILD_SPORECRAWLER
    AbilityData(1167, 0, Point, false, 2, false, 0) },
    {1195,  // EVOLUTIONCHAMBERRESEARCH_EVOLVEPROPULSIVEPERISTALSIS
    AbilityData(1195, 0, None, false, 0, false, 0) },
    {1216,  // MORPH_LAIR
    AbilityData(1216, 0, None, false, 0, false, 0) },
    {1218,  // MORPH_HIVE
    AbilityData(1218, 0, None, false, 0, false, 0) },
    {1220,  // MORPH_GREATERSPIRE
    AbilityData(1220, 0, None, false, 0, false, 0) },
    {1223,  // RESEARCH_PNEUMATIZEDCARAPACE
    AbilityData(1223, 0, None, false, 0, false, 0) },
    {1224,  // RESEARCH_EVOLVEVENTRALSACKS
    AbilityData(1224, 0, None, false, 0, false, 0) },
    {1225,  // RESEARCH_BURROW
    AbilityData(1225, 0, None, false, 0, false, 0) },
    {1252,  // RESEARCH_ZERGLINGADRENALGLANDS
    AbilityData(1252, 0, None, false, 0, false, 0) },
    {1253,  // RESEARCH_ZERGLINGMETABOLICBOOST
    AbilityData(1253, 0, None, false, 0, false, 0) },
    {1282,  // RESEARCH_GROOVEDSPINES
    AbilityData(1282, 0, None, false, 0, false, 0) },
    {1283,  // RESEARCH_MUSCULARAUGMENTS
    AbilityData(1283, 0, None, false, 0, false, 0) },
    {1286,  // RESEARCH_LURKERRANGE
    AbilityData(1286, 0, None, false, 0, false, 0) },
    {1342,  // TRAIN_DRONE
    AbilityData(1342, 0, None, false, 0, false, 0) },
    {1343,  // TRAIN_ZERGLING
    AbilityData(1343, 0, None, false, 0, false, 0) },
    {1344,  // TRAIN_OVERLORD
    AbilityData(1344, 0, None, false, 0, false, 0) },
    {1345,  // TRAIN_HYDRALISK
    AbilityData(1345, 0, None, false, 0, false, 0) },
    {1346,  // TRAIN_MUTALISK
    AbilityData(1346, 0, None, false, 0, false, 0) },
    {1348,  // TRAIN_ULTRALISK
    AbilityData(1348, 0, None, false, 0, false, 0) },
    {1351,  // TRAIN_ROACH
    AbilityData(1351, 0, None, false, 0, false, 0) },
    {1352,  // TRAIN_INFESTOR
    AbilityData(1352, 0, None, false, 0, false, 0) },
    {1353,  // TRAIN_CORRUPTOR
    AbilityData(1353, 0, None, false, 0, false, 0) },
    {1354,  // TRAIN_VIPER
    AbilityData(1354, 0, None, false, 0, false, 0) },
    {1356,  // TRAIN_SWARMHOST
    AbilityData(1356, 0, None, false, 0, false, 0) },
    {1372,  // MORPH_BROODLORD
    AbilityData(1372, 0, None, false, 0, false, 0) },
    {1413,  // TRAINWARP_ZEALOT
    AbilityData(1413, 0, Point, false, 0, false, 0) },
    {1414,  // TRAINWARP_STALKER
    AbilityData(1414, 0, Point, false, 0, false, 0) },
    {1416,  // TRAINWARP_HIGHTEMPLAR
    AbilityData(1416, 0, Point, false, 0, false, 0) },
    {1417,  // TRAINWARP_DARKTEMPLAR
    AbilityData(1417, 0, Point, false, 0, false, 0) },
    {1418,  // TRAINWARP_SENTRY
    AbilityData(1418, 0, Point, false, 0, false, 0) },
    {1419,  // TRAINWARP_ADEPT
    AbilityData(1419, 0, Point, false, 0, false, 0) },
    {1448,  // MORPH_OVERSEER
    AbilityData(1448, 0, None, false, 0, false, 0) },
    {1450,  // MORPH_PLANETARYFORTRESS
    AbilityData(1450, 0, None, false, 0, false, 0) },
    {1455,  // RESEARCH_NEURALPARASITE
    AbilityData(1455, 0, None, false, 0, false, 0) },
    {1456,  // RESEARCH_LOCUSTLIFETIMEINCREASE
    AbilityData(1456, 0, None, false, 0, false, 0) },
    {1457,  // RESEARCH_EVOLVEAMORPHOUSARMORCLOUD
    AbilityData(1457, 0, None, false, 0, false, 0) },
    {1482,  // RESEARCH_CENTRIFUGALHOOKS
    AbilityData(1482, 0, None, false, 0, false, 0) },
    {1516,  // MORPH_ORBITALCOMMAND
    AbilityData(1516, 0, None, false, 0, false, 0) },
    {1518,  // MORPH_WARPGATE
    AbilityData(1518, 0, None, false, 0, false, 0) },
    {1520,  // MORPH_GATEWAY
    AbilityData(1520, 0, None, false, 0, false, 0) },
    {1526,  // EFFECT_FORCEFIELD
    AbilityData(1526, 0, Point, false, 0, false, 9) },
    {1528,  // MORPH_WARPPRISMPHASINGMODE
    AbilityData(1528, 0, None, false, 0, false, 0) },
    {1530,  // MORPH_WARPPRISMTRANSPORTMODE
    AbilityData(1530, 0, None, false, 0, false, 0) },
    {1532,  // RESEARCH_BATTLECRUISERWEAPONREFIT
    AbilityData(1532, 0, None, false, 0, false, 0) },
    {1533,  // RESEARCH_BALLISTICRANGE
    AbilityData(1533, 0, None, false, 0, false, 0) },
    {1534,  // RESEARCH_RAPIDREIGNITIONSYSTEM
    AbilityData(1534, 0, None, false, 0, false, 0) },
    {1568,  // RESEARCH_WARPGATE
    AbilityData(1568, 0, None, false, 0, false, 0) },
    {1571,  // RESEARCH_HALLUCINATION
    AbilityData(1571, 0, None, false, 0, false, 0) },
    {1592,  // RESEARCH_CHARGE
    AbilityData(1592, 0, None, false, 0, false, 0) },
    {1593,  // RESEARCH_BLINK
    AbilityData(1593, 0, None, false, 0, false, 0) },
    {1594,  // RESEARCH_ADEPTRESONATINGGLAIVES
    AbilityData(1594, 0, None, false, 0, false, 0) },
    {1595,  // RESEARCH_PSIONICSURGE
    AbilityData(1595, 0, None, false, 0, false, 0) },
    {1596,  // RESEARCH_AMPLIFIEDSHIELDING
    AbilityData(1596, 0, None, false, 0, false, 0) },
    {1597,  // RESEARCH_PSIONICAMPLIFIERS
    AbilityData(1597, 0, None, false, 0, false, 0) },
    {1622,  // EFFECT_NUKECALLDOWN
    AbilityData(1622, 0, Point, false, 0, false, 12) },
    {1628,  // EFFECT_EMP
    AbilityData(1628, 0, Point, false, 0, false, 10) },
    {1632,  // TRAIN_QUEEN
    AbilityData(1632, 0, None, false, 0, false, 0) },
    {1664,  // EFFECT_TRANSFUSION
    AbilityData(1664, 0, Unit, false, 0, false, 7) },
    {1668,  // BARRACKSTECHLABMORPH_TECHLABBARRACKS
    AbilityData(1668, 0, None, false, 0, false, 0) },
    {1670,  // FACTORYTECHLABMORPH_TECHLABFACTORY
    AbilityData(1670, 0, None, false, 0, false, 0) },
    {1672,  // STARPORTTECHLABMORPH_TECHLABSTARPORT
    AbilityData(1672, 0, None, false, 0, false, 0) },
    {1676,  // BARRACKSREACTORMORPH_REACTOR
    AbilityData(1676, 0, None, false, 0, false, 0) },
    {1678,  // FACTORYREACTORMORPH_REACTOR
    AbilityData(1678, 0, None, false, 0, false, 0) },
    {1680,  // STARPORTREACTORMORPH_REACTOR
    AbilityData(1680, 0, None, false, 0, false, 0) },
    {1692,  // BEHAVIOR_GENERATECREEPON
    AbilityData(1692, 0, None, false, 0, false, 0) },
    {1693,  // BEHAVIOR_GENERATECREEPOFF
    AbilityData(1693, 0, None, false, 0, false, 0) },
    {1766,  // MORPH_ARCHON
    AbilityData(1766, 0, None, false, 0, false, 0) },
    {1767,  // ARCHONWARP_ARCHONWARPTARGET
    AbilityData(1767, 0, Unit, false, 0, false, 0) },
    {1768,  // BUILD_NYDUSWORM
    AbilityData(1768, 0, Point, false, 3, false, 0) },
    {1769,  // BUILDNYDUSCANAL_SUMMONNYDUSCANALATTACKER
    AbilityData(1769, 0, Point, false, 2, false, 0) },
    {1819,  // EFFECT_CHARGE
    AbilityData(1819, 0, Unit, true, 0, false, 0) },
    {1821,  // HERDINTERACT_HERD
    AbilityData(1821, 0, Unit, true, 0, false, 10) },
    {1825,  // EFFECT_CONTAMINATE
    AbilityData(1825, 0, Unit, false, 0, false, 3) },
    {1839,  // DIGESTERCREEPSPRAY
    AbilityData(1839, 0, Point, false, 0, false, 500) },
    {1847,  // MORPH_MOTHERSHIP
    AbilityData(1847, 0, None, false, 0, false, 0) },
    {1928,  // XELNAGAHEALINGSHRINE
    AbilityData(1928, 0, None, true, 0, false, 0) },
    {1930,  // NEXUSINVULNERABILITY
    AbilityData(1930, 0, Unit, false, 0, false, 10) },
    {1978,  // MORPH_HELLION
    AbilityData(1978, 0, None, false, 0, false, 0) },
    {1998,  // MORPH_HELLBAT
    AbilityData(1998, 0, None, false, 0, false, 0) },
    {2058,  // STOPPROTOSSBUILDING_HOLDFIRE
    AbilityData(2058, 0, None, false, 0, false, 0) },
    {2059,  // STOPPROTOSSBUILDING_CHEER
    AbilityData(2059, 0, None, false, 0, false, 0) },
    {2060,  // STOPPROTOSSBUILDING_DANCE
    AbilityData(2060, 0, None, false, 0, false, 0) },
    {2063,  // EFFECT_BLINDINGCLOUD
    AbilityData(2063, 0, Point, false, 0, false, 10) },
    {2067,  // EFFECT_ABDUCT
    AbilityData(2067, 0, Unit, false, 0, false, 9) },
    {2081,  // BEHAVIOR_BUILDINGATTACKON
    AbilityData(2081, 0, None, false, 0, false, 0) },
    {2082,  // BEHAVIOR_BUILDINGATTACKOFF
    AbilityData(2082, 0, None, false, 0, false, 0) },
    {2083,  // PICKUPSCRAPSMALL
    AbilityData(2083, 0, Unit, true, 0, false, 1) },
    {2085,  // PICKUPSCRAPMEDIUM
    AbilityData(2085, 0, Unit, true, 0, false, 1) },
    {2087,  // PICKUPSCRAPLARGE
    AbilityData(2087, 0, Unit, true, 0, false, 1) },
    {2089,  // PICKUPPALLETGAS
    AbilityData(2089, 0, Unit, true, 0, false, 1) },
    {2091,  // PICKUPPALLETMINERALS
    AbilityData(2091, 0, Unit, true, 0, false, 1) },
    {2093,  // MASSIVEKNOCKOVER
    AbilityData(2093, 0, Unit, true, 0, false, 1) },
    {2099,  // EFFECT_WIDOWMINEATTACK
    AbilityData(2099, 0, Unit, true, 0, false, 5) },
    {2101,  // TORNADOMISSILE
    AbilityData(2101, 0, Unit, true, 0, false, 0) },
    {2114,  // HALLUCINATION_ORACLE
    AbilityData(2114, 0, None, false, 0, false, 0) },
    {2116,  // EFFECT_MEDIVACIGNITEAFTERBURNERS
    AbilityData(2116, 0, None, false, 0, false, 0) },
    {2118,  // EXTENDINGBRIDGENEWIDE8OUT_BRIDGEEXTEND
    AbilityData(2118, 0, None, false, 0, false, 0) },
    {2120,  // EXTENDINGBRIDGENEWIDE8_BRIDGERETRACT
    AbilityData(2120, 0, None, false, 0, false, 0) },
    {2122,  // EXTENDINGBRIDGENWWIDE8OUT_BRIDGEEXTEND
    AbilityData(2122, 0, None, false, 0, false, 0) },
    {2124,  // EXTENDINGBRIDGENWWIDE8_BRIDGERETRACT
    AbilityData(2124, 0, None, false, 0, false, 0) },
    {2126,  // EXTENDINGBRIDGENEWIDE10OUT_BRIDGEEXTEND
    AbilityData(2126, 0, None, false, 0, false, 0) },
    {2128,  // EXTENDINGBRIDGENEWIDE10_BRIDGERETRACT
    AbilityData(2128, 0, None, false, 0, false, 0) },
    {2130,  // EXTENDINGBRIDGENWWIDE10OUT_BRIDGEEXTEND
    AbilityData(2130, 0, None, false, 0, false, 0) },
    {2132,  // EXTENDINGBRIDGENWWIDE10_BRIDGERETRACT
    AbilityData(2132, 0, None, false, 0, false, 0) },
    {2134,  // EXTENDINGBRIDGENEWIDE12OUT_BRIDGEEXTEND
    AbilityData(2134, 0, None, false, 0, false, 0) },
    {2136,  // EXTENDINGBRIDGENEWIDE12_BRIDGERETRACT
    AbilityData(2136, 0, None, false, 0, false, 0) },
    {2138,  // EXTENDINGBRIDGENWWIDE12OUT_BRIDGEEXTEND
    AbilityData(2138, 0, None, false, 0, false, 0) },
    {2140,  // EXTENDINGBRIDGENWWIDE12_BRIDGERETRACT
    AbilityData(2140, 0, None, false, 0, false, 0) },
    {2144,  // CRITTERFLEE
    AbilityData(2144, 0, Point, true, 0, false, 5) },
    {2146,  // EFFECT_ORACLEREVELATION
    AbilityData(2146, 0, Point, false, 0, false, 12) },
    {2158,  // ULTRALISKWEAPONCOOLDOWN
    AbilityData(2158, 0, None, false, 0, false, 0) },
    {2162,  // EFFECT_PHOTONOVERCHARGE
    AbilityData(2162, 0, Unit, false, 0, false, 10) },
    {2164,  // XELNAGA_CAVERNS_DOORE_XELNAGA_CAVERNS_DOORDEFAULTCLOSE
    AbilityData(2164, 0, None, false, 0, false, 0) },
    {2166,  // XELNAGA_CAVERNS_DOOREOPENED_XELNAGA_CAVERNS_DOORDEFAULTCLOSE
    AbilityData(2166, 0, None, false, 0, false, 0) },
    {2168,  // XELNAGA_CAVERNS_DOORN_XELNAGA_CAVERNS_DOORDEFAULTCLOSE
    AbilityData(2168, 0, None, false, 0, false, 0) },
    {2170,  // XELNAGA_CAVERNS_DOORNE_XELNAGA_CAVERNS_DOORDEFAULTCLOSE
    AbilityData(2170, 0, None, false, 0, false, 0) },
    {2172,  // XELNAGA_CAVERNS_DOORNEOPENED_XELNAGA_CAVERNS_DOORDEFAULTOPEN
    AbilityData(2172, 0, None, false, 0, false, 0) },
    {2174,  // XELNAGA_CAVERNS_DOORNOPENED_XELNAGA_CAVERNS_DOORDEFAULTOPEN
    AbilityData(2174, 0, None, false, 0, false, 0) },
    {2176,  // XELNAGA_CAVERNS_DOORNW_XELNAGA_CAVERNS_DOORDEFAULTCLOSE
    AbilityData(2176, 0, None, false, 0, false, 0) },
    {2178,  // XELNAGA_CAVERNS_DOORNWOPENED_XELNAGA_CAVERNS_DOORDEFAULTOPEN
    AbilityData(2178, 0, None, false, 0, false, 0) },
    {2180,  // XELNAGA_CAVERNS_DOORS_XELNAGA_CAVERNS_DOORDEFAULTCLOSE
    AbilityData(2180, 0, None, false, 0, false, 0) },
    {2182,  // XELNAGA_CAVERNS_DOORSE_XELNAGA_CAVERNS_DOORDEFAULTCLOSE
    AbilityData(2182, 0, None, false, 0, false, 0) },
    {2184,  // XELNAGA_CAVERNS_DOORSEOPENED_XELNAGA_CAVERNS_DOORDEFAULTOPEN
    AbilityData(2184, 0, None, false, 0, false, 0) },
    {2186,  // XELNAGA_CAVERNS_DOORSOPENED_XELNAGA_CAVERNS_DOORDEFAULTOPEN
    AbilityData(2186, 0, None, false, 0, false, 0) },
    {2188,  // XELNAGA_CAVERNS_DOORSW_XELNAGA_CAVERNS_DOORDEFAULTCLOSE
    AbilityData(2188, 0, None, false, 0, false, 0) },
    {2190,  // XELNAGA_CAVERNS_DOORSWOPENED_XELNAGA_CAVERNS_DOORDEFAULTOPEN
    AbilityData(2190, 0, None, false, 0, false, 0) },
    {2192,  // XELNAGA_CAVERNS_DOORW_XELNAGA_CAVERNS_DOORDEFAULTCLOSE
    AbilityData(2192, 0, None, false, 0, false, 0) },
    {2194,  // XELNAGA_CAVERNS_DOORWOPENED_XELNAGA_CAVERNS_DOORDEFAULTOPEN
    AbilityData(2194, 0, None, false, 0, false, 0) },
    {2196,  // XELNAGA_CAVERNS_FLOATING_BRIDGENE8OUT_BRIDGEEXTEND
    AbilityData(2196, 0, None, false, 0, false, 0) },
    {2198,  // XELNAGA_CAVERNS_FLOATING_BRIDGENE8_BRIDGERETRACT
    AbilityData(2198, 0, None, false, 0, false, 0) },
    {2200,  // XELNAGA_CAVERNS_FLOATING_BRIDGENW8OUT_BRIDGEEXTEND
    AbilityData(2200, 0, None, false, 0, false, 0) },
    {2202,  // XELNAGA_CAVERNS_FLOATING_BRIDGENW8_BRIDGERETRACT
    AbilityData(2202, 0, None, false, 0, false, 0) },
    {2204,  // XELNAGA_CAVERNS_FLOATING_BRIDGENE10OUT_BRIDGEEXTEND
    AbilityData(2204, 0, None, false, 0, false, 0) },
    {2206,  // XELNAGA_CAVERNS_FLOATING_BRIDGENE10_BRIDGERETRACT
    AbilityData(2206, 0, None, false, 0, false, 0) },
    {2208,  // XELNAGA_CAVERNS_FLOATING_BRIDGENW10OUT_BRIDGEEXTEND
    AbilityData(2208, 0, None, false, 0, false, 0) },
    {2210,  // XELNAGA_CAVERNS_FLOATING_BRIDGENW10_BRIDGERETRACT
    AbilityData(2210, 0, None, false, 0, false, 0) },
    {2212,  // XELNAGA_CAVERNS_FLOATING_BRIDGENE12OUT_BRIDGEEXTEND
    AbilityData(2212, 0, None, false, 0, false, 0) },
    {2214,  // XELNAGA_CAVERNS_FLOATING_BRIDGENE12_BRIDGERETRACT
    AbilityData(2214, 0, None, false, 0, false, 0) },
    {2216,  // XELNAGA_CAVERNS_FLOATING_BRIDGENW12OUT_BRIDGEEXTEND
    AbilityData(2216, 0, None, false, 0, false, 0) },
    {2218,  // XELNAGA_CAVERNS_FLOATING_BRIDGENW12_BRIDGERETRACT
    AbilityData(2218, 0, None, false, 0, false, 0) },
    {2220,  // XELNAGA_CAVERNS_FLOATING_BRIDGEH8OUT_BRIDGEEXTEND
    AbilityData(2220, 0, None, false, 0, false, 0) },
    {2222,  // XELNAGA_CAVERNS_FLOATING_BRIDGEH8_BRIDGERETRACT
    AbilityData(2222, 0, None, false, 0, false, 0) },
    {2224,  // XELNAGA_CAVERNS_FLOATING_BRIDGEV8OUT_BRIDGEEXTEND
    AbilityData(2224, 0, None, false, 0, false, 0) },
    {2226,  // XELNAGA_CAVERNS_FLOATING_BRIDGEV8_BRIDGERETRACT
    AbilityData(2226, 0, None, false, 0, false, 0) },
    {2228,  // XELNAGA_CAVERNS_FLOATING_BRIDGEH10OUT_BRIDGEEXTEND
    AbilityData(2228, 0, None, false, 0, false, 0) },
    {2230,  // XELNAGA_CAVERNS_FLOATING_BRIDGEH10_BRIDGERETRACT
    AbilityData(2230, 0, None, false, 0, false, 0) },
    {2232,  // XELNAGA_CAVERNS_FLOATING_BRIDGEV10OUT_BRIDGEEXTEND
    AbilityData(2232, 0, None, false, 0, false, 0) },
    {2234,  // XELNAGA_CAVERNS_FLOATING_BRIDGEV10_BRIDGERETRACT
    AbilityData(2234, 0, None, false, 0, false, 0) },
    {2236,  // XELNAGA_CAVERNS_FLOATING_BRIDGEH12OUT_BRIDGEEXTEND
    AbilityData(2236, 0, None, false, 0, false, 0) },
    {2238,  // XELNAGA_CAVERNS_FLOATING_BRIDGEH12_BRIDGERETRACT
    AbilityData(2238, 0, None, false, 0, false, 0) },
    {2240,  // XELNAGA_CAVERNS_FLOATING_BRIDGEV12OUT_BRIDGEEXTEND
    AbilityData(2240, 0, None, false, 0, false, 0) },
    {2242,  // XELNAGA_CAVERNS_FLOATING_BRIDGEV12_BRIDGERETRACT
    AbilityData(2242, 0, None, false, 0, false, 0) },
    {2244,  // EFFECT_TIMEWARP
    AbilityData(2244, 0, Point, false, 0, false, 9) },
    {2246,  // SNOWREFINERY_TERRAN_EXTENDINGBRIDGENESHORT8OUT_BRIDGEEXTEND
    AbilityData(2246, 0, None, false, 0, false, 0) },
    {2248,  // SNOWREFINERY_TERRAN_EXTENDINGBRIDGENESHORT8_BRIDGERETRACT
    AbilityData(2248, 0, None, false, 0, false, 0) },
    {2250,  // SNOWREFINERY_TERRAN_EXTENDINGBRIDGENWSHORT8OUT_BRIDGEEXTEND
    AbilityData(2250, 0, None, false, 0, false, 0) },
    {2252,  // SNOWREFINERY_TERRAN_EXTENDINGBRIDGENWSHORT8_BRIDGERETRACT
    AbilityData(2252, 0, None, false, 0, false, 0) },
    {2324,  // EFFECT_CAUSTICSPRAY
    AbilityData(2324, 0, Unit, false, 0, false, 6) },
    {2330,  // MORPH_RAVAGER
    AbilityData(2330, 0, None, false, 0, false, 0) },
    {2332,  // MORPH_LURKER
    AbilityData(2332, 0, None, false, 0, false, 0) },
    {2338,  // EFFECT_CORROSIVEBILE
    AbilityData(2338, 0, Point, false, 0, false, 9) },
    {2344,  // PURIFICATIONNOVA
    AbilityData(2344, 0, None, false, 0, false, 0) },
    {2346,  // EFFECT_PURIFICATIONNOVA
    AbilityData(2346, 0, Point, false, 0, false, 500) },
    {2350,  // EFFECT_LOCKON
    AbilityData(2350, 0, Unit, true, 0, false, 7) },
    {2358,  // EFFECT_TACTICALJUMP
    AbilityData(2358, 0, Point, false, 0, false, 500) },
    {2362,  // MORPH_THORHIGHIMPACTMODE
    AbilityData(2362, 0, None, false, 0, false, 0) },
    {2364,  // MORPH_THOREXPLOSIVEMODE
    AbilityData(2364, 0, None, false, 0, false, 0) },
    {2375,  // BEHAVIOR_PULSARBEAMON
    AbilityData(2375, 0, None, false, 0, false, 0) },
    {2376,  // BEHAVIOR_PULSARBEAMOFF
    AbilityData(2376, 0, None, false, 0, false, 0) },
    {2383,  // LOCUSTMPFLYINGMORPHTOGROUND_LOCUSTMPFLYINGSWOOP
    AbilityData(2383, 0, None, false, 0, false, 0) },
    {2385,  // LOCUSTMPMORPHTOAIR_LOCUSTMPFLYINGSWOOP
    AbilityData(2385, 0, None, false, 0, false, 0) },
    {2387,  // EFFECT_LOCUSTSWOOP
    AbilityData(2387, 0, Point, false, 0, false, 6) },
    {2389,  // HALLUCINATION_DISRUPTOR
    AbilityData(2389, 0, None, false, 0, false, 0) },
    {2391,  // HALLUCINATION_ADEPT
    AbilityData(2391, 0, None, false, 0, false, 0) },
    {2393,  // EFFECT_VOIDRAYPRISMATICALIGNMENT
    AbilityData(2393, 0, None, false, 0, false, 0) },
    {2397,  // AIURLIGHTBRIDGENE8OUT_BRIDGEEXTEND
    AbilityData(2397, 0, None, false, 0, false, 0) },
    {2399,  // AIURLIGHTBRIDGENE8_BRIDGERETRACT
    AbilityData(2399, 0, None, false, 0, false, 0) },
    {2401,  // AIURLIGHTBRIDGENE10OUT_BRIDGEEXTEND
    AbilityData(2401, 0, None, false, 0, false, 0) },
    {2403,  // AIURLIGHTBRIDGENE10_BRIDGERETRACT
    AbilityData(2403, 0, None, false, 0, false, 0) },
    {2405,  // AIURLIGHTBRIDGENE12OUT_BRIDGEEXTEND
    AbilityData(2405, 0, None, false, 0, false, 0) },
    {2407,  // AIURLIGHTBRIDGENE12_BRIDGERETRACT
    AbilityData(2407, 0, None, false, 0, false, 0) },
    {2409,  // AIURLIGHTBRIDGENW8OUT_BRIDGEEXTEND
    AbilityData(2409, 0, None, false, 0, false, 0) },
    {2411,  // AIURLIGHTBRIDGENW8_BRIDGERETRACT
    AbilityData(2411, 0, None, false, 0, false, 0) },
    {2413,  // AIURLIGHTBRIDGENW10OUT_BRIDGEEXTEND
    AbilityData(2413, 0, None, false, 0, false, 0) },
    {2415,  // AIURLIGHTBRIDGENW10_BRIDGERETRACT
    AbilityData(2415, 0, None, false, 0, false, 0) },
    {2417,  // AIURLIGHTBRIDGENW12OUT_BRIDGEEXTEND
    AbilityData(2417, 0, None, false, 0, false, 0) },
    {2419,  // AIURLIGHTBRIDGENW12_BRIDGERETRACT
    AbilityData(2419, 0, None, false, 0, false, 0) },
    {2445,  // SHAKURASLIGHTBRIDGENE8OUT_BRIDGEEXTEND
    AbilityData(2445, 0, None, false, 0, false, 0) },
    {2447,  // SHAKURASLIGHTBRIDGENE8_BRIDGERETRACT
    AbilityData(2447, 0, None, false, 0, false, 0) },
    {2449,  // SHAKURASLIGHTBRIDGENE10OUT_BRIDGEEXTEND
    AbilityData(2449, 0, None, false, 0, false, 0) },
    {2451,  // SHAKURASLIGHTBRIDGENE10_BRIDGERETRACT
    AbilityData(2451, 0, None, false, 0, false, 0) },
    {2453,  // SHAKURASLIGHTBRIDGENE12OUT_BRIDGEEXTEND
    AbilityData(2453, 0, None, false, 0, false, 0) },
    {2455,  // SHAKURASLIGHTBRIDGENE12_BRIDGERETRACT
    AbilityData(2455, 0, None, false, 0, false, 0) },
    {2457,  // SHAKURASLIGHTBRIDGENW8OUT_BRIDGEEXTEND
    AbilityData(2457, 0, None, false, 0, false, 0) },
    {2459,  // SHAKURASLIGHTBRIDGENW8_BRIDGERETRACT
    AbilityData(2459, 0, None, false, 0, false, 0) },
    {2461,  // SHAKURASLIGHTBRIDGENW10OUT_BRIDGEEXTEND
    AbilityData(2461, 0, None, false, 0, false, 0) },
    {2463,  // SHAKURASLIGHTBRIDGENW10_BRIDGERETRACT
    AbilityData(2463, 0, None, false, 0, false, 0) },
    {2465,  // SHAKURASLIGHTBRIDGENW12OUT_BRIDGEEXTEND
    AbilityData(2465, 0, None, false, 0, false, 0) },
    {2467,  // SHAKURASLIGHTBRIDGENW12_BRIDGERETRACT
    AbilityData(2467, 0, None, false, 0, false, 0) },
    {2469,  // VOIDMPIMMORTALREVIVEREBUILD_IMMORTAL
    AbilityData(2469, 0, None, false, 0, false, 0) },
    {2473,  // ARBITERMPSTASISFIELD
    AbilityData(2473, 0, PointOrUnit, false, 0, false, 9) },
    {2475,  // ARBITERMPRECALL
    AbilityData(2475, 0, Point, false, 0, false, 500) },
    {2477,  // CORSAIRMPDISRUPTIONWEB
    AbilityData(2477, 0, Point, false, 0, false, 9) },
    {2479,  // MORPH_MORPHTOGUARDIANMP
    AbilityData(2479, 0, None, false, 0, false, 0) },
    {2481,  // MORPH_MORPHTODEVOURERMP
    AbilityData(2481, 0, None, false, 0, false, 0) },
    {2483,  // DEFILERMPCONSUME
    AbilityData(2483, 0, Unit, false, 0, false, 0.5) },
    {2485,  // DEFILERMPDARKSWARM
    AbilityData(2485, 0, Point, false, 0, false, 8) },
    {2487,  // DEFILERMPPLAGUE
    AbilityData(2487, 0, Point, false, 0, false, 8) },
    {2493,  // QUEENMPENSNARE
    AbilityData(2493, 0, Point, false, 0, false, 9) },
    {2495,  // QUEENMPSPAWNBROODLINGS
    AbilityData(2495, 0, Unit, false, 0, false, 9) },
    {2497,  // QUEENMPINFESTCOMMANDCENTER
    AbilityData(2497, 0, None, false, 0, false, 1) },
    {2505,  // BUILD_STASISTRAP
    AbilityData(2505, 0, Point, false, 1, false, 0) },
    {2536,  // ORACLESTASISTRAPACTIVATE_ACTIVATESTASISWARD
    AbilityData(2536, 0, None, true, 0, false, 0) },
    {2542,  // EFFECT_PARASITICBOMB
    AbilityData(2542, 0, Unit, false, 0, false, 8) },
    {2544,  // EFFECT_ADEPTPHASESHIFT
    AbilityData(2544, 0, Point, false, 0, false, 500) },
    {2548,  // PURIFICATIONNOVAMORPHBACK_PURIFICATIONNOVA
    AbilityData(2548, 0, None, false, 0, false, 0) },
    {2554,  // LIBERATORMORPHTOAG_LIBERATORAGMODE
    AbilityData(2554, 0, None, false, 0, false, 0) },
    {2556,  // LIBERATORMORPHTOAA_LIBERATORAAMODE
    AbilityData(2556, 0, None, false, 0, false, 0) },
    {2558,  // MORPH_LIBERATORAGMODE
    AbilityData(2558, 0, Point, false, 0, false, 5) },
    {2560,  // MORPH_LIBERATORAAMODE
    AbilityData(2560, 0, None, false, 0, false, 0) },
    {2564,  // AIURLIGHTBRIDGEABANDONEDNE8OUT_BRIDGEEXTEND
    AbilityData(2564, 0, None, false, 0, false, 0) },
    {2566,  // AIURLIGHTBRIDGEABANDONEDNE8_BRIDGERETRACT
    AbilityData(2566, 0, None, false, 0, false, 0) },
    {2568,  // AIURLIGHTBRIDGEABANDONEDNE10OUT_BRIDGEEXTEND
    AbilityData(2568, 0, None, false, 0, false, 0) },
    {2570,  // AIURLIGHTBRIDGEABANDONEDNE10_BRIDGERETRACT
    AbilityData(2570, 0, None, false, 0, false, 0) },
    {2572,  // AIURLIGHTBRIDGEABANDONEDNE12OUT_BRIDGEEXTEND
    AbilityData(2572, 0, None, false, 0, false, 0) },
    {2574,  // AIURLIGHTBRIDGEABANDONEDNE12_BRIDGERETRACT
    AbilityData(2574, 0, None, false, 0, false, 0) },
    {2576,  // AIURLIGHTBRIDGEABANDONEDNW8OUT_BRIDGEEXTEND
    AbilityData(2576, 0, None, false, 0, false, 0) },
    {2578,  // AIURLIGHTBRIDGEABANDONEDNW8_BRIDGERETRACT
    AbilityData(2578, 0, None, false, 0, false, 0) },
    {2580,  // AIURLIGHTBRIDGEABANDONEDNW10OUT_BRIDGEEXTEND
    AbilityData(2580, 0, None, false, 0, false, 0) },
    {2582,  // AIURLIGHTBRIDGEABANDONEDNW10_BRIDGERETRACT
    AbilityData(2582, 0, None, false, 0, false, 0) },
    {2584,  // AIURLIGHTBRIDGEABANDONEDNW12OUT_BRIDGEEXTEND
    AbilityData(2584, 0, None, false, 0, false, 0) },
    {2586,  // AIURLIGHTBRIDGEABANDONEDNW12_BRIDGERETRACT
    AbilityData(2586, 0, None, false, 0, false, 0) },
    {2588,  // EFFECT_KD8CHARGE
    AbilityData(2588, 0, Point, false, 0, false, 5) },
    {2598,  // SLAYNELEMENTALGRAB
    AbilityData(2598, 0, Unit, false, 0, false, 10) },
    {2602,  // PORTCITY_BRIDGE_UNITNE8OUT_BRIDGEEXTEND
    AbilityData(2602, 0, None, false, 0, false, 0) },
    {2604,  // PORTCITY_BRIDGE_UNITNE8_BRIDGERETRACT
    AbilityData(2604, 0, None, false, 0, false, 0) },
    {2606,  // PORTCITY_BRIDGE_UNITSE8OUT_BRIDGEEXTEND
    AbilityData(2606, 0, None, false, 0, false, 0) },
    {2608,  // PORTCITY_BRIDGE_UNITSE8_BRIDGERETRACT
    AbilityData(2608, 0, None, false, 0, false, 0) },
    {2610,  // PORTCITY_BRIDGE_UNITNW8OUT_BRIDGEEXTEND
    AbilityData(2610, 0, None, false, 0, false, 0) },
    {2612,  // PORTCITY_BRIDGE_UNITNW8_BRIDGERETRACT
    AbilityData(2612, 0, None, false, 0, false, 0) },
    {2614,  // PORTCITY_BRIDGE_UNITSW8OUT_BRIDGEEXTEND
    AbilityData(2614, 0, None, false, 0, false, 0) },
    {2616,  // PORTCITY_BRIDGE_UNITSW8_BRIDGERETRACT
    AbilityData(2616, 0, None, false, 0, false, 0) },
    {2618,  // PORTCITY_BRIDGE_UNITNE10OUT_BRIDGEEXTEND
    AbilityData(2618, 0, None, false, 0, false, 0) },
    {2620,  // PORTCITY_BRIDGE_UNITNE10_BRIDGERETRACT
    AbilityData(2620, 0, None, false, 0, false, 0) },
    {2622,  // PORTCITY_BRIDGE_UNITSE10OUT_BRIDGEEXTEND
    AbilityData(2622, 0, None, false, 0, false, 0) },
    {2624,  // PORTCITY_BRIDGE_UNITSE10_BRIDGERETRACT
    AbilityData(2624, 0, None, false, 0, false, 0) },
    {2626,  // PORTCITY_BRIDGE_UNITNW10OUT_BRIDGEEXTEND
    AbilityData(2626, 0, None, false, 0, false, 0) },
    {2628,  // PORTCITY_BRIDGE_UNITNW10_BRIDGERETRACT
    AbilityData(2628, 0, None, false, 0, false, 0) },
    {2630,  // PORTCITY_BRIDGE_UNITSW10OUT_BRIDGEEXTEND
    AbilityData(2630, 0, None, false, 0, false, 0) },
    {2632,  // PORTCITY_BRIDGE_UNITSW10_BRIDGERETRACT
    AbilityData(2632, 0, None, false, 0, false, 0) },
    {2634,  // PORTCITY_BRIDGE_UNITNE12OUT_BRIDGEEXTEND
    AbilityData(2634, 0, None, false, 0, false, 0) },
    {2636,  // PORTCITY_BRIDGE_UNITNE12_BRIDGERETRACT
    AbilityData(2636, 0, None, false, 0, false, 0) },
    {2638,  // PORTCITY_BRIDGE_UNITSE12OUT_BRIDGEEXTEND
    AbilityData(2638, 0, None, false, 0, false, 0) },
    {2640,  // PORTCITY_BRIDGE_UNITSE12_BRIDGERETRACT
    AbilityData(2640, 0, None, false, 0, false, 0) },
    {2642,  // PORTCITY_BRIDGE_UNITNW12OUT_BRIDGEEXTEND
    AbilityData(2642, 0, None, false, 0, false, 0) },
    {2644,  // PORTCITY_BRIDGE_UNITNW12_BRIDGERETRACT
    AbilityData(2644, 0, None, false, 0, false, 0) },
    {2646,  // PORTCITY_BRIDGE_UNITSW12OUT_BRIDGEEXTEND
    AbilityData(2646, 0, None, false, 0, false, 0) },
    {2648,  // PORTCITY_BRIDGE_UNITSW12_BRIDGERETRACT
    AbilityData(2648, 0, None, false, 0, false, 0) },
    {2650,  // PORTCITY_BRIDGE_UNITN8OUT_BRIDGEEXTEND
    AbilityData(2650, 0, None, false, 0, false, 0) },
    {2652,  // PORTCITY_BRIDGE_UNITN8_BRIDGERETRACT
    AbilityData(2652, 0, None, false, 0, false, 0) },
    {2654,  // PORTCITY_BRIDGE_UNITS8OUT_BRIDGEEXTEND
    AbilityData(2654, 0, None, false, 0, false, 0) },
    {2656,  // PORTCITY_BRIDGE_UNITS8_BRIDGERETRACT
    AbilityData(2656, 0, None, false, 0, false, 0) },
    {2658,  // PORTCITY_BRIDGE_UNITE8OUT_BRIDGEEXTEND
    AbilityData(2658, 0, None, false, 0, false, 0) },
    {2660,  // PORTCITY_BRIDGE_UNITE8_BRIDGERETRACT
    AbilityData(2660, 0, None, false, 0, false, 0) },
    {2662,  // PORTCITY_BRIDGE_UNITW8OUT_BRIDGEEXTEND
    AbilityData(2662, 0, None, false, 0, false, 0) },
    {2664,  // PORTCITY_BRIDGE_UNITW8_BRIDGERETRACT
    AbilityData(2664, 0, None, false, 0, false, 0) },
    {2666,  // PORTCITY_BRIDGE_UNITN10OUT_BRIDGEEXTEND
    AbilityData(2666, 0, None, false, 0, false, 0) },
    {2668,  // PORTCITY_BRIDGE_UNITN10_BRIDGERETRACT
    AbilityData(2668, 0, None, false, 0, false, 0) },
    {2670,  // PORTCITY_BRIDGE_UNITS10OUT_BRIDGEEXTEND
    AbilityData(2670, 0, None, false, 0, false, 0) },
    {2672,  // PORTCITY_BRIDGE_UNITS10_BRIDGERETRACT
    AbilityData(2672, 0, None, false, 0, false, 0) },
    {2674,  // PORTCITY_BRIDGE_UNITE10OUT_BRIDGEEXTEND
    AbilityData(2674, 0, None, false, 0, false, 0) },
    {2676,  // PORTCITY_BRIDGE_UNITE10_BRIDGERETRACT
    AbilityData(2676, 0, None, false, 0, false, 0) },
    {2678,  // PORTCITY_BRIDGE_UNITW10OUT_BRIDGEEXTEND
    AbilityData(2678, 0, None, false, 0, false, 0) },
    {2680,  // PORTCITY_BRIDGE_UNITW10_BRIDGERETRACT
    AbilityData(2680, 0, None, false, 0, false, 0) },
    {2682,  // PORTCITY_BRIDGE_UNITN12OUT_BRIDGEEXTEND
    AbilityData(2682, 0, None, false, 0, false, 0) },
    {2684,  // PORTCITY_BRIDGE_UNITN12_BRIDGERETRACT
    AbilityData(2684, 0, None, false, 0, false, 0) },
    {2686,  // PORTCITY_BRIDGE_UNITS12OUT_BRIDGEEXTEND
    AbilityData(2686, 0, None, false, 0, false, 0) },
    {2688,  // PORTCITY_BRIDGE_UNITS12_BRIDGERETRACT
    AbilityData(2688, 0, None, false, 0, false, 0) },
    {2690,  // PORTCITY_BRIDGE_UNITE12OUT_BRIDGEEXTEND
    AbilityData(2690, 0, None, false, 0, false, 0) },
    {2692,  // PORTCITY_BRIDGE_UNITE12_BRIDGERETRACT
    AbilityData(2692, 0, None, false, 0, false, 0) },
    {2694,  // PORTCITY_BRIDGE_UNITW12OUT_BRIDGEEXTEND
    AbilityData(2694, 0, None, false, 0, false, 0) },
    {2696,  // PORTCITY_BRIDGE_UNITW12_BRIDGERETRACT
    AbilityData(2696, 0, None, false, 0, false, 0) },
    {2704,  // EFFECT_SPAWNLOCUSTS
    AbilityData(2704, 0, Point, false, 0, false, 500) },
    {2706,  // LOCUSTMPFLYINGSWOOPATTACK_LOCUSTMPFLYINGSWOOP
    AbilityData(2706, 0, PointOrUnit, false, 0, false, 6) },
    {2708,  // MORPH_OVERLORDTRANSPORT
    AbilityData(2708, 0, None, false, 0, false, 0) },
    {2714,  // EFFECT_GHOSTSNIPE
    AbilityData(2714, 0, Unit, false, 0, false, 10) },
    {2716,  // PURIFYMORPHPYLON_MOTHERSHIPCOREWEAPON
    AbilityData(2716, 0, None, false, 0, false, 0) },
    {2718,  // PURIFYMORPHPYLONBACK_MOTHERSHIPCOREWEAPON
    AbilityData(2718, 0, None, false, 0, false, 0) },
    {2720,  // RESEARCH_SHADOWSTRIKE
    AbilityData(2720, 0, None, false, 0, false, 0) },
    {3659,  // CANCEL
    AbilityData(3659, 0, None, false, 0, false, 0) },
    {3660,  // HALT
    AbilityData(3660, 0, None, false, 0, false, 0) },
    {3661,  // BURROWDOWN
    AbilityData(3661, 0, None, false, 0, false, 0) },
    {3662,  // BURROWUP
    AbilityData(3662, 0, None, true, 0, false, 0) },
    {3663,  // LOADALL
    AbilityData(3663, 0, None, false, 0, false, 0) },
    {3664,  // UNLOADALL
    AbilityData(3664, 0, None, false, 0, false, 0) },
    {3665,  // STOP
    AbilityData(3665, 0, None, false, 0, false, 0) },
    {3666,  // HARVEST_GATHER
    AbilityData(3666, 0, Unit, false, 0, false, 0) },
    {3667,  // HARVEST_RETURN
    AbilityData(3667, 0, None, false, 0, false, 0) },
    {3668,  // LOAD
    AbilityData(3668, 0, Unit, false, 0, false, 0) },
    {3669,  // UNLOADALLAT
    AbilityData(3669, 0, PointOrUnit, false, 0, false, 0) },
    {3670,  // UNLOADUNIT
    AbilityData(3670, 0, None, false, 0, false, 0) },
    {3671,  // CANCEL_LAST
    AbilityData(3671, 0, None, false, 0, false, 0) },
    {3672,  // CANCEL_SLOT
    AbilityData(3672, 0, None, false, 0, false, 0) },
    {3673,  // RALLY_UNITS
    AbilityData(3673, 0, PointOrUnit, false, 0, false, 0) },
    {3674,  // ATTACK
    AbilityData(3674, 0, PointOrUnit, false, 0, false, 0) },
    {3675,  // EFFECT_STIM
    AbilityData(3675, 0, None, false, 0, false, 0) },
    {3676,  // BEHAVIOR_CLOAKON
    AbilityData(3676, 0, None, false, 0, false, 0) },
    {3677,  // BEHAVIOR_CLOAKOFF
    AbilityData(3677, 0, None, false, 0, false, 0) },
    {3678,  // LAND
    AbilityData(3678, 0, Point, false, 0, false, 0) },
    {3679,  // LIFT
    AbilityData(3679, 0, None, false, 0, false, 0) },
    {3680,  // MORPH_ROOT
    AbilityData(3680, 0, Point, false, 0, false, 0) },
    {3681,  // MORPH_UPROOT
    AbilityData(3681, 0, None, false, 0, false, 0) },
    {3682,  // BUILD_TECHLAB
    AbilityData(3682, 0, PointOrNone, false, 7, true, 0) },
    {3683,  // BUILD_REACTOR
    AbilityData(3683, 0, PointOrNone, false, 7, true, 0) },
    {3684,  // EFFECT_SPRAY
    AbilityData(3684, 0, Point, false, 0, false, 1) },
    {3685,  // EFFECT_REPAIR
    AbilityData(3685, 0, Unit, true, 0, false, 6) },
    {3686,  // EFFECT_MASSRECALL
    AbilityData(3686, 0, Point, false, 0, false, 500) },
    {3687,  // EFFECT_BLINK
    AbilityData(3687, 0, Point, false, 0, false, 500) },
    {3688,  // BEHAVIOR_HOLDFIREON
    AbilityData(3688, 0, None, false, 0, false, 0) },
    {3689,  // BEHAVIOR_HOLDFIREOFF
    AbilityData(3689, 0, None, false, 0, false, 0) },
    {3690,  // RALLY_WORKERS
    AbilityData(3690, 0, PointOrUnit, false, 0, false, 0) },
    {3692,  // RESEARCH_PROTOSSAIRARMOR
    AbilityData(3692, 0, None, false, 0, false, 0) },
    {3693,  // RESEARCH_PROTOSSAIRWEAPONS
    AbilityData(3693, 0, None, false, 0, false, 0) },
    {3694,  // RESEARCH_PROTOSSGROUNDARMOR
    AbilityData(3694, 0, None, false, 0, false, 0) },
    {3695,  // RESEARCH_PROTOSSGROUNDWEAPONS
    AbilityData(3695, 0, None, false, 0, false, 0) },
    {3696,  // RESEARCH_PROTOSSSHIELDS
    AbilityData(3696, 0, None, false, 0, false, 0) },
    {3697,  // RESEARCH_TERRANINFANTRYARMOR
    AbilityData(3697, 0, None, false, 0, false, 0) },
    {3698,  // RESEARCH_TERRANINFANTRYWEAPONS
    AbilityData(3698, 0, None, false, 0, false, 0) },
    {3699,  // RESEARCH_TERRANSHIPWEAPONS
    AbilityData(3699, 0, None, false, 0, false, 0) },
    {3700,  // RESEARCH_TERRANVEHICLEANDSHIPPLATING
    AbilityData(3700, 0, None, false, 0, false, 0) },
    {3701,  // RESEARCH_TERRANVEHICLEWEAPONS
    AbilityData(3701, 0, None, false, 0, false, 0) },
    {3702,  // RESEARCH_ZERGFLYERARMOR
    AbilityData(3702, 0, None, false, 0, false, 0) },
    {3703,  // RESEARCH_ZERGFLYERATTACK
    AbilityData(3703, 0, None, false, 0, false, 0) },
    {3704,  // RESEARCH_ZERGGROUNDARMOR
    AbilityData(3704, 0, None, false, 0, false, 0) },
    {3705,  // RESEARCH_ZERGMELEEWEAPONS
    AbilityData(3705, 0, None, false, 0, false, 0) },
    {3706,  // RESEARCH_ZERGMISSILEWEAPONS
    AbilityData(3706, 0, None, false, 0, false, 0) },
    {3709,  // RESEARCH_ADAPTIVETALONS
    AbilityData(3709, 0, None, false, 0, false, 0) },
    {3739,  // MORPH_OBSERVERMODE
    AbilityData(3739, 0, None, false, 0, false, 0) },
    {3741,  // MORPH_SURVEILLANCEMODE
    AbilityData(3741, 0, None, false, 0, false, 0) },
    {3743,  // MORPH_OVERSIGHTMODE
    AbilityData(3743, 0, None, false, 0, false, 0) },
    {3745,  // MORPH_OVERSEERMODE
    AbilityData(3745, 0, None, false, 0, false, 0) },
    {3747,  // EFFECT_INTERFERENCEMATRIX
    AbilityData(3747, 0, Unit, false, 0, false, 9) },
    {3753,  // EFFECT_ANTIARMORMISSILE
    AbilityData(3753, 0, Unit, false, 0, false, 10) },
    {3755,  // EFFECT_CHRONOBOOSTENERGYCOST
    AbilityData(3755, 0, Unit, false, 0, false, 500) },
    {3763,  // INFESTORENSNARE
    AbilityData(3763, 0, Unit, false, 0, false, 8) },
    {3779,  // BATTLECRUISERMOVE_ACQUIREMOVE
    AbilityData(3779, 0, PointOrUnit, false, 0, false, 0) },
    {3780,  // BATTLECRUISERMOVE_TURN
    AbilityData(3780, 0, PointOrUnit, false, 0, false, 0) },
    {3784,  // BATTLECRUISERSTOP_HOLDFIRE
    AbilityData(3784, 0, None, false, 0, false, 0) },
    {3785,  // BATTLECRUISERSTOP_CHEER
    AbilityData(3785, 0, None, false, 0, false, 0) },
    {3786,  // BATTLECRUISERSTOP_DANCE
    AbilityData(3786, 0, None, false, 0, false, 0) },
    {3793,  // GENERAL_HOLDPOSITION
    AbilityData(3793, 0, None, false, 0, false, 0) },
    {3794,  // GENERAL_MOVE
    AbilityData(3794, 0, PointOrUnit, false, 0, false, 0) },
    {3795,  // GENERAL_PATROL
    AbilityData(3795, 0, PointOrUnit, false, 0, false, 0) },
    {4109,  // EFFECT_AMORPHOUSARMORCLOUD
    AbilityData(4109, 0, None, false, 0, false, 0) },
    {4111,  // SHIELDBATTERYRECHARGEEX5_SHIELDBATTERYRECHARGE
    AbilityData(4111, 0, Point, false, 0, false, 12) },
    {4119,  // MORPH_BANELING
    AbilityData(4119, 0, None, false, 0, false, 0) },
    {4122,  // MOTHERSHIPCLOAK_ORACLECLOAKFIELD
    AbilityData(4122, 0, None, false, 0, false, 0) },
}; // clang-format on

} // namespace sc2