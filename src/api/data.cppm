module;
#include <stdint.h>
#include <string>
#include <vector>

#include <s2clientprotocol/data.pb.h>

#include "api/proto_to_pods.h"
#include "lib/gametypes.h"
#include "lib/typeids/5.0.14_typeenums.h"
export module data;
import common;
import protocol_interface;

using std::string, std::to_string, std::vector;

// TODO: Fill out the log functions

export namespace sc2 {

//! Indicates if an ability is available, and if that ability requires a point.
struct AvailableAbility {
    AvailableAbility ( ) = default;

    //! Ability that is available.
    AbilityID ability_id { ABILITY_ID::INVALID };
    //! Indicates if the ability requires a point to invoke.
    bool      requires_point { false };
};

//! Data about an ability.
struct AbilityData {
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
        //! Target can be a point or no target. Only used for addons.
        PointOrNone = 5,
    };

    static string
        TargetToName ( Target target ) {
        switch ( target ) {
            case Target::None        : return "None";
            case Target::Point       : return "Point";
            case Target::Unit        : return "Unit";
            case Target::PointOrUnit : return "PointOrUnit";
            case Target::PointOrNone : return "PointOrNone";
            default                  : return "None";
        }
    }

    //! AbilityData constructor.
    AbilityData ( ) = default;

    /*! Stable ID. For a given ability, this value will be immutable throughout
     * different patches.*/
    AbilityID ability_id { };

    //! Determines if a point, unit, both or none is required as a target.
    Target target { Target::None }; // (3)

    /*!If true, the ability is available to the current mods/map. Also tells
     * whether a value exists or not within the preconstructed database.*/
    bool available { }; // (1)

    //! This ability id may be represented by the given more generic id.
    uint16_t remaps_to_ability_id;

    // Removed parameters to save space.

    // //! Range unit can cast ability without needing to approach target.
    // float          cast_range;
    //
    // //! If the ability is placing a building, give the radius of the
    // footprint. std::float16_t footprint_radius;
    //
    // //! Autocast can be set.
    // bool allow_autocast;
    //
    // //! Requires placement to construct a building.
    // bool is_structure;
    //
    // /*! Placement next to an existing structure, e.g., an add-on like a Tech
    //  * Lab.*/
    // bool is_instant_placement;
    //

    //

    //
    // //! In case the button name is not descriptive.
    // string           friendly_name;
    //


    /* @Worthless_Parameters:

    //! Catalog (game data xml) name of the ability.
    string           link_name;

    //! Catalog (game data xml) index of the ability.
    uint32_t         link_index;

    //! Name of the button for the command card.
    string           button_name;

    //! UI hotkey.
    string           hotkey;

    //! Can be cast in the minimap. (Not implemented)
    bool             allow_minimap;

     */


    //! Serialize this ability entry from the .proto file (used internally).
    //! @param ability_data The proto entry for this ability.
    void
        ReadFromProto ( const SC2APIProtocol::AbilityData& ability_data ) {
        // ability_id_
        if ( ability_data.has_ability_id( ) ) {
            ability_id = ability_data.ability_id( );
        }

        // available_
        available = false;
        if ( ability_data.has_available( ) ) {
            available = ability_data.available( );
        }

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
    string
        Log ( ) const {
        std::string str_out = ability_id.to_string( ) + ":\n";
        str_out            += "  Target: " + TargetToName ( target );
        str_out +=
            std::format ( "  Available: {}\n", available ? "true" : "false" ) +
            ":\n";

        return str_out;
    }
};

using Abilities = vector<AbilityData>;

//! All available abilities for a unit.
struct AvailableAbilities {
    //! The available abilities.
    vector<AvailableAbility> abilities;
    //! The unit.
    Tag                      unit_tag;
    //! The unit type.
    UnitTypeID               unit_type_id;

