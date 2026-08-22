module;
#include <functional>
#include <limits>

// #include "api/control_interfaces.h"
#include "api/data.h"
#include "api/proto_to_pods.h"
#include "api/unit.h"
#include "utils/macro/message_response.h"
export module Client:observation_interface;
import enum_db;
import map_info;
import points;
import score;

using std::function;
using std::numeric_limits;

namespace {

using std::function, std::numeric_limits;

class ControlInterface;
class ProtocolInterface;

} // namespace

export namespace sc2 {

class ObservationInterface {
    ControlInterface&  control_face_;
    ProtocolInterface& proto_face_;

    ObservationPtr&         observation_ptr_;
    ResponseObservationPtr& response_observation_ptr;
    uint32_t                player_id_ { };

    // Game state info.
    UnitPool            unit_pool_;
    uint32_t            current_game_loop_ { };
    uint32_t            previous_game_loop { };
    RawActions          raw_actions_;
    SpatialActions      feature_layer_actions_;
    SpatialActions      rendered_actions_;
    vector<PowerSource> power_sources_;
    vector<Effect>      effects_;
    vector<UpgradeID>   upgrades_;
    vector<UpgradeID>   upgrades_previous_;
    vector<ChatMessage> chat_;

    // Game info.
    mutable GameInfo game_info_;
    mutable bool     game_info_cached_;
    mutable bool     use_generalized_ability_ = true;

    // Player data.
    uint32_t minerals_ { };
    uint32_t vespene_ { };
    uint32_t supply_cap_ { };
    uint32_t supply_used_ { };
    uint32_t supply_army_ { };
    uint32_t supply_workers_ { };
    uint32_t idle_worker_count_ { };
    uint32_t army_count_ { };
    uint32_t warp_gate_count_ { };
    uint32_t larva_count_ { };
    Point2D  camera_pos_;
    Point3D  start_location_;

    // Game data.
    mutable Abilities abilities_;
    mutable UnitTypes unit_types_;
    mutable Upgrades  upgrade_ids_;
    mutable Buffs     buff_ids_;
    mutable Effects   effect_ids_;

    // Score.
    Score score_;

    // Cached data.
    mutable bool abilities_cached_ { };
    mutable bool unit_types_cached { };
    mutable bool upgrades_cached_ { };
    mutable bool buffs_cached_ { };
    mutable bool effects_cached_ { };

    vector<PlayerResult> player_results_;

    ObservationInterface ( );

    ObservationInterface (
            ControlInterface&       control_face,
            ProtocolInterface&      proto_face,
            ObservationPtr&         observation_ptr,
            ResponseObservationPtr& response

    ):
            control_face_ (control_face),
            proto_face_ (proto_face),
            observation_ptr_ (observation_ptr),
            response_observation_ptr (response),
            // Sets game_loop_ to max so that on loop++ it overflows to 0.
            current_game_loop_ (numeric_limits<uint32_t>::max( )),
            previous_game_loop (numeric_limits<uint32_t>::max( )) {
        ClearFlags( );
    }

    ~ObservationInterface ( );

    void ClearFlags ( ) {
        player_id_        = 0;
        game_info_cached_ = false;
        abilities_cached_ = false;
        unit_types_cached = false;
        upgrades_cached_  = false;
        buffs_cached_     = false;
        effects_cached_   = false;
    }

    //! Gets a unique ID that represents the player.
    //! @return The player ID.
    uint32_t GetPlayerID ( ) const {
        return player_id_;
    }

    //! Get the current game loop for this observation.
    //! @return The game loop.
    uint32_t GetGameLoop ( ) const {
        return current_game_loop_;
    }

    //! Get a list of all known units in the game.
    //! @return List of all ally and visible enemy and neutral units.
    Units GetUnits ( ) const {
        Units units;
        unit_pool_.ForEachExistingUnit ([&] (const Unit& unit) {
            units.push_back (&unit);
        });
        return units;
    }

