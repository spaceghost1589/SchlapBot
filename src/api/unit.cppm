module;
#include <algorithm>
#include <functional>
#include <ranges>
#include <stdint.h>
#include <unordered_map>
#include <unordered_set>
#include <vector>
export module unit;
import common;
import type_enums;
import error_handler;
import game_types;


export namespace sc2 {
using namespace std;

//! An order that is active on a unit.
struct UnitOrder
{
    //! Ability ID that triggered the order.
    AbilityID ability_id      = ABILITY_ID::INVALID;
    //! Target unit of the order, if there is one.
    Tag       target_unit_tag = NullTag;
    //! Target position of the order, if there is one.
    Point2D   target_pos;
    //! Progress of the order.
    float     progress = 0.0f;
};

//! A passenger on a transport.
struct PassengerUnit
{
    //! The tag of the unit in the transport.
    Tag        tag        = NullTag;
    //! The health of the unit in the transport.
    float      health     = 0.0f;
    //! The max possible health of the unit in the transport.
    float      health_max = 0.0f;
    //! The shield of the unit in the transport.
    float      shield     = 0.0f;
    //! The max possible shield of the unit in the transport.
    float      shield_max = 0.0f;
    //! The energy of the unit in the transport.
    float      energy     = 0.0f;
    //! The max possible energy of the unit in the transport.
    float      energy_max = 0.0f;
    //! The type of unit in the transport.
    UnitTypeID unit_type  = UNIT_TYPEID::INVALID;
};

//! A unit. Could be a structure, a worker or a military unit.
class Unit {
public:
    //! If the unit is shown on screen or not.
    enum DisplayType : uint8_t {
        //! Unit will be visible.
        Visible     = 1,
        /*! Unit is represented by a snapshot in the fog-of-war. This is for
         * units that don't belong to the player. The actual unit may be in a
         * different location or state. */
        Snapshot    = 2,
        //! Unit will be hidden to enemies.
        Hidden      = 3,
        //! Building that hasn't started construction.
        Placeholder = 4,
    };

    //! Relationship to this player.
    enum Alliance : uint8_t {
        //! Belongs to the player.
        Self    = 1,
        //! Ally of the player.
        Ally    = 2,
        //! A neutral unit, usually a non-player unit like a mineral field.
        Neutral = 3,
        //! Enemy of the player.
        Enemy   = 4
    };

    //! Unit cloak state.
    enum CloakState : uint8_t {
        //! Under the fog, so unknown whether it's cloaked or not.
        CloakedUnknown  = 0,
        //! Cloaked enemy units, invisible until detected.
        Cloaked         = 1,
        //! Cloaked enemy, but detected.
        CloakedDetected = 2,
        //! No cloaking.
        NotCloaked      = 3,
        //! Cloaked ally unit.
        CloakedAllied   = 4,
    };

    //! A unique identifier for the instance of a unit.
    Tag tag;

    //! If the unit is shown on screen or not.
    DisplayType display_type;
    //! Relationship of the unit to this player.
    Alliance    alliance;


    //! An identifier of the type of unit.
    UnitTypeID unit_type;
    //! Which player owns a unit.
    int        owner;

    //! Position of the unit in the world.
    Point3D pos;
    //! Direction the unit faces in radians (1 radian == 57.296 degrees)
    float   facing;
    //! Radius of the unit.
    float   radius;
    //! Gives progress under construction. Range: [0.0, 1.0]. 1.0 == finished.
    float   build_progress;

    //! If the unit is cloaked.
    CloakState cloak;

    //! Range of detector for detector units.
    float detect_range;
    //! Range of radar for units that are radar units.
    float radar_range;

    //! If the unit is in the current selection of the player.
    bool is_selected;
    //! Visible and within the camera frustum.
    bool is_on_screen;
    //! Detected by sensor tower.
    bool is_blip;

    // Not populated for snapshots

