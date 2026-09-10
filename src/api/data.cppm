module;
#include <flat_map>
#include <stdint.h>
#include <string>
#include <vector>

#include <s2clientprotocol/data.pb.h>
#include <s2clientprotocol/raw.pb.h>
export module data;
import protocol_interface;
import point;
import game_types;
import proto_to_pods;
import type_enums;

// TODO: Fill out the log functions

export namespace sc2 {
using namespace std;

//! Indicates if an ability is available, and if that ability requires a point.
struct AvailableAbility
{
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
    PointOrNone = 5,
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
    float     cast_range { 0.0F };
    //! If the ability is placing a building, give the radius of the footprint.
    float     footprint_radius { 0.0F };
    /*! Stable ID. For a given ability, this value will be immutable throughout
     * different patches. */
    AbilityID ability_id;
    //! This ability id may be represented by the given more generic id.
    AbilityID remaps_to_ability_id { 0u };
    //! Determines if a point, unit, both or none is required as a target.
    Target    target { 1u };
    //! Autocast can be set.
    bool      allow_autocast { false };
    //! Requires placement to construct a building.
    bool      is_structure { false };
    /*! Placement next to an existing structure, e.g., an add-on like a Tech
     * Lab. */
    bool      is_instant_placement { false };


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
    //! If true, the ability is available to the current mods/map.
    bool available;
    //! Can be cast in the minimap. (Not implemented)
    bool allow_minimap;


    */

    //! AbilityData constructor.
    AbilityData ( ) = default;

    AbilityData (
        const AbilityID ability_id,
        const Target    target,
        const float     cast_range,
        const float     footprint_radius,
        const bool      allow_autocast,
        const bool      is_structure,
        const bool      is_instant_placement
    )
        : cast_range ( cast_range ),
          footprint_radius ( footprint_radius ),
          ability_id ( ability_id ),
          target ( target ),
          allow_autocast ( allow_autocast ),
          is_structure ( is_structure ),
          is_instant_placement ( is_instant_placement ) { }