    //! Get the unit state as represented by the last call to GetObservation.
    //! @param tag Unique tag of the unit.
    //! @return Pointer to the Unit object.
    const Unit* GetUnit (Tag tag) const {
        return unit_pool_.GetExistingUnit (tag);
    }

    //! Used to filter out units when querying. You can use this filter to
    //! get all full health units, for example.
    //! @param unit The unit in question to filter.
    //! @param observation The interface for querying game state to
    //! determine whether the unit should be filtered or not.
    //! @return Whether or not to filter the unit in or out of the list.
    //! true will add the unit, false will leave it out of the list.
    //! @sa GetUnits()
    using Filter = function<bool (const Unit& unit)>;

    //! Get all units belonging to self that meet the conditions provided by
    //! the filter. The unit structure is const data only. Therefore editing
    //! that data will not change any in game state. See the ActionInterface
    //! for changing Unit state.
    //! @param filter A functor or lambda used to filter out any unneeded
    //! units in the list.
    //! @return A list of units that meet the conditions provided by the
    //! filter.
    Units GetUnits (const Filter& filter) const;

    //! Get all units belonging to a certain alliance and meet the
    //! conditions provided by the filter. The unit structure is const data
    //! only. Therefore editing that data will not change any in game state.
    //! See the ActionInterface for changing Unit state.
    //! @param alliance The faction the units belong to.
    //! @param filter A functor or lambda used to filter out any unneeded
    //! units in the list.
    //! @return A list of units that meet the conditions provided by
    //! alliance and filter.
    Units GetUnits (Unit::Alliance alliance, const Filter& filter) const {
        Units units;
        unit_pool_.ForEachExistingUnit ([&] (const Unit& unit) {
            if ( unit.alliance != alliance ) {
                return;
            }

            if ( !filter || filter (unit) ) {
                units.push_back (&unit);
            }
        });
        return units;
    }

    //! Gets a list of actions performed as abilities applied to units. For
    //! use with the raw option.
    //! @return List of raw actions.
    const RawActions& GetRawActions ( ) const {
        return raw_actions_;
    }

    //! Gets a list of actions performed. For use with the feature layer
    //! options.
    //! @return List of actions.
    const SpatialActions& GetFeatureLayerActions ( ) const {
        return feature_layer_actions_;
    }

    //! Gets a list of actions performed. For use with the rendered options.
    //! @return List of actions.
    const SpatialActions& GetRenderedActions ( ) const {
        return rendered_actions_;
    }

    //! Gets new chat messages.
    //! @return List of chat messages.
    const vector<ChatMessage>& GetChatMessages ( ) const {
        return chat_;
    }

    //! Gets all power sources associated with the current player.
    //! @return List of power sources.
    const vector<PowerSource>& GetPowerSources ( ) const {
        return power_sources_;
    }

    //! Gets all active effects in vision of the current player.
    //! @return List of effects.
    const vector<Effect>& GetEffects ( ) const {
        return effects_;
    }

    //! Gets all upgrades.
    //! @return List of upgrades.
    const vector<UpgradeID>& GetUpgrades ( ) const {
        return upgrades_;
    }

    //! Gets the detailed current set of scores.
    //! @return The current score structure.
    const Score& GetScore ( ) const {
        return score_;
    }

    virtual const Abilities& GetAbilityData (bool force_refresh = false) const;

    // TODO Refactor
    AbilityID GetGeneralizedAbilityID (uint32_t ability_id) const {
        if ( ability_id == 0 ) // ABILITY_ID::INVALID
        {
            return AbilityID (ability_id);
        }

        const Abilities& abilities = GetAbilityData( );
        if ( ability_id >= abilities.size( ) ) {
            assert (0);
            return AbilityID (ability_id);
        }

        if ( const AbilityData& ability = abilities[ability_id];
             ability.remaps_to_ability_id != 0 ) {
            return AbilityID (ability.remaps_to_ability_id);
        }

        return AbilityID (ability_id);
    }

    virtual const UnitTypes& GetUnitTypeData (
            bool force_refresh = false
    ) const = 0;
    ;

    virtual const Upgrades& GetUpgradeData (bool force_refresh) const;