    //! Health of the unit. Not set for snapshots.
    float health;
    //! Max health for the unit. Not set for snapshots.
    float health_max;
    //! Shield of the unit. Not set for snapshots.
    float shield;
    //! Max shield of the unit. Not set for snapshots.
    float shield_max;
    //! Energy of the unit. Not set for snapshots.
    float energy;
    //! Max energy of the unit. Not set for snapshots.
    float energy_max;
    //! Amount of minerals if the unit is a mineral field. Not set for
    //! snapshots.
    int   mineral_contents;
    //! Amount of vespene if the unit is a geyser. Not set for snapshots.
    int   vespene_contents;
    //! If the unit is flying. Not set for snapshots.
    bool  is_flying;
    //! If the unit is burrowed. Not set for snapshots.
    bool  is_burrowed;
    //! If the unit is hallucination. Not set for snapshots.
    bool  is_hallucination;
    //! Time remaining for a weapon on cooldown. Not set for snapshots.
    float weapon_cooldown;

    // Not populated for enemies/snapshots

    //! Orders on a unit. Only valid for this player's units.
    vector<UnitOrder>     orders;
    //! Add-on like a tech lab or reactor. Only valid for this player's units.
    Tag                   add_on_tag;
    //! Passengers in this transport. Only valid for this player's units.
    vector<PassengerUnit> passengers;
    //! Number of cargo slots used in the transport. Only valid for this
    //! player's units.
    int                   cargo_space_taken;
    //! Number of cargo slots available for a transport. Only valid for this
    //! player's units.
    int                   cargo_space_max;
    //! Number of harvesters associated with a town hall (e.g., Command Center).
    //! Only valid for this player's units.
    int                   assigned_harvesters;
    //! Number of harvesters that can be assigned to a town hall (e.g., Command
    //! Center) or a geyser (e.g., Refinery). Only valid for this player's
    //! units.
    int                   ideal_harvesters;
    //! Target unit of a unit. Only valid for this player's units.
    Tag                   engaged_target_tag;
    //! Buffs on this unit. Only valid for this player's units.
    vector<BuffID>        buffs;
    //! Whether the unit is powered by a pylon.
    bool                  is_powered;

    //! Whether the unit is alive or not.
    bool     is_alive;
    //! The last time the unit was seen.
    uint32_t last_seen_game_loop;

    //! Level of weapon upgrades.
    int8_t attack_upgrade_level;

    //! Level of armor upgrades.
    int8_t armor_upgrade_level;

    //! Level of shield upgrades.
    int8_t shield_upgrade_level;

    //! Whether the unit is building or not.
    bool is_structure;

    //! Whether the unit construction/training completed.
    [[nodiscard]]
    bool IsBuildFinished ( ) const {
        return build_progress >= 1.0f;
    }

    // ReSharper disable once CppNonExplicitConversionOperator
    operator const Point2D&( ) const {
        return pos;
    }

    // ReSharper disable once CppNonExplicitConversionOperator
    operator const Point3D&( ) const {
        return pos;
    }

    operator const Tag&( ) const{
        return tag;
    }

}; // class Unit

using Units      = vector<const Unit*>;
using Tags       = vector<Tag>;
using UnitIdxMap = unordered_map<Tag, size_t>;

[[deprecated]]
Tags ConvertToTags ( const Units& units ) {
    Tags tags;
    ranges::transform ( units, back_inserter ( tags ), [] ( const Unit* unit ) {
        return unit->tag;
    } );
    return tags;
}

struct UnitDamage
{
    const Unit* unit;
    float       health;
    float       shields;
};

using UnitsDamaged = vector<UnitDamage>;

class UnitPool {
public:
    Unit* CreateUnit ( const Tag tag ) {
        if ( Unit* existing = GetUnit ( tag ) ) {
            tag_to_existing_unit_[tag] = existing;
            return existing;
        }

        if ( unit_pool_.empty( ) ||
             unit_pool_.size( ) == available_index_.first )
        {
            unit_pool_.push_back ( vector<Unit> ( ENTRY_SIZE ) );
        }

        vector<Unit>& pool = unit_pool_[available_index_.first];
        Unit*              unit = &pool[available_index_.second];
        unit->last_seen_game_loop =
            0; // initialization required for OnUnitEnterVision
        tag_to_unit_[tag]          = unit;
        tag_to_existing_unit_[tag] = unit;
        AddNewUnit ( unit );
        IncrementIndex( );
        return unit;
    }