    // TODO: Move to ProtoToPots
    /*! @brief Serialize this ability entry from the .proto file (used
     * internally).
     * @param ability_data The proto entry for this ability. */
    void ReadFromProto ( const SC2APIProtocol::AbilityData &ability_data ) {
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
        return to_string ( ability_id ) + ":\n" +
               "  Target: " + TargetToName ( target );
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
//     << '\n'; DB_file_out << "      is_structure: " <<
//     ability_data.is_structure
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
 * @note bitmask */
enum class Attribute : uint8_t {
    Invalid    = 0,
    Light      = 1 << 0, // 1
    Armored    = 1 << 1, // 2
    Biological = 1 << 2, // 4
    Mechanical = 1 << 3, // 8
    Psionic    = 1 << 4, // 16
    Massive    = 1 << 5, // 32
    Structure  = 1 << 6, // 64
    Flying     = 1 << 7, // 128 // formerly Hover
};

uint8_t ConvertAttributeEnum (
    const SC2APIProtocol::Attribute &SC2API_attr,
    uint8_t                          bit_mask = 0
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

    void ReadFromProto ( const SC2APIProtocol::DamageBonus &damage_bonus ) {
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
        const SC2APIProtocol::Weapon::TargetType type
    ) {
        switch ( type ) {
            case SC2APIProtocol::Weapon::Ground : return TargetType::Ground;
            case SC2APIProtocol::Weapon::Air    : return TargetType::Air;
            case SC2APIProtocol::Weapon::Any    : return TargetType::Any;
            default                             : return TargetType::Invalid;
        }
    }

    void ReadFromProto ( const SC2APIProtocol::Weapon &weapon ) {
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
    void ReadFromProto ( const SC2APIProtocol::UnitTypeData &unit_data ) {
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
            attributes = ConvertAttributeEnum (
                unit_data.attributes ( i ),
                attributes
            );
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
        return to_string ( unit_type_id ) + ":\n" + "  " +
               ( !name.empty( ) ? name : "Null" ) + "\n";
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

    void ReadFromProto ( const SC2APIProtocol::UpgradeData &upgrade_data ) {
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

    void ReadFromProto ( const SC2APIProtocol::BuffData &buff_data ) {
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

    void ReadFromProto ( const SC2APIProtocol::EffectData &effect_data ) {
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
    PowerSource (
        const Point2D in_position,
        const float   in_radius,
        const Tag     in_tag
    )
        : position ( in_position ),
          radius ( in_radius ),
          tag ( in_tag ) { }

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

    void ReadFromProto ( const SC2APIProtocol::Effect &effect ) {
        effect_id = effect.effect_id( );
        for ( int i = 0; i < effect.pos_size( ); ++i ) {
            const SC2APIProtocol::Point2D &pos = effect.pos ( i );
            positions.push_back ( Point2D ( pos.x( ), pos.y( ) ) );
        }
    }
};

} // namespace sc2

namespace {

// using sc2::Target::None;
// using sc2::Target::Point;
// using sc2::Target::PointOrNone;
// using sc2::Target::PointOrUnit;
// using sc2::Target::Unit;
using enum sc2::Target;

} // namespace

namespace sc2 {

const AbilityData AbilityDataDB[526]
{
    // clang-format off
AbilityData ( 0 ,   // INVALID
    None , 0.0f , 0.0f , false , false , false ),
AbilityData ( 1 ,   // SMART
    PointOrUnit , 0.0f , 0.0f , false , false , false ),
AbilityData ( 2 ,   // TAUNT
    PointOrUnit , 10.0f , 0.0f , false , false , false ),
AbilityData ( 20 ,   // MOVE_TURN
    PointOrUnit , 0.0f , 0.0f , false , false , false ),
AbilityData ( 24 ,   // ATTACK_ATTACKTOWARDS
    Point , 0.0f , 0.0f , false , false , false ),
AbilityData ( 25 ,   // ATTACK_ATTACKBARRAGE
    Point , 0.0f , 0.0f , false , false , false ),
AbilityData ( 40 ,   // EFFECT_INFESTEDTERRANS
    None , 0.0f , 0.0f , false , false , false ),
AbilityData ( 42 ,   // EFFECT_EXPLODE
    None , 0.0f , 0.0f , false , false , false ),
AbilityData ( 44 ,   // RESEARCH_INTERCEPTORGRAVITONCATAPULT
    None , 0.0f , 0.0f , false , false , false ),
AbilityData ( 45 ,   // RESEARCH_INTERCEPTORLAUNCHSPEEDUPGRADE
    None , 0.0f , 0.0f , false , false , false ),
AbilityData ( 46 ,   // RESEARCH_PHOENIXANIONPULSECRYSTALS
    None , 0.0f , 0.0f , false , false , false ),
AbilityData ( 47 ,   // RESEARCH_TEMPESTRANGEUPGRADE
    None , 0.0f , 0.0f , false , false , false ),
AbilityData ( 48 ,   // RESEARCH_VOIDRAYSPEEDUPGRADE
    None , 0.0f , 0.0f , false , false , false ),
AbilityData ( 49 ,   // RESEARCH_TEMPESTRESEARCHGROUNDATTACKUPGRADE
    None , 0.0f , 0.0f , false , false , false ),
AbilityData ( 74 ,   // EFFECT_FUNGALGROWTH
    Point , 10.0f , 0.0f , false , false , false ),
AbilityData ( 76 ,   // EFFECT_GUARDIANSHIELD
    None , 0.0f , 0.0f , false , false , false ),
AbilityData ( 110 ,   // TRAIN_MOTHERSHIP
    None , 0.0f , 0.0f , false , false , false ),
AbilityData ( 140 ,   // EFFECT_FEEDBACK
    Unit , 10.0f , 0.0f , false , false , false ),
AbilityData ( 146 ,   // HALLUCINATION_ARCHON
    None , 0.0f , 0.0f , false , false , false ),
AbilityData ( 148 ,   // HALLUCINATION_COLOSSUS
    None , 0.0f , 0.0f , false , false , false ),
AbilityData ( 150 ,   // HALLUCINATION_HIGHTEMPLAR
    None , 0.0f , 0.0f , false , false , false ),
AbilityData ( 152 ,   // HALLUCINATION_IMMORTAL
    None , 0.0f , 0.0f , false , false , false ),
AbilityData ( 154 ,   // HALLUCINATION_PHOENIX
    None , 0.0f , 0.0f , false , false , false ),
AbilityData ( 156 ,   // HALLUCINATION_PROBE
    None , 0.0f , 0.0f , false , false , false ),
AbilityData ( 158 ,   // HALLUCINATION_STALKER
    None , 0.0f , 0.0f , false , false , false ),
AbilityData ( 160 ,   // HALLUCINATION_VOIDRAY
    None , 0.0f , 0.0f , false , false , false ),
AbilityData ( 162 ,   // HALLUCINATION_WARPPRISM
    None , 0.0f , 0.0f , false , false , false ),
AbilityData ( 164 ,   // HALLUCINATION_ZEALOT
    None , 0.0f , 0.0f , false , false , false ),
AbilityData ( 171 ,   // EFFECT_CALLDOWNMULE
    PointOrUnit , 500.0f , 0.0f , false , false , false ),
AbilityData ( 173 ,   // EFFECT_GRAVITONBEAM
    Unit , 4.0f , 0.0f , false , false , false ),
AbilityData ( 181 ,   // EFFECT_SPAWNCHANGELING
    None , 0.0f , 0.0f , false , false , false ),
AbilityData ( 216 ,   // RESEARCH_GLIALREGENERATION
    None , 0.0f , 0.0f , false , false , false ),
AbilityData ( 217 ,   // RESEARCH_TUNNELINGCLAWS
    None , 0.0f , 0.0f , false , false , false ),
AbilityData ( 218 ,   // RESEARCH_ROACHSUPPLY
    None , 0.0f , 0.0f , false , false , false ),
AbilityData ( 245 ,   // SAPSTRUCTURE
    Unit , 0.25f , 0.0f , true , false , false ),
AbilityData ( 249 ,   // EFFECT_NEURALPARASITE
    Unit , 8.0f , 0.0f , false , false , false ),
AbilityData ( 251 ,   // EFFECT_INJECTLARVA
    Unit , 0.1001f , 0.0f , false , false , false ),
AbilityData ( 255 ,   // EFFECT_SUPPLYDROP
    Unit , 500.0f , 0.0f , false , false , false ),
AbilityData ( 263 ,   // RESEARCH_ANABOLICSYNTHESIS
    None , 0.0f , 0.0f , false , false , false ),
AbilityData ( 265 ,   // RESEARCH_CHITINOUSPLATING
    None , 0.0f , 0.0f , false , false , false ),
AbilityData ( 301 ,   // ATTACK_ATTACKWARPPRISM
    PointOrUnit , 0.0f , 0.0f , false , false , false ),
AbilityData ( 318 ,   // BUILD_COMMANDCENTER
    Point , 0.0f , 2.5f , false , true , false ),
AbilityData ( 319 ,   // BUILD_SUPPLYDEPOT
    Point , 0.0f , 1.0f , false , true , false ),
AbilityData ( 320 ,   // BUILD_REFINERY
    Unit , 0.0f , 1.5f , false , true , false ),
AbilityData ( 321 ,   // BUILD_BARRACKS
    Point , 0.0f , 1.5f , false , true , false ),
AbilityData ( 322 ,   // BUILD_ENGINEERINGBAY
    Point , 0.0f , 1.5f , false , true , false ),
AbilityData ( 323 ,   // BUILD_MISSILETURRET
    Point , 0.0f , 1.0f , false , true , false ),
AbilityData ( 324 ,   // BUILD_BUNKER
    Point , 0.0f , 1.5f , false , true , false ),
AbilityData ( 326 ,   // BUILD_SENSORTOWER
    Point , 0.0f , 0.5f , false , true , false ),
AbilityData ( 327 ,   // BUILD_GHOSTACADEMY
    Point , 0.0f , 1.5f , false , true , false ),
AbilityData ( 328 ,   // BUILD_FACTORY
    Point , 0.0f , 1.5f , false , true , false ),
AbilityData ( 329 ,   // BUILD_STARPORT
    Point , 0.0f , 1.5f , false , true , false ),
AbilityData ( 331 ,   // BUILD_ARMORY
    Point , 0.0f , 1.5f , false , true , false ),
AbilityData ( 333 ,   // BUILD_FUSIONCORE
    Point , 0.0f , 1.5f , false , true , false ),
AbilityData ( 386 ,   // EFFECT_HEAL
    Unit , 4.0f , 0.0f , true , false , false ),
AbilityData ( 388 ,   // MORPH_SIEGEMODE
    None , 0.0f , 0.0f , false , false , false ),
AbilityData ( 390 ,   // MORPH_UNSIEGE
    None , 0.0f , 0.0f , false , false , false ),
AbilityData ( 399 ,   // EFFECT_SCAN
    Point , 500.0f , 0.0f , false , false , false ),
AbilityData ( 401 ,   // EFFECT_YAMATOGUN
    Unit , 10.0f , 0.0f , false , false , false ),
AbilityData ( 403 ,   // MORPH_VIKINGASSAULTMODE
    None , 0.0f , 0.0f , false , false , false ),
AbilityData ( 405 ,   // MORPH_VIKINGFIGHTERMODE
    None , 0.0f , 0.0f , false , false , false ),
AbilityData ( 524 ,   // TRAIN_SCV
    None , 0.0f , 0.0f , false , false , false ),
AbilityData ( 556 ,   // MORPH_SUPPLYDEPOT_LOWER
    None , 0.0f , 0.0f , false , false , false ),
AbilityData ( 558 ,   // MORPH_SUPPLYDEPOT_RAISE
    None , 0.0f , 0.0f , false , false , false ),
AbilityData ( 560 ,   // TRAIN_MARINE
    None , 0.0f , 0.0f , false , false , false ),
AbilityData ( 561 ,   // TRAIN_REAPER
    None , 0.0f , 0.0f , false , false , false ),
AbilityData ( 562 ,   // TRAIN_GHOST
    None , 0.0f , 0.0f , false , false , false ),
AbilityData ( 563 ,   // TRAIN_MARAUDER
    None , 0.0f , 0.0f , false , false , false ),
AbilityData ( 591 ,   // TRAIN_SIEGETANK
    None , 0.0f , 0.0f , false , false , false ),
AbilityData ( 594 ,   // TRAIN_THOR
    None , 0.0f , 0.0f , false , false , false ),
AbilityData ( 595 ,   // TRAIN_HELLION
    None , 0.0f , 0.0f , false , false , false ),
AbilityData ( 596 ,   // TRAIN_HELLBAT
    None , 0.0f , 0.0f , false , false , false ),
AbilityData ( 597 ,   // TRAIN_CYCLONE
    None , 0.0f , 0.0f , false , false , false ),
AbilityData ( 614 ,   // TRAIN_WIDOWMINE
    None , 0.0f , 0.0f , false , false , false ),
AbilityData ( 620 ,   // TRAIN_MEDIVAC
    None , 0.0f , 0.0f , false , false , false ),
AbilityData ( 621 ,   // TRAIN_BANSHEE
    None , 0.0f , 0.0f , false , false , false ),
AbilityData ( 622 ,   // TRAIN_RAVEN
    None , 0.0f , 0.0f , false , false , false ),
AbilityData ( 623 ,   // TRAIN_BATTLECRUISER
    None , 0.0f , 0.0f , false , false , false ),
AbilityData ( 624 ,   // TRAIN_VIKINGFIGHTER
    None , 0.0f , 0.0f , false , false , false ),
AbilityData ( 626 ,   // TRAIN_LIBERATOR
    None , 0.0f , 0.0f , false , false , false ),
AbilityData ( 650 ,   // RESEARCH_HISECAUTOTRACKING
    None , 0.0f , 0.0f , false , false , false ),
AbilityData ( 651 ,   // RESEARCH_TERRANSTRUCTUREARMORUPGRADE
    None , 0.0f , 0.0f , false , false , false ),
AbilityData ( 655 ,   // RESEARCH_NEOSTEELFRAME
    None , 0.0f , 0.0f , false , false , false ),
AbilityData ( 710 ,   // BUILD_NUKE
    None , 0.0f , 0.0f , false , false , false ),
AbilityData ( 730 ,   // RESEARCH_STIMPACK
    None , 0.0f , 0.0f , false , false , false ),
AbilityData ( 731 ,   // RESEARCH_COMBATSHIELD
    None , 0.0f , 0.0f , false , false , false ),
AbilityData ( 732 ,   // RESEARCH_CONCUSSIVESHELLS
    None , 0.0f , 0.0f , false , false , false ),
AbilityData ( 761 ,   // RESEARCH_INFERNALPREIGNITER
    None , 0.0f , 0.0f , false , false , false ),
AbilityData ( 763 ,   // RESEARCH_TRANSFORMATIONSERVOS
    None , 0.0f , 0.0f , false , false , false ),
AbilityData ( 764 ,   // RESEARCH_DRILLINGCLAWS
    None , 0.0f , 0.0f , false , false , false ),
AbilityData ( 765 ,   // RESEARCH_LOCKONRANGEUPGRADE
    None , 0.0f , 0.0f , false , false , false ),
AbilityData ( 766 ,   // RESEARCH_SMARTSERVOS
    None , 0.0f , 0.0f , false , false , false ),
AbilityData ( 767 ,   // RESEARCH_ARMORPIERCINGROCKETS
    None , 0.0f , 0.0f , false , false , false ),
AbilityData ( 768 ,   // RESEARCH_CYCLONERAPIDFIRELAUNCHERS
    None , 0.0f , 0.0f , false , false , false ),
AbilityData ( 769 ,   // RESEARCH_CYCLONELOCKONDAMAGE
    None , 0.0f , 0.0f , false , false , false ),
AbilityData ( 770 ,   // RESEARCH_CYCLONERESEARCHHURRICANETHRUSTERS
    None , 0.0f , 0.0f , false , false , false ),
AbilityData ( 790 ,   // RESEARCH_BANSHEECLOAKINGFIELD
    None , 0.0f , 0.0f , false , false , false ),
AbilityData ( 792 ,   // RESEARCH_MEDIVACENERGYUPGRADE
    None , 0.0f , 0.0f , false , false , false ),
AbilityData ( 793 ,   // RESEARCH_RAVENCORVIDREACTOR
    None , 0.0f , 0.0f , false , false , false ),
AbilityData ( 796 ,   // RESEARCH_SEEKERMISSILE
    None , 0.0f , 0.0f , false , false , false ),
AbilityData ( 797 ,   // RESEARCH_DURABLEMATERIALS
    None , 0.0f , 0.0f , false , false , false ),
AbilityData ( 799 ,   // RESEARCH_BANSHEEHYPERFLIGHTROTORS
    None , 0.0f , 0.0f , false , false , false ),
AbilityData ( 800 ,   // RESEARCH_LIBERATORAGMODE
    None , 0.0f , 0.0f , false , false , false ),
AbilityData ( 802 ,   // RESEARCH_RAPIDDEPLOYMENT
    None , 0.0f , 0.0f , false , false , false ),
AbilityData ( 803 ,   // RESEARCH_RAVENRECALIBRATEDEXPLOSIVES
    None , 0.0f , 0.0f , false , false , false ),
AbilityData ( 804 ,   // RESEARCH_HIGHCAPACITYFUELTANKS
    None , 0.0f , 0.0f , false , false , false ),
AbilityData ( 805 ,   // RESEARCH_ADVANCEDBALLISTICS
    None , 0.0f , 0.0f , false , false , false ),
AbilityData ( 806 ,   // RESEARCH_ENHANCEDMUNITIONS
    None , 0.0f , 0.0f , false , false , false ),
AbilityData ( 807 ,   // RESEARCH_RAVENINTERFERENCEMATRIX
    None , 0.0f , 0.0f , false , false , false ),
AbilityData ( 820 ,   // RESEARCH_PERSONALCLOAKING
    None , 0.0f , 0.0f , false , false , false ),
AbilityData ( 852 ,   // RESEARCH_TERRANVEHICLEPLATINGLEVEL1
    None , 0.0f , 0.0f , false , false , false ),
AbilityData ( 853 ,   // RESEARCH_TERRANVEHICLEPLATINGLEVEL2
    None , 0.0f , 0.0f , false , false , false ),
AbilityData ( 854 ,   // RESEARCH_TERRANVEHICLEPLATINGLEVEL3
    None , 0.0f , 0.0f , false , false , false ),
AbilityData ( 858 ,   // RESEARCH_TERRANSHIPPLATINGLEVEL1
    None , 0.0f , 0.0f , false , false , false ),
AbilityData ( 859 ,   // RESEARCH_TERRANSHIPPLATINGLEVEL2
    None , 0.0f , 0.0f , false , false , false ),
AbilityData ( 860 ,   // RESEARCH_TERRANSHIPPLATINGLEVEL3
    None , 0.0f , 0.0f , false , false , false ),
AbilityData ( 880 ,   // BUILD_NEXUS
    Point , 0.0f , 2.5f , false , true , false ),
AbilityData ( 881 ,   // BUILD_PYLON
    Point , 0.0f , 1.0f , false , true , false ),
AbilityData ( 882 ,   // BUILD_ASSIMILATOR
    Unit , 0.0f , 1.5f , false , true , false ),
AbilityData ( 883 ,   // BUILD_GATEWAY
    Point , 0.0f , 1.5f , false , true , false ),
AbilityData ( 884 ,   // BUILD_FORGE
    Point , 0.0f , 1.5f , false , true , false ),
AbilityData ( 885 ,   // BUILD_FLEETBEACON
    Point , 0.0f , 1.5f , false , true , false ),
AbilityData ( 886 ,   // BUILD_TWILIGHTCOUNCIL
    Point , 0.0f , 1.5f , false , true , false ),
AbilityData ( 887 ,   // BUILD_PHOTONCANNON
    Point , 0.0f , 1.0f , false , true , false ),
AbilityData ( 889 ,   // BUILD_STARGATE
    Point , 0.0f , 1.5f , false , true , false ),
AbilityData ( 890 ,   // BUILD_TEMPLARARCHIVE
    Point , 0.0f , 1.5f , false , true , false ),
AbilityData ( 891 ,   // BUILD_DARKSHRINE
    Point , 0.0f , 1.0f , false , true , false ),
AbilityData ( 892 ,   // BUILD_ROBOTICSBAY
    Point , 0.0f , 1.5f , false , true , false ),
AbilityData ( 893 ,   // BUILD_ROBOTICSFACILITY
    Point , 0.0f , 1.5f , false , true , false ),
AbilityData ( 894 ,   // BUILD_CYBERNETICSCORE
    Point , 0.0f , 1.5f , false , true , false ),
AbilityData ( 895 ,   // BUILD_SHIELDBATTERY
    Point , 0.0f , 1.0f , false , true , false ),
AbilityData ( 916 ,   // TRAIN_ZEALOT
    None , 0.0f , 0.0f , false , false , false ),
AbilityData ( 917 ,   // TRAIN_STALKER
    None , 0.0f , 0.0f , false , false , false ),
AbilityData ( 919 ,   // TRAIN_HIGHTEMPLAR
    None , 0.0f , 0.0f , false , false , false ),
AbilityData ( 920 ,   // TRAIN_DARKTEMPLAR
    None , 0.0f , 0.0f , false , false , false ),
AbilityData ( 921 ,   // TRAIN_SENTRY
    None , 0.0f , 0.0f , false , false , false ),
AbilityData ( 922 ,   // TRAIN_ADEPT
    None , 0.0f , 0.0f , false , false , false ),
AbilityData ( 946 ,   // TRAIN_PHOENIX
    None , 0.0f , 0.0f , false , false , false ),
AbilityData ( 948 ,   // TRAIN_CARRIER
    None , 0.0f , 0.0f , false , false , false ),
AbilityData ( 950 ,   // TRAIN_VOIDRAY
    None , 0.0f , 0.0f , false , false , false ),
AbilityData ( 954 ,   // TRAIN_ORACLE
    None , 0.0f , 0.0f , false , false , false ),
AbilityData ( 955 ,   // TRAIN_TEMPEST
    None , 0.0f , 0.0f , false , false , false ),
AbilityData ( 976 ,   // TRAIN_WARPPRISM
    None , 0.0f , 0.0f , false , false , false ),
AbilityData ( 977 ,   // TRAIN_OBSERVER
    None , 0.0f , 0.0f , false , false , false ),
AbilityData ( 978 ,   // TRAIN_COLOSSUS
    None , 0.0f , 0.0f , false , false , false ),
AbilityData ( 979 ,   // TRAIN_IMMORTAL
    None , 0.0f , 0.0f , false , false , false ),
AbilityData ( 994 ,   // TRAIN_DISRUPTOR
    None , 0.0f , 0.0f , false , false , false ),
AbilityData ( 1006 ,   // TRAIN_PROBE
    None , 0.0f , 0.0f , false , false , false ),
AbilityData ( 1036 ,   // EFFECT_PSISTORM
    Point , 8.0f , 0.0f , false , false , false ),
AbilityData ( 1042 ,   // BUILD_INTERCEPTORS
    None , 0.0f , 0.0f , true , false , false ),
AbilityData ( 1093 ,   // RESEARCH_GRAVITICBOOSTER
    None , 0.0f , 0.0f , false , false , false ),
AbilityData ( 1094 ,   // RESEARCH_GRAVITICDRIVE
    None , 0.0f , 0.0f , false , false , false ),
AbilityData ( 1097 ,   // RESEARCH_EXTENDEDTHERMALLANCE
    None , 0.0f , 0.0f , false , false , false ),
AbilityData ( 1099 ,   // RESEARCH_IMMORTALREVIVE
    None , 0.0f , 0.0f , false , false , false ),
AbilityData ( 1126 ,   // RESEARCH_PSISTORM
    None , 0.0f , 0.0f , false , false , false ),
AbilityData ( 1152 ,   // BUILD_HATCHERY
    Point , 0.0f , 2.5f , false , true , false ),
AbilityData ( 1153 ,   // BUILD_CREEPTUMOR
    Point , 0.0f , 0.5f , false , true , false ),
AbilityData ( 1154 ,   // BUILD_EXTRACTOR
    Unit , 0.0f , 1.5f , false , true , false ),
AbilityData ( 1155 ,   // BUILD_SPAWNINGPOOL
    Point , 0.0f , 1.5f , false , true , false ),
AbilityData ( 1156 ,   // BUILD_EVOLUTIONCHAMBER
    Point , 0.0f , 1.5f , false , true , false ),
AbilityData ( 1157 ,   // BUILD_HYDRALISKDEN
    Point , 0.0f , 1.5f , false , true , false ),
AbilityData ( 1158 ,   // BUILD_SPIRE
    Point , 0.0f , 1.0f , false , true , false ),
AbilityData ( 1159 ,   // BUILD_ULTRALISKCAVERN
    Point , 0.0f , 1.5f , false , true , false ),
AbilityData ( 1160 ,   // BUILD_INFESTATIONPIT
    Point , 0.0f , 1.5f , false , true , false ),
AbilityData ( 1161 ,   // BUILD_NYDUSNETWORK
    Point , 0.0f , 1.5f , false , true , false ),
AbilityData ( 1162 ,   // BUILD_BANELINGNEST
    Point , 0.0f , 1.5f , false , true , false ),
AbilityData ( 1163 ,   // BUILD_LURKERDEN
    Point , 0.0f , 1.5f , false , true , false ),
AbilityData ( 1165 ,   // BUILD_ROACHWARREN
    Point , 0.0f , 1.5f , false , true , false ),
AbilityData ( 1166 ,   // BUILD_SPINECRAWLER
    Point , 0.0f , 1.0f , false , true , false ),
AbilityData ( 1167 ,   // BUILD_SPORECRAWLER
    Point , 0.0f , 1.0f , false , true , false ),
AbilityData ( 1195 ,   // EVOLUTIONCHAMBERRESEARCH_EVOLVEPROPULSIVEPERISTALSIS
    None , 0.0f , 0.0f , false , false , false ),
AbilityData ( 1216 ,   // MORPH_LAIR
    None , 0.0f , 0.0f , false , false , false ),
AbilityData ( 1218 ,   // MORPH_HIVE
    None , 0.0f , 0.0f , false , false , false ),
AbilityData ( 1220 ,   // MORPH_GREATERSPIRE
    None , 0.0f , 0.0f , false , false , false ),
AbilityData ( 1223 ,   // RESEARCH_PNEUMATIZEDCARAPACE
    None , 0.0f , 0.0f , false , false , false ),
AbilityData ( 1224 ,   // RESEARCH_EVOLVEVENTRALSACKS
    None , 0.0f , 0.0f , false , false , false ),
AbilityData ( 1225 ,   // RESEARCH_BURROW
    None , 0.0f , 0.0f , false , false , false ),
AbilityData ( 1252 ,   // RESEARCH_ZERGLINGADRENALGLANDS
    None , 0.0f , 0.0f , false , false , false ),
AbilityData ( 1253 ,   // RESEARCH_ZERGLINGMETABOLICBOOST
    None , 0.0f , 0.0f , false , false , false ),
AbilityData ( 1282 ,   // RESEARCH_GROOVEDSPINES
    None , 0.0f , 0.0f , false , false , false ),
AbilityData ( 1283 ,   // RESEARCH_MUSCULARAUGMENTS
    None , 0.0f , 0.0f , false , false , false ),
AbilityData ( 1286 ,   // RESEARCH_LURKERRANGE
    None , 0.0f , 0.0f , false , false , false ),
AbilityData ( 1342 ,   // TRAIN_DRONE
    None , 0.0f , 0.0f , false , false , false ),
AbilityData ( 1343 ,   // TRAIN_ZERGLING
    None , 0.0f , 0.0f , false , false , false ),
AbilityData ( 1344 ,   // TRAIN_OVERLORD
    None , 0.0f , 0.0f , false , false , false ),
AbilityData ( 1345 ,   // TRAIN_HYDRALISK
    None , 0.0f , 0.0f , false , false , false ),
AbilityData ( 1346 ,   // TRAIN_MUTALISK
    None , 0.0f , 0.0f , false , false , false ),
AbilityData ( 1348 ,   // TRAIN_ULTRALISK
    None , 0.0f , 0.0f , false , false , false ),
AbilityData ( 1351 ,   // TRAIN_ROACH
    None , 0.0f , 0.0f , false , false , false ),
AbilityData ( 1352 ,   // TRAIN_INFESTOR
    None , 0.0f , 0.0f , false , false , false ),
AbilityData ( 1353 ,   // TRAIN_CORRUPTOR
    None , 0.0f , 0.0f , false , false , false ),
AbilityData ( 1354 ,   // TRAIN_VIPER
    None , 0.0f , 0.0f , false , false , false ),
AbilityData ( 1356 ,   // TRAIN_SWARMHOST
    None , 0.0f , 0.0f , false , false , false ),
AbilityData ( 1372 ,   // MORPH_BROODLORD
    None , 0.0f , 0.0f , false , false , false ),
AbilityData ( 1413 ,   // TRAINWARP_ZEALOT
    Point , 0.0f , 0.0f , false , false , false ),
AbilityData ( 1414 ,   // TRAINWARP_STALKER
    Point , 0.0f , 0.0f , false , false , false ),
AbilityData ( 1416 ,   // TRAINWARP_HIGHTEMPLAR
    Point , 0.0f , 0.0f , false , false , false ),
AbilityData ( 1417 ,   // TRAINWARP_DARKTEMPLAR
    Point , 0.0f , 0.0f , false , false , false ),
AbilityData ( 1418 ,   // TRAINWARP_SENTRY
    Point , 0.0f , 0.0f , false , false , false ),
AbilityData ( 1419 ,   // TRAINWARP_ADEPT
    Point , 0.0f , 0.0f , false , false , false ),
AbilityData ( 1448 ,   // MORPH_OVERSEER
    None , 0.0f , 0.0f , false , false , false ),
AbilityData ( 1450 ,   // MORPH_PLANETARYFORTRESS
    None , 0.0f , 0.0f , false , false , false ),
AbilityData ( 1455 ,   // RESEARCH_NEURALPARASITE
    None , 0.0f , 0.0f , false , false , false ),
AbilityData ( 1456 ,   // RESEARCH_LOCUSTLIFETIMEINCREASE
    None , 0.0f , 0.0f , false , false , false ),
AbilityData ( 1457 ,   // RESEARCH_EVOLVEAMORPHOUSARMORCLOUD
    None , 0.0f , 0.0f , false , false , false ),
AbilityData ( 1482 ,   // RESEARCH_CENTRIFUGALHOOKS
    None , 0.0f , 0.0f , false , false , false ),
AbilityData ( 1516 ,   // MORPH_ORBITALCOMMAND
    None , 0.0f , 0.0f , false , false , false ),
AbilityData ( 1518 ,   // MORPH_WARPGATE
    None , 0.0f , 0.0f , false , false , false ),
AbilityData ( 1520 ,   // MORPH_GATEWAY
    None , 0.0f , 0.0f , false , false , false ),
AbilityData ( 1526 ,   // EFFECT_FORCEFIELD
    Point , 9.0f , 0.0f , false , false , false ),
AbilityData ( 1528 ,   // MORPH_WARPPRISMPHASINGMODE
    None , 0.0f , 0.0f , false , false , false ),
AbilityData ( 1530 ,   // MORPH_WARPPRISMTRANSPORTMODE
    None , 0.0f , 0.0f , false , false , false ),
AbilityData ( 1532 ,   // RESEARCH_BATTLECRUISERWEAPONREFIT
    None , 0.0f , 0.0f , false , false , false ),
AbilityData ( 1533 ,   // RESEARCH_BALLISTICRANGE
    None , 0.0f , 0.0f , false , false , false ),
AbilityData ( 1534 ,   // RESEARCH_RAPIDREIGNITIONSYSTEM
    None , 0.0f , 0.0f , false , false , false ),
AbilityData ( 1568 ,   // RESEARCH_WARPGATE
    None , 0.0f , 0.0f , false , false , false ),
AbilityData ( 1571 ,   // RESEARCH_HALLUCINATION
    None , 0.0f , 0.0f , false , false , false ),
AbilityData ( 1592 ,   // RESEARCH_CHARGE
    None , 0.0f , 0.0f , false , false , false ),
AbilityData ( 1593 ,   // RESEARCH_BLINK
    None , 0.0f , 0.0f , false , false , false ),
AbilityData ( 1594 ,   // RESEARCH_ADEPTRESONATINGGLAIVES
    None , 0.0f , 0.0f , false , false , false ),
AbilityData ( 1595 ,   // RESEARCH_PSIONICSURGE
    None , 0.0f , 0.0f , false , false , false ),
AbilityData ( 1596 ,   // RESEARCH_AMPLIFIEDSHIELDING
    None , 0.0f , 0.0f , false , false , false ),
AbilityData ( 1597 ,   // RESEARCH_PSIONICAMPLIFIERS
    None , 0.0f , 0.0f , false , false , false ),
AbilityData ( 1622 ,   // EFFECT_NUKECALLDOWN
    Point , 12.0f , 0.0f , false , false , false ),
AbilityData ( 1628 ,   // EFFECT_EMP
    Point , 10.0f , 0.0f , false , false , false ),
AbilityData ( 1632 ,   // TRAIN_QUEEN
    None , 0.0f , 0.0f , false , false , false ),
AbilityData ( 1664 ,   // EFFECT_TRANSFUSION
    Unit , 7.0f , 0.0f , false , false , false ),
AbilityData ( 1668 ,   // BARRACKSTECHLABMORPH_TECHLABBARRACKS
    None , 0.0f , 0.0f , false , false , false ),
AbilityData ( 1670 ,   // FACTORYTECHLABMORPH_TECHLABFACTORY
    None , 0.0f , 0.0f , false , false , false ),
AbilityData ( 1672 ,   // STARPORTTECHLABMORPH_TECHLABSTARPORT
    None , 0.0f , 0.0f , false , false , false ),
AbilityData ( 1676 ,   // BARRACKSREACTORMORPH_REACTOR
    None , 0.0f , 0.0f , false , false , false ),
AbilityData ( 1678 ,   // FACTORYREACTORMORPH_REACTOR
    None , 0.0f , 0.0f , false , false , false ),
AbilityData ( 1680 ,   // STARPORTREACTORMORPH_REACTOR
    None , 0.0f , 0.0f , false , false , false ),
AbilityData ( 1692 ,   // BEHAVIOR_GENERATECREEPON
    None , 0.0f , 0.0f , false , false , false ),
AbilityData ( 1693 ,   // BEHAVIOR_GENERATECREEPOFF
    None , 0.0f , 0.0f , false , false , false ),
AbilityData ( 1766 ,   // MORPH_ARCHON
    None , 0.0f , 0.0f , false , false , false ),
AbilityData ( 1767 ,   // ARCHONWARP_ARCHONWARPTARGET
    Unit , 0.0f , 0.0f , false , false , false ),
AbilityData ( 1768 ,   // BUILD_NYDUSWORM
    Point , 0.0f , 1.5f , false , true , false ),
AbilityData ( 1769 ,   // BUILDNYDUSCANAL_SUMMONNYDUSCANALATTACKER
    Point , 0.0f , 1.0f , false , true , false ),
AbilityData ( 1819 ,   // EFFECT_CHARGE
    Unit , 0.0f , 0.0f , true , false , false ),
AbilityData ( 1821 ,   // HERDINTERACT_HERD
    Unit , 10.0f , 0.0f , true , false , false ),
AbilityData ( 1825 ,   // EFFECT_CONTAMINATE
    Unit , 3.0f , 0.0f , false , false , false ),
AbilityData ( 1839 ,   // DIGESTERCREEPSPRAY
    Point , 500.0f , 0.0f , false , false , false ),
AbilityData ( 1847 ,   // MORPH_MOTHERSHIP
    None , 0.0f , 0.0f , false , false , false ),
AbilityData ( 1928 ,   // XELNAGAHEALINGSHRINE
    None , 0.0f , 0.0f , true , false , false ),
AbilityData ( 1930 ,   // NEXUSINVULNERABILITY
    Unit , 10.0f , 0.0f , false , false , false ),
AbilityData ( 1978 ,   // MORPH_HELLION
    None , 0.0f , 0.0f , false , false , false ),
AbilityData ( 1998 ,   // MORPH_HELLBAT
    None , 0.0f , 0.0f , false , false , false ),
AbilityData ( 2058 ,   // STOPPROTOSSBUILDING_HOLDFIRE
    None , 0.0f , 0.0f , false , false , false ),
AbilityData ( 2059 ,   // STOPPROTOSSBUILDING_CHEER
    None , 0.0f , 0.0f , false , false , false ),
AbilityData ( 2060 ,   // STOPPROTOSSBUILDING_DANCE
    None , 0.0f , 0.0f , false , false , false ),
AbilityData ( 2063 ,   // EFFECT_BLINDINGCLOUD
    Point , 10.0f , 0.0f , false , false , false ),
AbilityData ( 2067 ,   // EFFECT_ABDUCT
    Unit , 9.0f , 0.0f , false , false , false ),
AbilityData ( 2081 ,   // BEHAVIOR_BUILDINGATTACKON
    None , 0.0f , 0.0f , false , false , false ),
AbilityData ( 2082 ,   // BEHAVIOR_BUILDINGATTACKOFF
    None , 0.0f , 0.0f , false , false , false ),
AbilityData ( 2083 ,   // PICKUPSCRAPSMALL
    Unit , 1.0f , 0.0f , true , false , false ),
AbilityData ( 2085 ,   // PICKUPSCRAPMEDIUM
    Unit , 1.0f , 0.0f , true , false , false ),
AbilityData ( 2087 ,   // PICKUPSCRAPLARGE
    Unit , 1.0f , 0.0f , true , false , false ),
AbilityData ( 2089 ,   // PICKUPPALLETGAS
    Unit , 1.0f , 0.0f , true , false , false ),
AbilityData ( 2091 ,   // PICKUPPALLETMINERALS
    Unit , 1.0f , 0.0f , true , false , false ),
AbilityData ( 2093 ,   // MASSIVEKNOCKOVER
    Unit , 1.0f , 0.0f , true , false , false ),
AbilityData ( 2099 ,   // EFFECT_WIDOWMINEATTACK
    Unit , 5.0f , 0.0f , true , false , false ),
AbilityData ( 2101 ,   // TORNADOMISSILE
    Unit , 0.0f , 0.0f , true , false , false ),
AbilityData ( 2114 ,   // HALLUCINATION_ORACLE
    None , 0.0f , 0.0f , false , false , false ),
AbilityData ( 2116 ,   // EFFECT_MEDIVACIGNITEAFTERBURNERS
    None , 0.0f , 0.0f , false , false , false ),
AbilityData ( 2118 ,   // EXTENDINGBRIDGENEWIDE8OUT_BRIDGEEXTEND
    None , 0.0f , 0.0f , false , false , false ),
AbilityData ( 2120 ,   // EXTENDINGBRIDGENEWIDE8_BRIDGERETRACT
    None , 0.0f , 0.0f , false , false , false ),
AbilityData ( 2122 ,   // EXTENDINGBRIDGENWWIDE8OUT_BRIDGEEXTEND
    None , 0.0f , 0.0f , false , false , false ),
AbilityData ( 2124 ,   // EXTENDINGBRIDGENWWIDE8_BRIDGERETRACT
    None , 0.0f , 0.0f , false , false , false ),
AbilityData ( 2126 ,   // EXTENDINGBRIDGENEWIDE10OUT_BRIDGEEXTEND
    None , 0.0f , 0.0f , false , false , false ),
AbilityData ( 2128 ,   // EXTENDINGBRIDGENEWIDE10_BRIDGERETRACT
    None , 0.0f , 0.0f , false , false , false ),
AbilityData ( 2130 ,   // EXTENDINGBRIDGENWWIDE10OUT_BRIDGEEXTEND
    None , 0.0f , 0.0f , false , false , false ),
AbilityData ( 2132 ,   // EXTENDINGBRIDGENWWIDE10_BRIDGERETRACT
    None , 0.0f , 0.0f , false , false , false ),
AbilityData ( 2134 ,   // EXTENDINGBRIDGENEWIDE12OUT_BRIDGEEXTEND
    None , 0.0f , 0.0f , false , false , false ),
AbilityData ( 2136 ,   // EXTENDINGBRIDGENEWIDE12_BRIDGERETRACT
    None , 0.0f , 0.0f , false , false , false ),
AbilityData ( 2138 ,   // EXTENDINGBRIDGENWWIDE12OUT_BRIDGEEXTEND
    None , 0.0f , 0.0f , false , false , false ),
AbilityData ( 2140 ,   // EXTENDINGBRIDGENWWIDE12_BRIDGERETRACT
    None , 0.0f , 0.0f , false , false , false ),
AbilityData ( 2144 ,   // CRITTERFLEE
    Point , 5.0f , 0.0f , true , false , false ),
AbilityData ( 2146 ,   // EFFECT_ORACLEREVELATION
    Point , 12.0f , 0.0f , false , false , false ),
AbilityData ( 2158 ,   // ULTRALISKWEAPONCOOLDOWN
    None , 0.0f , 0.0f , false , false , false ),
AbilityData ( 2162 ,   // EFFECT_PHOTONOVERCHARGE
    Unit , 10.0f , 0.0f , false , false , false ),
AbilityData ( 2164 ,   // XELNAGA_CAVERNS_DOORE_XELNAGA_CAVERNS_DOORDEFAULTCLOSE
    None , 0.0f , 0.0f , false , false , false ),
AbilityData ( 2166 ,   // XELNAGA_CAVERNS_DOOREOPENED_XELNAGA_CAVERNS_DOORDEFAULTCLOSE
    None , 0.0f , 0.0f , false , false , false ),
AbilityData ( 2168 ,   // XELNAGA_CAVERNS_DOORN_XELNAGA_CAVERNS_DOORDEFAULTCLOSE
    None , 0.0f , 0.0f , false , false , false ),
AbilityData ( 2170 ,   // XELNAGA_CAVERNS_DOORNE_XELNAGA_CAVERNS_DOORDEFAULTCLOSE
    None , 0.0f , 0.0f , false , false , false ),
AbilityData ( 2172 ,   // XELNAGA_CAVERNS_DOORNEOPENED_XELNAGA_CAVERNS_DOORDEFAULTOPEN
    None , 0.0f , 0.0f , false , false , false ),
AbilityData ( 2174 ,   // XELNAGA_CAVERNS_DOORNOPENED_XELNAGA_CAVERNS_DOORDEFAULTOPEN
    None , 0.0f , 0.0f , false , false , false ),
AbilityData ( 2176 ,   // XELNAGA_CAVERNS_DOORNW_XELNAGA_CAVERNS_DOORDEFAULTCLOSE
    None , 0.0f , 0.0f , false , false , false ),
AbilityData ( 2178 ,   // XELNAGA_CAVERNS_DOORNWOPENED_XELNAGA_CAVERNS_DOORDEFAULTOPEN
    None , 0.0f , 0.0f , false , false , false ),
AbilityData ( 2180 ,   // XELNAGA_CAVERNS_DOORS_XELNAGA_CAVERNS_DOORDEFAULTCLOSE
    None , 0.0f , 0.0f , false , false , false ),
AbilityData ( 2182 ,   // XELNAGA_CAVERNS_DOORSE_XELNAGA_CAVERNS_DOORDEFAULTCLOSE
    None , 0.0f , 0.0f , false , false , false ),
AbilityData ( 2184 ,   // XELNAGA_CAVERNS_DOORSEOPENED_XELNAGA_CAVERNS_DOORDEFAULTOPEN
    None , 0.0f , 0.0f , false , false , false ),
AbilityData ( 2186 ,   // XELNAGA_CAVERNS_DOORSOPENED_XELNAGA_CAVERNS_DOORDEFAULTOPEN
    None , 0.0f , 0.0f , false , false , false ),
AbilityData ( 2188 ,   // XELNAGA_CAVERNS_DOORSW_XELNAGA_CAVERNS_DOORDEFAULTCLOSE
    None , 0.0f , 0.0f , false , false , false ),
AbilityData ( 2190 ,   // XELNAGA_CAVERNS_DOORSWOPENED_XELNAGA_CAVERNS_DOORDEFAULTOPEN
    None , 0.0f , 0.0f , false , false , false ),
AbilityData ( 2192 ,   // XELNAGA_CAVERNS_DOORW_XELNAGA_CAVERNS_DOORDEFAULTCLOSE
    None , 0.0f , 0.0f , false , false , false ),
AbilityData ( 2194 ,   // XELNAGA_CAVERNS_DOORWOPENED_XELNAGA_CAVERNS_DOORDEFAULTOPEN
    None , 0.0f , 0.0f , false , false , false ),
AbilityData ( 2196 ,   // XELNAGA_CAVERNS_FLOATING_BRIDGENE8OUT_BRIDGEEXTEND
    None , 0.0f , 0.0f , false , false , false ),
AbilityData ( 2198 ,   // XELNAGA_CAVERNS_FLOATING_BRIDGENE8_BRIDGERETRACT
    None , 0.0f , 0.0f , false , false , false ),
AbilityData ( 2200 ,   // XELNAGA_CAVERNS_FLOATING_BRIDGENW8OUT_BRIDGEEXTEND
    None , 0.0f , 0.0f , false , false , false ),
AbilityData ( 2202 ,   // XELNAGA_CAVERNS_FLOATING_BRIDGENW8_BRIDGERETRACT
    None , 0.0f , 0.0f , false , false , false ),
AbilityData ( 2204 ,   // XELNAGA_CAVERNS_FLOATING_BRIDGENE10OUT_BRIDGEEXTEND
    None , 0.0f , 0.0f , false , false , false ),
AbilityData ( 2206 ,   // XELNAGA_CAVERNS_FLOATING_BRIDGENE10_BRIDGERETRACT
    None , 0.0f , 0.0f , false , false , false ),
AbilityData ( 2208 ,   // XELNAGA_CAVERNS_FLOATING_BRIDGENW10OUT_BRIDGEEXTEND
    None , 0.0f , 0.0f , false , false , false ),
AbilityData ( 2210 ,   // XELNAGA_CAVERNS_FLOATING_BRIDGENW10_BRIDGERETRACT
    None , 0.0f , 0.0f , false , false , false ),
AbilityData ( 2212 ,   // XELNAGA_CAVERNS_FLOATING_BRIDGENE12OUT_BRIDGEEXTEND
    None , 0.0f , 0.0f , false , false , false ),
AbilityData ( 2214 ,   // XELNAGA_CAVERNS_FLOATING_BRIDGENE12_BRIDGERETRACT
    None , 0.0f , 0.0f , false , false , false ),
AbilityData ( 2216 ,   // XELNAGA_CAVERNS_FLOATING_BRIDGENW12OUT_BRIDGEEXTEND
    None , 0.0f , 0.0f , false , false , false ),
AbilityData ( 2218 ,   // XELNAGA_CAVERNS_FLOATING_BRIDGENW12_BRIDGERETRACT
    None , 0.0f , 0.0f , false , false , false ),
AbilityData ( 2220 ,   // XELNAGA_CAVERNS_FLOATING_BRIDGEH8OUT_BRIDGEEXTEND
    None , 0.0f , 0.0f , false , false , false ),
AbilityData ( 2222 ,   // XELNAGA_CAVERNS_FLOATING_BRIDGEH8_BRIDGERETRACT
    None , 0.0f , 0.0f , false , false , false ),
AbilityData ( 2224 ,   // XELNAGA_CAVERNS_FLOATING_BRIDGEV8OUT_BRIDGEEXTEND
    None , 0.0f , 0.0f , false , false , false ),
AbilityData ( 2226 ,   // XELNAGA_CAVERNS_FLOATING_BRIDGEV8_BRIDGERETRACT
    None , 0.0f , 0.0f , false , false , false ),
AbilityData ( 2228 ,   // XELNAGA_CAVERNS_FLOATING_BRIDGEH10OUT_BRIDGEEXTEND
    None , 0.0f , 0.0f , false , false , false ),
AbilityData ( 2230 ,   // XELNAGA_CAVERNS_FLOATING_BRIDGEH10_BRIDGERETRACT
    None , 0.0f , 0.0f , false , false , false ),
AbilityData ( 2232 ,   // XELNAGA_CAVERNS_FLOATING_BRIDGEV10OUT_BRIDGEEXTEND
    None , 0.0f , 0.0f , false , false , false ),
AbilityData ( 2234 ,   // XELNAGA_CAVERNS_FLOATING_BRIDGEV10_BRIDGERETRACT
    None , 0.0f , 0.0f , false , false , false ),
AbilityData ( 2236 ,   // XELNAGA_CAVERNS_FLOATING_BRIDGEH12OUT_BRIDGEEXTEND
    None , 0.0f , 0.0f , false , false , false ),
AbilityData ( 2238 ,   // XELNAGA_CAVERNS_FLOATING_BRIDGEH12_BRIDGERETRACT
    None , 0.0f , 0.0f , false , false , false ),
AbilityData ( 2240 ,   // XELNAGA_CAVERNS_FLOATING_BRIDGEV12OUT_BRIDGEEXTEND
    None , 0.0f , 0.0f , false , false , false ),
AbilityData ( 2242 ,   // XELNAGA_CAVERNS_FLOATING_BRIDGEV12_BRIDGERETRACT
    None , 0.0f , 0.0f , false , false , false ),
AbilityData ( 2244 ,   // EFFECT_TIMEWARP
    Point , 9.0f , 0.0f , false , false , false ),
AbilityData ( 2246 ,   // SNOWREFINERY_TERRAN_EXTENDINGBRIDGENESHORT8OUT_BRIDGEEXTEND
    None , 0.0f , 0.0f , false , false , false ),
AbilityData ( 2248 ,   // SNOWREFINERY_TERRAN_EXTENDINGBRIDGENESHORT8_BRIDGERETRACT
    None , 0.0f , 0.0f , false , false , false ),
AbilityData ( 2250 ,   // SNOWREFINERY_TERRAN_EXTENDINGBRIDGENWSHORT8OUT_BRIDGEEXTEND
    None , 0.0f , 0.0f , false , false , false ),
AbilityData ( 2252 ,   // SNOWREFINERY_TERRAN_EXTENDINGBRIDGENWSHORT8_BRIDGERETRACT
    None , 0.0f , 0.0f , false , false , false ),
AbilityData ( 2324 ,   // EFFECT_CAUSTICSPRAY
    Unit , 6.0f , 0.0f , false , false , false ),
AbilityData ( 2330 ,   // MORPH_RAVAGER
    None , 0.0f , 0.0f , false , false , false ),
AbilityData ( 2332 ,   // MORPH_LURKER
    None , 0.0f , 0.0f , false , false , false ),
AbilityData ( 2338 ,   // EFFECT_CORROSIVEBILE
    Point , 9.0f , 0.0f , false , false , false ),
AbilityData ( 2344 ,   // PURIFICATIONNOVA
    None , 0.0f , 0.0f , false , false , false ),
AbilityData ( 2346 ,   // EFFECT_PURIFICATIONNOVA
    Point , 500.0f , 0.0f , false , false , false ),
AbilityData ( 2350 ,   // EFFECT_LOCKON
    Unit , 7.0f , 0.0f , true , false , false ),
AbilityData ( 2358 ,   // EFFECT_TACTICALJUMP
    Point , 500.0f , 0.0f , false , false , false ),
AbilityData ( 2362 ,   // MORPH_THORHIGHIMPACTMODE
    None , 0.0f , 0.0f , false , false , false ),
AbilityData ( 2364 ,   // MORPH_THOREXPLOSIVEMODE
    None , 0.0f , 0.0f , false , false , false ),
AbilityData ( 2375 ,   // BEHAVIOR_PULSARBEAMON
    None , 0.0f , 0.0f , false , false , false ),
AbilityData ( 2376 ,   // BEHAVIOR_PULSARBEAMOFF
    None , 0.0f , 0.0f , false , false , false ),
AbilityData ( 2383 ,   // LOCUSTMPFLYINGMORPHTOGROUND_LOCUSTMPFLYINGSWOOP
    None , 0.0f , 0.0f , false , false , false ),
AbilityData ( 2385 ,   // LOCUSTMPMORPHTOAIR_LOCUSTMPFLYINGSWOOP
    None , 0.0f , 0.0f , false , false , false ),
AbilityData ( 2387 ,   // EFFECT_LOCUSTSWOOP
    Point , 6.0f , 0.0f , false , false , false ),
AbilityData ( 2389 ,   // HALLUCINATION_DISRUPTOR
    None , 0.0f , 0.0f , false , false , false ),
AbilityData ( 2391 ,   // HALLUCINATION_ADEPT
    None , 0.0f , 0.0f , false , false , false ),
AbilityData ( 2393 ,   // EFFECT_VOIDRAYPRISMATICALIGNMENT
    None , 0.0f , 0.0f , false , false , false ),
AbilityData ( 2397 ,   // AIURLIGHTBRIDGENE8OUT_BRIDGEEXTEND
    None , 0.0f , 0.0f , false , false , false ),
AbilityData ( 2399 ,   // AIURLIGHTBRIDGENE8_BRIDGERETRACT
    None , 0.0f , 0.0f , false , false , false ),
AbilityData ( 2401 ,   // AIURLIGHTBRIDGENE10OUT_BRIDGEEXTEND
    None , 0.0f , 0.0f , false , false , false ),
AbilityData ( 2403 ,   // AIURLIGHTBRIDGENE10_BRIDGERETRACT
    None , 0.0f , 0.0f , false , false , false ),
AbilityData ( 2405 ,   // AIURLIGHTBRIDGENE12OUT_BRIDGEEXTEND
    None , 0.0f , 0.0f , false , false , false ),
AbilityData ( 2407 ,   // AIURLIGHTBRIDGENE12_BRIDGERETRACT
    None , 0.0f , 0.0f , false , false , false ),
AbilityData ( 2409 ,   // AIURLIGHTBRIDGENW8OUT_BRIDGEEXTEND
    None , 0.0f , 0.0f , false , false , false ),
AbilityData ( 2411 ,   // AIURLIGHTBRIDGENW8_BRIDGERETRACT
    None , 0.0f , 0.0f , false , false , false ),
AbilityData ( 2413 ,   // AIURLIGHTBRIDGENW10OUT_BRIDGEEXTEND
    None , 0.0f , 0.0f , false , false , false ),
AbilityData ( 2415 ,   // AIURLIGHTBRIDGENW10_BRIDGERETRACT
    None , 0.0f , 0.0f , false , false , false ),
AbilityData ( 2417 ,   // AIURLIGHTBRIDGENW12OUT_BRIDGEEXTEND
    None , 0.0f , 0.0f , false , false , false ),
AbilityData ( 2419 ,   // AIURLIGHTBRIDGENW12_BRIDGERETRACT
    None , 0.0f , 0.0f , false , false , false ),
AbilityData ( 2445 ,   // SHAKURASLIGHTBRIDGENE8OUT_BRIDGEEXTEND
    None , 0.0f , 0.0f , false , false , false ),
AbilityData ( 2447 ,   // SHAKURASLIGHTBRIDGENE8_BRIDGERETRACT
    None , 0.0f , 0.0f , false , false , false ),
AbilityData ( 2449 ,   // SHAKURASLIGHTBRIDGENE10OUT_BRIDGEEXTEND
    None , 0.0f , 0.0f , false , false , false ),
AbilityData ( 2451 ,   // SHAKURASLIGHTBRIDGENE10_BRIDGERETRACT
    None , 0.0f , 0.0f , false , false , false ),
AbilityData ( 2453 ,   // SHAKURASLIGHTBRIDGENE12OUT_BRIDGEEXTEND
    None , 0.0f , 0.0f , false , false , false ),
AbilityData ( 2455 ,   // SHAKURASLIGHTBRIDGENE12_BRIDGERETRACT
    None , 0.0f , 0.0f , false , false , false ),
AbilityData ( 2457 ,   // SHAKURASLIGHTBRIDGENW8OUT_BRIDGEEXTEND
    None , 0.0f , 0.0f , false , false , false ),
AbilityData ( 2459 ,   // SHAKURASLIGHTBRIDGENW8_BRIDGERETRACT
    None , 0.0f , 0.0f , false , false , false ),
AbilityData ( 2461 ,   // SHAKURASLIGHTBRIDGENW10OUT_BRIDGEEXTEND
    None , 0.0f , 0.0f , false , false , false ),
AbilityData ( 2463 ,   // SHAKURASLIGHTBRIDGENW10_BRIDGERETRACT
    None , 0.0f , 0.0f , false , false , false ),
AbilityData ( 2465 ,   // SHAKURASLIGHTBRIDGENW12OUT_BRIDGEEXTEND
    None , 0.0f , 0.0f , false , false , false ),
AbilityData ( 2467 ,   // SHAKURASLIGHTBRIDGENW12_BRIDGERETRACT
    None , 0.0f , 0.0f , false , false , false ),
AbilityData ( 2469 ,   // VOIDMPIMMORTALREVIVEREBUILD_IMMORTAL
    None , 0.0f , 0.0f , false , false , false ),
AbilityData ( 2473 ,   // ARBITERMPSTASISFIELD
    PointOrUnit , 9.0f , 0.0f , false , false , false ),
AbilityData ( 2475 ,   // ARBITERMPRECALL
    Point , 500.0f , 0.0f , false , false , false ),
AbilityData ( 2477 ,   // CORSAIRMPDISRUPTIONWEB
    Point , 9.0f , 0.0f , false , false , false ),
AbilityData ( 2479 ,   // MORPH_MORPHTOGUARDIANMP
    None , 0.0f , 0.0f , false , false , false ),
AbilityData ( 2481 ,   // MORPH_MORPHTODEVOURERMP
    None , 0.0f , 0.0f , false , false , false ),
AbilityData ( 2483 ,   // DEFILERMPCONSUME
    Unit , 0.5f , 0.0f , false , false , false ),
AbilityData ( 2485 ,   // DEFILERMPDARKSWARM
    Point , 8.0f , 0.0f , false , false , false ),
AbilityData ( 2487 ,   // DEFILERMPPLAGUE
    Point , 8.0f , 0.0f , false , false , false ),
AbilityData ( 2493 ,   // QUEENMPENSNARE
    Point , 9.0f , 0.0f , false , false , false ),
AbilityData ( 2495 ,   // QUEENMPSPAWNBROODLINGS
    Unit , 9.0f , 0.0f , false , false , false ),
AbilityData ( 2497 ,   // QUEENMPINFESTCOMMANDCENTER
    None , 1.0f , 0.0f , false , false , false ),
AbilityData ( 2505 ,   // BUILD_STASISTRAP
    Point , 0.0f , 0.5f , false , true , false ),
AbilityData ( 2536 ,   // ORACLESTASISTRAPACTIVATE_ACTIVATESTASISWARD
    None , 0.0f , 0.0f , true , false , false ),
AbilityData ( 2542 ,   // EFFECT_PARASITICBOMB
    Unit , 8.0f , 0.0f , false , false , false ),
AbilityData ( 2544 ,   // EFFECT_ADEPTPHASESHIFT
    Point , 500.0f , 0.0f , false , false , false ),
AbilityData ( 2548 ,   // PURIFICATIONNOVAMORPHBACK_PURIFICATIONNOVA
    None , 0.0f , 0.0f , false , false , false ),
AbilityData ( 2554 ,   // LIBERATORMORPHTOAG_LIBERATORAGMODE
    None , 0.0f , 0.0f , false , false , false ),
AbilityData ( 2556 ,   // LIBERATORMORPHTOAA_LIBERATORAAMODE
    None , 0.0f , 0.0f , false , false , false ),
AbilityData ( 2558 ,   // MORPH_LIBERATORAGMODE
    Point , 5.0f , 0.0f , false , false , false ),
AbilityData ( 2560 ,   // MORPH_LIBERATORAAMODE
    None , 0.0f , 0.0f , false , false , false ),
AbilityData ( 2564 ,   // AIURLIGHTBRIDGEABANDONEDNE8OUT_BRIDGEEXTEND
    None , 0.0f , 0.0f , false , false , false ),
AbilityData ( 2566 ,   // AIURLIGHTBRIDGEABANDONEDNE8_BRIDGERETRACT
    None , 0.0f , 0.0f , false , false , false ),
AbilityData ( 2568 ,   // AIURLIGHTBRIDGEABANDONEDNE10OUT_BRIDGEEXTEND
    None , 0.0f , 0.0f , false , false , false ),
AbilityData ( 2570 ,   // AIURLIGHTBRIDGEABANDONEDNE10_BRIDGERETRACT
    None , 0.0f , 0.0f , false , false , false ),
AbilityData ( 2572 ,   // AIURLIGHTBRIDGEABANDONEDNE12OUT_BRIDGEEXTEND
    None , 0.0f , 0.0f , false , false , false ),
AbilityData ( 2574 ,   // AIURLIGHTBRIDGEABANDONEDNE12_BRIDGERETRACT
    None , 0.0f , 0.0f , false , false , false ),
AbilityData ( 2576 ,   // AIURLIGHTBRIDGEABANDONEDNW8OUT_BRIDGEEXTEND
    None , 0.0f , 0.0f , false , false , false ),
AbilityData ( 2578 ,   // AIURLIGHTBRIDGEABANDONEDNW8_BRIDGERETRACT
    None , 0.0f , 0.0f , false , false , false ),
AbilityData ( 2580 ,   // AIURLIGHTBRIDGEABANDONEDNW10OUT_BRIDGEEXTEND
    None , 0.0f , 0.0f , false , false , false ),
AbilityData ( 2582 ,   // AIURLIGHTBRIDGEABANDONEDNW10_BRIDGERETRACT
    None , 0.0f , 0.0f , false , false , false ),
AbilityData ( 2584 ,   // AIURLIGHTBRIDGEABANDONEDNW12OUT_BRIDGEEXTEND
    None , 0.0f , 0.0f , false , false , false ),
AbilityData ( 2586 ,   // AIURLIGHTBRIDGEABANDONEDNW12_BRIDGERETRACT
    None , 0.0f , 0.0f , false , false , false ),
AbilityData ( 2588 ,   // EFFECT_KD8CHARGE
    Point , 5.0f , 0.0f , false , false , false ),
AbilityData ( 2598 ,   // SLAYNELEMENTALGRAB
    Unit , 10.0f , 0.0f , false , false , false ),
AbilityData ( 2602 ,   // PORTCITY_BRIDGE_UNITNE8OUT_BRIDGEEXTEND
    None , 0.0f , 0.0f , false , false , false ),
AbilityData ( 2604 ,   // PORTCITY_BRIDGE_UNITNE8_BRIDGERETRACT
    None , 0.0f , 0.0f , false , false , false ),
AbilityData ( 2606 ,   // PORTCITY_BRIDGE_UNITSE8OUT_BRIDGEEXTEND
    None , 0.0f , 0.0f , false , false , false ),
AbilityData ( 2608 ,   // PORTCITY_BRIDGE_UNITSE8_BRIDGERETRACT
    None , 0.0f , 0.0f , false , false , false ),
AbilityData ( 2610 ,   // PORTCITY_BRIDGE_UNITNW8OUT_BRIDGEEXTEND
    None , 0.0f , 0.0f , false , false , false ),
AbilityData ( 2612 ,   // PORTCITY_BRIDGE_UNITNW8_BRIDGERETRACT
    None , 0.0f , 0.0f , false , false , false ),
AbilityData ( 2614 ,   // PORTCITY_BRIDGE_UNITSW8OUT_BRIDGEEXTEND
    None , 0.0f , 0.0f , false , false , false ),
AbilityData ( 2616 ,   // PORTCITY_BRIDGE_UNITSW8_BRIDGERETRACT
    None , 0.0f , 0.0f , false , false , false ),
AbilityData ( 2618 ,   // PORTCITY_BRIDGE_UNITNE10OUT_BRIDGEEXTEND
    None , 0.0f , 0.0f , false , false , false ),
AbilityData ( 2620 ,   // PORTCITY_BRIDGE_UNITNE10_BRIDGERETRACT
    None , 0.0f , 0.0f , false , false , false ),
AbilityData ( 2622 ,   // PORTCITY_BRIDGE_UNITSE10OUT_BRIDGEEXTEND
    None , 0.0f , 0.0f , false , false , false ),
AbilityData ( 2624 ,   // PORTCITY_BRIDGE_UNITSE10_BRIDGERETRACT
    None , 0.0f , 0.0f , false , false , false ),
AbilityData ( 2626 ,   // PORTCITY_BRIDGE_UNITNW10OUT_BRIDGEEXTEND
    None , 0.0f , 0.0f , false , false , false ),
AbilityData ( 2628 ,   // PORTCITY_BRIDGE_UNITNW10_BRIDGERETRACT
    None , 0.0f , 0.0f , false , false , false ),
AbilityData ( 2630 ,   // PORTCITY_BRIDGE_UNITSW10OUT_BRIDGEEXTEND
    None , 0.0f , 0.0f , false , false , false ),
AbilityData ( 2632 ,   // PORTCITY_BRIDGE_UNITSW10_BRIDGERETRACT
    None , 0.0f , 0.0f , false , false , false ),
AbilityData ( 2634 ,   // PORTCITY_BRIDGE_UNITNE12OUT_BRIDGEEXTEND
    None , 0.0f , 0.0f , false , false , false ),
AbilityData ( 2636 ,   // PORTCITY_BRIDGE_UNITNE12_BRIDGERETRACT
    None , 0.0f , 0.0f , false , false , false ),
AbilityData ( 2638 ,   // PORTCITY_BRIDGE_UNITSE12OUT_BRIDGEEXTEND
    None , 0.0f , 0.0f , false , false , false ),
AbilityData ( 2640 ,   // PORTCITY_BRIDGE_UNITSE12_BRIDGERETRACT
    None , 0.0f , 0.0f , false , false , false ),
AbilityData ( 2642 ,   // PORTCITY_BRIDGE_UNITNW12OUT_BRIDGEEXTEND
    None , 0.0f , 0.0f , false , false , false ),
AbilityData ( 2644 ,   // PORTCITY_BRIDGE_UNITNW12_BRIDGERETRACT
    None , 0.0f , 0.0f , false , false , false ),
AbilityData ( 2646 ,   // PORTCITY_BRIDGE_UNITSW12OUT_BRIDGEEXTEND
    None , 0.0f , 0.0f , false , false , false ),
AbilityData ( 2648 ,   // PORTCITY_BRIDGE_UNITSW12_BRIDGERETRACT
    None , 0.0f , 0.0f , false , false , false ),
AbilityData ( 2650 ,   // PORTCITY_BRIDGE_UNITN8OUT_BRIDGEEXTEND
    None , 0.0f , 0.0f , false , false , false ),
AbilityData ( 2652 ,   // PORTCITY_BRIDGE_UNITN8_BRIDGERETRACT
    None , 0.0f , 0.0f , false , false , false ),
AbilityData ( 2654 ,   // PORTCITY_BRIDGE_UNITS8OUT_BRIDGEEXTEND
    None , 0.0f , 0.0f , false , false , false ),
AbilityData ( 2656 ,   // PORTCITY_BRIDGE_UNITS8_BRIDGERETRACT
    None , 0.0f , 0.0f , false , false , false ),
AbilityData ( 2658 ,   // PORTCITY_BRIDGE_UNITE8OUT_BRIDGEEXTEND
    None , 0.0f , 0.0f , false , false , false ),
AbilityData ( 2660 ,   // PORTCITY_BRIDGE_UNITE8_BRIDGERETRACT
    None , 0.0f , 0.0f , false , false , false ),
AbilityData ( 2662 ,   // PORTCITY_BRIDGE_UNITW8OUT_BRIDGEEXTEND
    None , 0.0f , 0.0f , false , false , false ),
AbilityData ( 2664 ,   // PORTCITY_BRIDGE_UNITW8_BRIDGERETRACT
    None , 0.0f , 0.0f , false , false , false ),
AbilityData ( 2666 ,   // PORTCITY_BRIDGE_UNITN10OUT_BRIDGEEXTEND
    None , 0.0f , 0.0f , false , false , false ),
AbilityData ( 2668 ,   // PORTCITY_BRIDGE_UNITN10_BRIDGERETRACT
    None , 0.0f , 0.0f , false , false , false ),
AbilityData ( 2670 ,   // PORTCITY_BRIDGE_UNITS10OUT_BRIDGEEXTEND
    None , 0.0f , 0.0f , false , false , false ),
AbilityData ( 2672 ,   // PORTCITY_BRIDGE_UNITS10_BRIDGERETRACT
    None , 0.0f , 0.0f , false , false , false ),
AbilityData ( 2674 ,   // PORTCITY_BRIDGE_UNITE10OUT_BRIDGEEXTEND
    None , 0.0f , 0.0f , false , false , false ),
AbilityData ( 2676 ,   // PORTCITY_BRIDGE_UNITE10_BRIDGERETRACT
    None , 0.0f , 0.0f , false , false , false ),
AbilityData ( 2678 ,   // PORTCITY_BRIDGE_UNITW10OUT_BRIDGEEXTEND
    None , 0.0f , 0.0f , false , false , false ),
AbilityData ( 2680 ,   // PORTCITY_BRIDGE_UNITW10_BRIDGERETRACT
    None , 0.0f , 0.0f , false , false , false ),
AbilityData ( 2682 ,   // PORTCITY_BRIDGE_UNITN12OUT_BRIDGEEXTEND
    None , 0.0f , 0.0f , false , false , false ),
AbilityData ( 2684 ,   // PORTCITY_BRIDGE_UNITN12_BRIDGERETRACT
    None , 0.0f , 0.0f , false , false , false ),
AbilityData ( 2686 ,   // PORTCITY_BRIDGE_UNITS12OUT_BRIDGEEXTEND
    None , 0.0f , 0.0f , false , false , false ),
AbilityData ( 2688 ,   // PORTCITY_BRIDGE_UNITS12_BRIDGERETRACT
    None , 0.0f , 0.0f , false , false , false ),
AbilityData ( 2690 ,   // PORTCITY_BRIDGE_UNITE12OUT_BRIDGEEXTEND
    None , 0.0f , 0.0f , false , false , false ),
AbilityData ( 2692 ,   // PORTCITY_BRIDGE_UNITE12_BRIDGERETRACT
    None , 0.0f , 0.0f , false , false , false ),
AbilityData ( 2694 ,   // PORTCITY_BRIDGE_UNITW12OUT_BRIDGEEXTEND
    None , 0.0f , 0.0f , false , false , false ),
AbilityData ( 2696 ,   // PORTCITY_BRIDGE_UNITW12_BRIDGERETRACT
    None , 0.0f , 0.0f , false , false , false ),
AbilityData ( 2704 ,   // EFFECT_SPAWNLOCUSTS
    Point , 500.0f , 0.0f , false , false , false ),
AbilityData ( 2706 ,   // LOCUSTMPFLYINGSWOOPATTACK_LOCUSTMPFLYINGSWOOP
    PointOrUnit , 6.0f , 0.0f , false , false , false ),
AbilityData ( 2708 ,   // MORPH_OVERLORDTRANSPORT
    None , 0.0f , 0.0f , false , false , false ),
AbilityData ( 2714 ,   // EFFECT_GHOSTSNIPE
    Unit , 10.0f , 0.0f , false , false , false ),
AbilityData ( 2716 ,   // PURIFYMORPHPYLON_MOTHERSHIPCOREWEAPON
    None , 0.0f , 0.0f , false , false , false ),
AbilityData ( 2718 ,   // PURIFYMORPHPYLONBACK_MOTHERSHIPCOREWEAPON
    None , 0.0f , 0.0f , false , false , false ),
AbilityData ( 2720 ,   // RESEARCH_SHADOWSTRIKE
    None , 0.0f , 0.0f , false , false , false ),
AbilityData ( 3659 ,   // CANCEL
    None , 0.0f , 0.0f , false , false , false ),
AbilityData ( 3660 ,   // HALT
    None , 0.0f , 0.0f , false , false , false ),
AbilityData ( 3661 ,   // BURROWDOWN
    None , 0.0f , 0.0f , false , false , false ),
AbilityData ( 3662 ,   // BURROWUP
    None , 0.0f , 0.0f , true , false , false ),
AbilityData ( 3663 ,   // LOADALL
    None , 0.0f , 0.0f , false , false , false ),
AbilityData ( 3664 ,   // UNLOADALL
    None , 0.0f , 0.0f , false , false , false ),
AbilityData ( 3665 ,   // STOP
    None , 0.0f , 0.0f , false , false , false ),
AbilityData ( 3666 ,   // HARVEST_GATHER
    Unit , 0.0f , 0.0f , false , false , false ),
AbilityData ( 3667 ,   // HARVEST_RETURN
    None , 0.0f , 0.0f , false , false , false ),
AbilityData ( 3668 ,   // LOAD
    Unit , 0.0f , 0.0f , false , false , false ),
AbilityData ( 3669 ,   // UNLOADALLAT
    PointOrUnit , 0.0f , 0.0f , false , false , false ),
AbilityData ( 3670 ,   // UNLOADUNIT
    None , 0.0f , 0.0f , false , false , false ),
AbilityData ( 3671 ,   // CANCEL_LAST
    None , 0.0f , 0.0f , false , false , false ),
AbilityData ( 3672 ,   // CANCEL_SLOT
    None , 0.0f , 0.0f , false , false , false ),
AbilityData ( 3673 ,   // RALLY_UNITS
    PointOrUnit , 0.0f , 0.0f , false , false , false ),
AbilityData ( 3674 ,   // ATTACK
    PointOrUnit , 0.0f , 0.0f , false , false , false ),
AbilityData ( 3675 ,   // EFFECT_STIM
    None , 0.0f , 0.0f , false , false , false ),
AbilityData ( 3676 ,   // BEHAVIOR_CLOAKON
    None , 0.0f , 0.0f , false , false , false ),
AbilityData ( 3677 ,   // BEHAVIOR_CLOAKOFF
    None , 0.0f , 0.0f , false , false , false ),
AbilityData ( 3678 ,   // LAND
    Point , 0.0f , 0.0f , false , false , false ),
AbilityData ( 3679 ,   // LIFT
    None , 0.0f , 0.0f , false , false , false ),
AbilityData ( 3680 ,   // MORPH_ROOT
    Point , 0.0f , 0.0f , false , false , false ),
AbilityData ( 3681 ,   // MORPH_UPROOT
    None , 0.0f , 0.0f , false , false , false ),
AbilityData ( 3682 ,   // BUILD_TECHLAB
    PointOrNone , 0.0f , 3.5f , false , true , true ),
AbilityData ( 3683 ,   // BUILD_REACTOR
    PointOrNone , 0.0f , 3.5f , false , true , true ),
AbilityData ( 3684 ,   // EFFECT_SPRAY
    Point , 1.0f , 0.0f , false , false , false ),
AbilityData ( 3685 ,   // EFFECT_REPAIR
    Unit , 6.0f , 0.0f , true , false , false ),
AbilityData ( 3686 ,   // EFFECT_MASSRECALL
    Point , 500.0f , 0.0f , false , false , false ),
AbilityData ( 3687 ,   // EFFECT_BLINK
    Point , 500.0f , 0.0f , false , false , false ),
AbilityData ( 3688 ,   // BEHAVIOR_HOLDFIREON
    None , 0.0f , 0.0f , false , false , false ),
AbilityData ( 3689 ,   // BEHAVIOR_HOLDFIREOFF
    None , 0.0f , 0.0f , false , false , false ),
AbilityData ( 3690 ,   // RALLY_WORKERS
    PointOrUnit , 0.0f , 0.0f , false , false , false ),
AbilityData ( 3692 ,   // RESEARCH_PROTOSSAIRARMOR
    None , 0.0f , 0.0f , false , false , false ),
AbilityData ( 3693 ,   // RESEARCH_PROTOSSAIRWEAPONS
    None , 0.0f , 0.0f , false , false , false ),
AbilityData ( 3694 ,   // RESEARCH_PROTOSSGROUNDARMOR
    None , 0.0f , 0.0f , false , false , false ),
AbilityData ( 3695 ,   // RESEARCH_PROTOSSGROUNDWEAPONS
    None , 0.0f , 0.0f , false , false , false ),
AbilityData ( 3696 ,   // RESEARCH_PROTOSSSHIELDS
    None , 0.0f , 0.0f , false , false , false ),
AbilityData ( 3697 ,   // RESEARCH_TERRANINFANTRYARMOR
    None , 0.0f , 0.0f , false , false , false ),
AbilityData ( 3698 ,   // RESEARCH_TERRANINFANTRYWEAPONS
    None , 0.0f , 0.0f , false , false , false ),
AbilityData ( 3699 ,   // RESEARCH_TERRANSHIPWEAPONS
    None , 0.0f , 0.0f , false , false , false ),
AbilityData ( 3700 ,   // RESEARCH_TERRANVEHICLEANDSHIPPLATING
    None , 0.0f , 0.0f , false , false , false ),
AbilityData ( 3701 ,   // RESEARCH_TERRANVEHICLEWEAPONS
    None , 0.0f , 0.0f , false , false , false ),
AbilityData ( 3702 ,   // RESEARCH_ZERGFLYERARMOR
    None , 0.0f , 0.0f , false , false , false ),
AbilityData ( 3703 ,   // RESEARCH_ZERGFLYERATTACK
    None , 0.0f , 0.0f , false , false , false ),
AbilityData ( 3704 ,   // RESEARCH_ZERGGROUNDARMOR
    None , 0.0f , 0.0f , false , false , false ),
AbilityData ( 3705 ,   // RESEARCH_ZERGMELEEWEAPONS
    None , 0.0f , 0.0f , false , false , false ),
AbilityData ( 3706 ,   // RESEARCH_ZERGMISSILEWEAPONS
    None , 0.0f , 0.0f , false , false , false ),
AbilityData ( 3709 ,   // RESEARCH_ADAPTIVETALONS
    None , 0.0f , 0.0f , false , false , false ),
AbilityData ( 3739 ,   // MORPH_OBSERVERMODE
    None , 0.0f , 0.0f , false , false , false ),
AbilityData ( 3741 ,   // MORPH_SURVEILLANCEMODE
    None , 0.0f , 0.0f , false , false , false ),
AbilityData ( 3743 ,   // MORPH_OVERSIGHTMODE
    None , 0.0f , 0.0f , false , false , false ),
AbilityData ( 3745 ,   // MORPH_OVERSEERMODE
    None , 0.0f , 0.0f , false , false , false ),
AbilityData ( 3747 ,   // EFFECT_INTERFERENCEMATRIX
    Unit , 9.0f , 0.0f , false , false , false ),
AbilityData ( 3753 ,   // EFFECT_ANTIARMORMISSILE
    Unit , 10.0f , 0.0f , false , false , false ),
AbilityData ( 3755 ,   // EFFECT_CHRONOBOOSTENERGYCOST
    Unit , 500.0f , 0.0f , false , false , false ),
AbilityData ( 3763 ,   // INFESTORENSNARE
    Unit , 8.0f , 0.0f , false , false , false ),
AbilityData ( 3779 ,   // BATTLECRUISERMOVE_ACQUIREMOVE
    PointOrUnit , 0.0f , 0.0f , false , false , false ),
AbilityData ( 3780 ,   // BATTLECRUISERMOVE_TURN
    PointOrUnit , 0.0f , 0.0f , false , false , false ),
AbilityData ( 3784 ,   // BATTLECRUISERSTOP_HOLDFIRE
    None , 0.0f , 0.0f , false , false , false ),
AbilityData ( 3785 ,   // BATTLECRUISERSTOP_CHEER
    None , 0.0f , 0.0f , false , false , false ),
AbilityData ( 3786 ,   // BATTLECRUISERSTOP_DANCE
    None , 0.0f , 0.0f , false , false , false ),
AbilityData ( 3793 ,   // GENERAL_HOLDPOSITION
    None , 0.0f , 0.0f , false , false , false ),
AbilityData ( 3794 ,   // GENERAL_MOVE
    PointOrUnit , 0.0f , 0.0f , false , false , false ),
AbilityData ( 3795 ,   // GENERAL_PATROL
    PointOrUnit , 0.0f , 0.0f , false , false , false ),
AbilityData ( 4109 ,   // EFFECT_AMORPHOUSARMORCLOUD
    None , 0.0f , 0.0f , false , false , false ),
AbilityData ( 4111 ,   // SHIELDBATTERYRECHARGEEX5_SHIELDBATTERYRECHARGE
    Point , 12.0f , 0.0f , false , false , false ),
AbilityData ( 4119 ,   // MORPH_BANELING
    None , 0.0f , 0.0f , false , false , false ),
AbilityData ( 4122 ,   // MOTHERSHIPCLOAK_ORACLECLOAKFIELD
    None , 0.0f , 0.0f , false , false , false ),
}; // clang-format on

} // namespace sc2