    virtual const Buffs& GetBuffData (bool force_refresh = false) const;

    virtual const Effects& GetEffectData (bool force_refresh = false) const;

    virtual const GameInfo& GetGameInfo ( ) const = 0;

    //! Returns 'true' if the given point has creep.
    //! \param point Position to sample.
    //! \return Creep.
    // bool HasCreep (const Point2D& point) const
    // {
    //     ObservationRawPtr observation_raw;
    //     SET_SUBMESSAGE_RESPONSE (observation_raw, observation_ptr_,
    //     raw_data); if ( observation_raw.HasErrors( ) ) {
    //         return false;
    //     }
    //
    //     const SC2APIProtocol::MapState& map_state =
    //             observation_raw->map_state( );
    //     const SC2APIProtocol::ImageData& creep = map_state.creep( );
    //
    //     unsigned char value;
    //     if ( !ImageDataLocal (creep, point, value) ) return false;
    //
    //     return value > 0 ? true : false;
    // }

    // bool HasCreep(const Point2D& point) const {
    //    	ObservationRawPtr observation_raw;
    //    	SET_SUBMESSAGE_RESPONSE(observation_raw, observation_ptr_,
    //    raw_data); 	if (observation_raw.HasErrors()) { 		return false;
    //    	}
    //
    //    	return MapState(observation_raw->map_state()).HasCreep(point);
    //    }

    //! Returns visibility value of the given point for the current player.
    //! \param point Position to sample.
    //! \return Visibility.
    Visibility GetVisibility (const Point2D& point) const {
        ObservationRawPtr observation_raw;
        SET_SUBMESSAGE_RESPONSE (observation_raw, observation_ptr_, raw_data);
        if ( observation_raw.HasErrors( ) ) {
            return Visibility::FullHidden;
        }

        const SC2APIProtocol::MapState& map_state =
                observation_raw->map_state( );
        const SC2APIProtocol::ImageData& visibility = map_state.visibility( );

        unsigned char* value { };
        if ( !ImageDataLocal (visibility)
                      .GetBit<unsigned char*> (point, value) )
            return Visibility::FullHidden;
        switch ( value ) {
            case 0: return Visibility::Hidden;
            case 1: return Visibility::Fogged;
            case 2: return Visibility::Visible;
        }
        return Visibility::FullHidden;
    }

    //! Returns 'true' if the given point on the terrain is pathable. This
    //! does not include pathing blockers like structures. For more accurate
    //! pathing results use QueryInterface::PathingDistance.
    //! \param point Position to sample.
    //! \return Pathable.
    bool IsPathable (const Point2D& point) const {
        return PathingGrid (GetGameInfo( )).IsPathable (point);
    }

    //! Returns 'true' if the given point on the terrain is buildable. This
    //! does not include blockers like other structures. For more accurate
    //! building placement results use QueryInterface::Placement.
    //! \param point Position to sample.
    //! \return Placable.
    bool IsPlacable (const Point2D& point) const {
        return PlacementGrid (GetGameInfo( )).IsPlacable (point);
    }

    //! Returns terrain height of the given point.
    //! \param point Position to sample.
    //! \return Height.
    float TerrainHeight (const Point2D& point) const {
        return HeightMap (GetGameInfo( )).TerrainHeight (point);
    }

    //! The mineral count of the player.
    //! \return The mineral count.
    uint32_t GetMinerals ( ) const {
        return minerals_;
    }

    //! The vespene count of the player.
    //! \return The vespene count.
    uint32_t GetVespene ( ) const {
        return vespene_;
    }

    //! The total supply cap given the players max possible supply.
    //! \return Supply cap.
    //! \sa GetSupplyUsed() GetSupplyArmy() GetSupplyWorkers()
    uint32_t GetSupplyCap ( ) const {
        return supply_cap_;
    }

    //! The total supply used by the player as defined: GetSupplyArmy() +
    //! GetSupplyWorkers().
    //! \return Supply used.
    //! \sa GetSupplyArmy() GetSupplyWorkers()
    uint32_t GetSupplyUsed ( ) const {
        return supply_used_;
    }