    //! Returns true if this object refers to a valid unit and unit type.
    //! @return If this object is valid.
    bool
        IsValid ( ) const {
        return unit_tag && unit_type_id;
    }
};

//! Category of unit.
// enum class Attribute : uint8_t {
//     Invalid    = 0,
//     Light      = 1,
//     Armored    = 2,
//     Biological = 3,
//     Mechanical = 4,
//     // Robotic    = 5,
//     Psionic    = 6,
//     Massive    = 7,
//     Structure  = 8,
//     // Hover      = 9,
//     // Heroic     = 10,
//     // Summoned   = 11,
// };

//! Attribute of unit.
// Altered to use bitmask
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

uint8_t
    BitPackAttributes (
        const SC2APIProtocol::Attribute& SC2API_attr, uint8_t bit_mask = 0
    ) {
    switch ( SC2API_attr ) { // clang-format off
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

[[deprecated]]
Attribute
    ConvertAttributeEnum ( SC2APIProtocol::Attribute attribute ) {
    switch ( attribute ) { // clang-format off
        case SC2APIProtocol::Attribute::Light :
            return Attribute::Light;
        case SC2APIProtocol::Attribute::Armored :
            return Attribute::Armored;
        case SC2APIProtocol::Attribute::Biological :
            return Attribute::Biological;
        case SC2APIProtocol::Attribute::Mechanical :
            return Attribute::Mechanical;
        // case SC2APIProtocol::Attribute::Robotic :
        //     return Attribute::Robotic;
        case SC2APIProtocol::Attribute::Psionic :
            return Attribute::Psionic;
        case SC2APIProtocol::Attribute::Massive :
            return Attribute::Massive;
        case SC2APIProtocol::Attribute::Structure :
            return Attribute::Structure;
        case SC2APIProtocol::Attribute::Hover :
            return Attribute::Flying;
        // case SC2APIProtocol::Attribute::Heroic :
        //     return Attribute::Heroic;
        // case SC2APIProtocol::Attribute::Summoned :
        //     return Attribute::Summoned;
        default :
            return Attribute::Invalid;
    } // clang-format on
}

//! Damage bonus of unit.
struct DamageBonus {
    float   bonus { 0.0f };
    uint8_t attribute { };

    DamageBonus ( ) = default;

    void
        ReadFromProto ( const SC2APIProtocol::DamageBonus& damage_bonus ) {
        // attribute_
        attribute = BitPackAttributes ( damage_bonus.attribute( ) );

        // bonus_
        bonus = damage_bonus.bonus( );
    }
};

//! Unit weapon.
struct Weapon {
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

    static TargetType
        ConvertTargetTypeEnum ( SC2APIProtocol::Weapon::TargetType type ) {
        switch ( type ) {
            case SC2APIProtocol::Weapon::Ground : return TargetType::Ground;
            case SC2APIProtocol::Weapon::Air    : return TargetType::Air;
            case SC2APIProtocol::Weapon::Any    : return TargetType::Any;
            default                             : return TargetType::Invalid;
        }
    }

    void
        ReadFromProto ( const SC2APIProtocol::Weapon& weapon ) {
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
struct UnitTypeData {
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
    void
        ReadFromProto ( const SC2APIProtocol::UnitTypeData& unit_data ) {
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
            attributes = ( BitPackAttributes (
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
    string
        Log ( ) const {
        string str_out = unit_type_id.to_string( ) + ":\n";
        str_out       += "  " + ( name.length( ) > 0 ? name : "Null" ) + "\n";

        return str_out;
    }
};

using UnitTypes = vector<UnitTypeData>;

//! Upgrade data.
struct UpgradeData {
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

    void
        ReadFromProto ( const SC2APIProtocol::UpgradeData& upgrade_data ) {
        upgrade_id    = upgrade_data.upgrade_id( );
        name          = upgrade_data.name( );
        mineral_cost  = upgrade_data.mineral_cost( );
        vespene_cost  = upgrade_data.vespene_cost( );
        ability_id    = upgrade_data.ability_id( );
        research_time = upgrade_data.research_time( );
    }

    string
        Log ( ) {
        string str_out;
        // TODO Incomplete
        return str_out;
    }
};

using Upgrades = vector<UpgradeData>;

//! Buff data.
struct BuffData {
    //! Stable ID. This ID will not change between patches.
    uint32_t buff_id { 0 };
    //! Buff name, corresponds to the game's catalog.
    string   name;

    BuffData ( ) = default;

    void
        ReadFromProto ( const SC2APIProtocol::BuffData& buff_data ) {
        // upgrade_id_
        buff_id = buff_data.buff_id( );

        // name_
        name = buff_data.name( );
    }

    string
        Log ( ) {
        string str_out;
        // TODO Incomplete
        return str_out;
    }
};

typedef vector<BuffData> Buffs;

//! Effect data.
struct EffectData {
    //! Stable ID. This ID will not change between patches.
    uint32_t effect_id;
    //! Effect name, corresponds to the game's catalog.
    string   name;
    //! A more recognizable name of the effect.
    string   friendly_name;
    //! Size of the circle the effect impacts.
    float    radius;

    void
        ReadFromProto ( const SC2APIProtocol::EffectData& effect_data ) {
        effect_id     = effect_data.effect_id( );
        name          = effect_data.name( );
        friendly_name = effect_data.friendly_name( );
        radius        = effect_data.radius( );
    }

    string
        Log ( ) const {
        string str_out;
        // TODO Incomplete
        return str_out;
    }
};

using Effects = vector<EffectData>;

//! Power source information for Protoss.
struct PowerSource {
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
struct Effect {
    //! Type of the effect
    uint32_t        effect_id;
    //! All the positions that this effect is impacting on the map.
    //! eg. The Lurker's attack impacts multiple positions in a line.
    vector<Point2D> positions;

    void
        ReadFromProto ( const SC2APIProtocol::Effect& effect ) {
        effect_id = effect.effect_id( );
        for ( int i = 0; i < effect.pos_size( ); ++i ) {
            const SC2APIProtocol::Point2D& pos = effect.pos ( i );
            positions.push_back ( Point2D ( pos.x( ), pos.y( ) ) );
        }
    }
};

} // namespace sc2