    [[nodiscard]]
    Unit* GetUnit ( const Tag tag ) const {
        const auto found = tag_to_unit_.find ( tag );
        return found == tag_to_unit_.end( ) ? nullptr : found->second;
    }

    [[nodiscard]]
    Unit* GetExistingUnit ( const Tag tag ) const {
        const auto found = tag_to_existing_unit_.find ( tag );
        return found == tag_to_existing_unit_.end( ) ? nullptr : found->second;
    }

    void MarkDead ( const Tag tag ) {
        Unit* unit = GetUnit ( tag );
        if ( !unit ) {
            return;
        }
        unit->is_alive = false;
        // Check if this is necessary, bro
        tag_to_existing_unit_.erase ( tag );
    }

    // TODO(?): Change alive -> Exist
    void ForEachExistingUnit (
        const function<void ( Unit& unit )>& functor
    ) const {
        for ( const auto& val : tag_to_existing_unit_ | views::values ) {
            Assert ( val );
            functor ( *val );
        }
    }

    void ClearExisting ( ) {
        tag_to_existing_unit_.clear( );
        units_newly_created_.clear( );
        units_entering_vision_.clear( );
        buildings_constructed_.clear( );
        units_idled_.clear( );
        units_damaged_.clear( );
    }

    bool UnitExists ( const Tag tag ) const {
        return tag_to_existing_unit_.contains ( tag );
    }

    [[nodiscard]]
    const Units& GetNewUnits ( ) const noexcept {
        return units_newly_created_;
    }

    [[nodiscard]]
    const Units& GetUnitsEnteringVision ( ) const noexcept {
        return units_entering_vision_;
    }

    [[nodiscard]]
    const Units& GetCompletedBuildings ( ) const noexcept {
        return buildings_constructed_;
    }

    [[nodiscard]]
    const UnitsDamaged& GetDamagedUnits ( ) const noexcept {
        return units_damaged_;
    }

    [[nodiscard]]
    const unordered_set<const Unit*>& GetIdledUnits ( ) const noexcept {
        return units_idled_;
    }

    void AddNewUnit ( const Unit* u ) {
        units_newly_created_.push_back ( u );
    }

    void AddUnitEnteredVision ( const Unit* u ) {
        units_entering_vision_.push_back ( u );
    }

    void AddCompletedBuilding ( const Unit* u ) {
        buildings_constructed_.push_back ( u );
    }

    void AddUnitIdled ( const Unit* u ) {
        if ( u->alliance == Unit::Alliance::Self ) {
            units_idled_.insert ( u );
        }
    }

    void AddUnitDamaged ( const Unit* u, float health, float shield ) {
        units_damaged_.push_back (
            { .unit = u, .health = health, .shields = shield }
        );
    }

private:
    void IncrementIndex ( ) {
        ++available_index_.second;
        if ( available_index_.second == ENTRY_SIZE ) {
            ++available_index_.first;
            available_index_.second = 0;
        }
    }

    static constexpr size_t         ENTRY_SIZE = 1000;
    // std::array<Unit, ENTRY_SIZE>
    vector<vector<Unit> > unit_pool_;
    pair<size_t, size_t>       available_index_;
    unordered_map<Tag, Unit*>  tag_to_unit_;
    unordered_map<Tag, Unit*>  tag_to_existing_unit_;
    Units                           units_newly_created_;
    Units                           units_entering_vision_;
    Units                           buildings_constructed_;
    UnitsDamaged                    units_damaged_;
    unordered_set<const Unit*> units_idled_;
};

} // namespace sc2