    //! The total supply consumed by army units alone.
    //! \sa GetSupplyUsed() GetSupplyWorkers()
    //! \return Supply used by army units.
    uint32_t GetSupplyArmy ( ) const {
        return supply_army_;
    }

    //! The total supply consumed by workers units alone.
    //! \sa GetSupplyArmy() GetSupplyUsed()
    //! \return Supply used by worker units.
    uint32_t GetSupplyWorkers ( ) const {
        return supply_workers_;
    }

    //! The number of workers that currently have no orders.
    //! \return Count of idle workers.
    uint32_t GetIdleWorkerCount ( ) const {
        return idle_worker_count_;
    }

    //! The number of army units.
    //! \return Count of army units.
    uint32_t GetArmyCount ( ) const {
        return army_count_;
    }

    //! Number of warp gates owned by the player. This value should only be
    //! nonzero for Protoss.
    //! \return Count of warp gates.
    uint32_t GetWarpGateCount ( ) const {
        return warp_gate_count_;
    }

    //! Number of larva owned by the player. This value should only be
    //! nonzero for Zerg.
    //! \return Count of larva.
    uint32_t GetLarvaCount ( ) const {
        return larva_count_;
    }

    //! Position of the center of the camera.
    //! \return Camera position.
    Point2D GetCameraPos ( ) const {
        return camera_pos_;
    }

    //! Gets the initial start location of the player.
    //! \return Player start position.
    Point3D GetStartLocation ( ) const {
        return start_location_;
    }

    //! Gets the results of the game.
    //! \return Player results if the game ended, an empty vector otherwise.
    const vector<PlayerResult>& GetResults ( ) const {
        return player_results_;
    }

    //! A pointer to the low-level protocol data for the current
    //! observation. While it's possible to extract most in-game data from
    //! this pointer it is highly discouraged. It should only be used for
    //! extracting feature layers because
    //!     it would be inefficient to copy these each frame.
    //! \return A const pointer to the Observation.
    //! \sa Observation GetObservation()
    const SC2APIProtocol::Observation* GetRawObservation ( ) const {
        return observation_ptr_.get( );
    }

    bool UpdateObservation ( ) {
        // Convert observation into data.
        if ( !Convert (observation_ptr_, score_) ) {
            return false;
        }

        uint32_t next_game_loop = observation_ptr_->game_loop( );
        bool     is_new_frame   = next_game_loop != current_game_loop_;
        previous_game_loop      = current_game_loop_;
        current_game_loop_      = next_game_loop;

        const SC2APIProtocol::PlayerCommon& player_common =
                observation_ptr_->player_common( );
        assert (player_common.has_player_id( ));
        if ( player_common.has_player_id( ) ) {
            player_id_ = player_common.player_id( );
        }

        // Fill out game data.
        minerals_          = player_common.minerals( );
        vespene_           = player_common.vespene( );
        supply_used_       = player_common.food_used( );
        supply_cap_        = player_common.food_cap( );
        supply_army_       = player_common.food_army( );
        supply_workers_    = player_common.food_workers( );
        idle_worker_count_ = player_common.idle_worker_count( );
        army_count_        = player_common.army_count( );
        // if constexpr (Race::Protoss) // TODO add race check
        warp_gate_count_   = player_common.warp_gate_count( );
        // else if constexpr (Race::Zerg)
        larva_count_       = player_common.larva_count( );

        // Actions first, as the actions apply to the previous selection.
        if ( is_new_frame ) {
            raw_actions_.clear( );
            feature_layer_actions_ = SpatialActions( );
            rendered_actions_      = SpatialActions( );
        }

        ConvertRawActions (response_observation_ptr, raw_actions_);
        ConvertFeatureLayerActions (
                response_observation_ptr,
                feature_layer_actions_
        );
        ConvertRenderedActions (response_observation_ptr, rendered_actions_);

        { // Remap ability ids.
            for ( ActionRaw& action : raw_actions_ ) {
                action.ability_id = GetGeneralizedAbilityID (action.ability_id);
            }
            for ( SpatialUnitCommand& spatial_action :
                  feature_layer_actions_.unit_commands ) {
                spatial_action.ability_id =
                        GetGeneralizedAbilityID (spatial_action.ability_id);
            }
            for ( SpatialUnitCommand& spatial_action :
                  rendered_actions_.unit_commands ) {
                spatial_action.ability_id =
                        GetGeneralizedAbilityID (spatial_action.ability_id);
            }
        }

        chat_.clear( );
        for ( const auto& message : response_observation_ptr->chat( ) ) {
            chat_.push_back ({message.player_id( ), message.message( )});
        }

        ObservationRawPtr observation_raw;
        SET_SUBMESSAGE_RESPONSE (observation_raw, observation_ptr_, raw_data);
        if ( observation_raw.HasErrors( ) ) {
            return false;
        }

        unit_pool_.ClearExisting( );
        Convert (
                observation_raw,
                unit_pool_,
                current_game_loop_,
                previous_game_loop
        );

        // Remap ability ids in orders.
        unit_pool_.ForEachExistingUnit ([&] (Unit& unit) {
            for ( UnitOrder& unit_order : unit.orders ) {
                if ( use_generalized_ability_ ) {
                    unit_order.ability_id =
                            GetGeneralizedAbilityID (unit_order.ability_id);
                }
            }
        });

        effects_.clear( );
        effects_.resize (observation_raw->effects_size( ));
        for ( int i = 0; i < observation_raw->effects_size( ); ++i ) {
            effects_[i].ReadFromProto (observation_raw->effects (i));
        }

        if ( !observation_raw->has_player( ) ) {
            return false;
        }

        const SC2APIProtocol::PlayerRaw& player_raw =
                observation_raw->player( );
        if ( !player_raw.has_camera( ) ) {
            return false;
        }

        camera_pos_.x = player_raw.camera( ).x( );
        camera_pos_.y = player_raw.camera( ).y( );

        power_sources_.clear( );
        for ( int i = 0, e = player_raw.power_sources_size( ); i < e; ++i ) {
            const SC2APIProtocol::PowerSource& power_source =
                    player_raw.power_sources (i);
            power_sources_.push_back (PowerSource (
                    Point2D (
                            power_source.pos( ).x( ),
                            power_source.pos( ).y( )
                    ),
                    power_source.radius( ),
                    power_source.tag( )
            ));
        }

        upgrades_previous_ = upgrades_;
        upgrades_.clear( );
        for ( int i = 0; i < player_raw.upgrade_ids_size( ); ++i ) {
            upgrades_.push_back (player_raw.upgrade_ids (i));
        }

        player_results_.clear( );
        for ( const auto& player_result :
              response_observation_ptr->player_result( ) ) {
            player_results_.push_back (PlayerResult (
                    player_result.player_id( ),
                    ConvertGameResultFromProto (player_result.result( ))
            ));
        }

        return true;
    }

}; // class ObservationImplementation

[[maybe_unused]]
static bool ImageDataLocal (
        const string&  data,
        int            width,
        int            height,
        const Point2D& point,
        unsigned char& result
) {
    const Point2DI pointI = point;
    // Check to see that the point is within the map space
    if ( pointI.x >= width || pointI.y >= height ) {
        return false;
    }

    // Image data is stored with an upper left origin.
    assert (data.size( ) == width * height);
    result = data[pointI.x + (height - 1 - pointI.y) * width];
    return true;
}

[[maybe_unused]]
static bool ImageDataLocal (
        const SC2APIProtocol::ImageData& i_data,
        const Point2D&                   point,
        unsigned char&                   result
) {
    return ImageDataLocal (
            i_data.data( ),
            i_data.size( ).x( ),
            i_data.size( ).y( ),
            point,
            result
    );
}

// [[maybe_unused]]
// static bool ImageDataLocal( const ImageDataLocal& i_data,
//                             const Point2D&        point,
//                             unsigned char&        result ) {
//     return ImageDataLocal( i_data.data, i_data.width, i_data.height, point,
//     result );
// }

} // namespace sc2
