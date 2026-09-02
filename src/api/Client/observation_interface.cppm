module;
// #include <functional>
// #include <limits>
// #include <string>

#include <s2clientprotocol/sc2api.pb.h>

#include "utils/macro/message_response.h"
export module observation_interface;
import std;
import protocol_interface;
import action;
import common;
import data;
import enum_db;
import error_handler;
import game_types;
import map_info;
import proto_to_pods;
import score;
import type_enums;
import unit;

namespace {

struct MapState
{
private:
    sc2::ImageData_StepSample creep_data_;
    sc2::ImageData_StepSample visibility_data_;

public:
    explicit MapState ( const SC2APIProtocol::MapState &map )
      : creep_data_ ( map.creep( ) ),
        visibility_data_ ( map.visibility( ) ) { }

    bool HasCreep ( const sc2::Point2DI &point ) const {
        if ( creep_data_.BPP( ) == 1 ) {
            bool value;
            if ( !creep_data_.GetBit ( point, &value ) )
                return false;

            return value;
        }

        unsigned char value;
        if ( !creep_data_.GetBit ( point, &value ) )
            return false;

        return value > 0;
    }

    sc2::Visibility GetVisibility ( const sc2::Point2DI &point ) const {
        unsigned char value;
        if ( !visibility_data_.GetBit ( point, &value ) )
            return sc2::Visibility::FullHidden;

        if ( value == 0 )
            return sc2::Visibility::Hidden;

        if ( value == 1 )
            return sc2::Visibility::Fogged;

        if ( value == 2 )
            return sc2::Visibility::Visible;

        return sc2::Visibility::FullHidden;
    }
};


} // namespace

export namespace sc2 {
using namespace std;

//! The ObservationInterface reflects the current state of the game.
//! Guaranteed to be valid when OnGameStart or OnStep is called.
class ObservationInterface {
public:
    ObservationPtr         &observation_;
    ResponseObservationPtr &response_;
    uint32_t                player_id_ { 0 };

    // Game state info.
    UnitPool            unit_pool_;
    // Sets game_loop_ to max so that on loop++ it overflows to 0.
    uint32_t            current_game_loop_ { numeric_limits<uint32_t>::max( ) };
    uint32_t            previous_game_loop { numeric_limits<uint32_t>::max( ) };
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
    uint32_t minerals_ { 0 };
    uint32_t vespene_ { 0 };
    uint32_t supply_cap_ { 0 };
    uint32_t supply_used_ { 0 };
    uint32_t supply_army_ { 0 };
    uint32_t supply_workers_ { 0 };
    uint32_t idle_worker_count_ { 0 };
    uint32_t army_count_ { 0 };
    uint32_t warp_gate_count_ { 0 };
    uint32_t larva_count_ { 0 };
    Point2D  camera_pos_ { };
    Point3D  start_location_ { };

    // Game data.
    mutable Abilities abilities_;
    mutable UnitTypes unit_types_;
    mutable Upgrades  upgrade_ids_;
    mutable Buffs     buff_ids_;
    mutable Effects   effect_ids_;

    // Score.
    Score score_;

    // Cached data.
    mutable bool abilities_cached_ { false };
    mutable bool unit_types_cached { false };
    mutable bool upgrades_cached_ { false };
    mutable bool buffs_cached_ { false };
    mutable bool effects_cached_ { false };

    vector<PlayerResult> player_results_;

    ObservationInterface (
      ObservationPtr         &observation,
      ResponseObservationPtr &response
    )
      : observation_ ( observation ),
        response_ ( response ),
        game_info_ ( GetGameInfo( ) )
    {
        ClearFlags( );
    }

    ~ObservationInterface ( ) = default;

    void ClearFlags ( ) {
        player_id_        = 0;
        game_info_cached_ = false;
        abilities_cached_ = false;
        unit_types_cached = false;
        upgrades_cached_  = false;
        buffs_cached_     = false;
        effects_cached_   = false;
    }

    /*! @brief Gets a unique ID that represents the player.
     * @return The player ID. */
    uint32_t GetPlayerID ( ) const {
        return player_id_;
    }

    /*! @brief Get the current game loop for this observation.
     * @return The game loop. */
    uint32_t GetGameLoop ( ) const {
        return current_game_loop_;
    }

    /*! @brief Get a list of all known units in the game.
     * @return List of all ally and visible enemy and neutral units. */
    Units GetUnits ( ) const {
        Units units;
        unit_pool_.ForEachExistingUnit ( [&] ( const Unit &unit ) {
            units.push_back ( &unit );
        } );
        return units;
    }

    /*! Get the unit state as represented by the last call to GetObservation.
     * @param tag Unique tag of the unit.
     * @return @code Unit* @endcode Pointer to the Unit object. */
    const Unit *GetUnit ( Tag tag ) const {
        return unit_pool_.GetExistingUnit ( tag );
    }

    /*! @brief Used to filter out units when querying. You can use this filter
     * to get all full health units, for example.
     * @param unit The unit in question to filter.
     * @param observation The interface for querying game state to determine
     * whether the unit should be filtered or not.
     * @return Whether or not to filter the unit in or out of the list. true
     * will add the unit, false will leave it out of the list.
     * @see GetUnits() */
    using Filter = function<bool ( const Unit &unit )>;

    /*! @brief Get all units belonging to self that meet the conditions provided
     * by the filter. The unit * structure is const data only. Therefore editing
     * that data will not change any in game state.
     * @see @ActionInterface for changing Unit state.
     * @param filter A functor or lambda used to filter out any unneeded units
     * in the list.
     * @return A list of units that meet the conditions provided by the filter.
     */
    Units GetUnits ( const Filter &filter ) const {
        Units units;
        unit_pool_.ForEachExistingUnit ( [&] ( const Unit &unit ) {
            if ( !filter || filter ( unit ) ) {
                units.push_back ( &unit );
            }
        } );
        return units;
    }

    /*! @brief Get all units belonging to a certain alliance and meet the
     * conditions provided by the filter. The unit structure is const data only.
     * Therefore editing that data will not change any in game state. See the
     * ActionInterface for changing Unit state.
     * @param alliance The faction the units belong to.
     * @param filter A functor or lambda used to filter out any unneeded units
     * in the list.
     * @return @code Units @endcode A list of units that meet the conditions
     * provided by alliance and filter. */
    Units GetUnits ( Unit::Alliance alliance, const Filter &filter ) const {
        Units units;
        unit_pool_.ForEachExistingUnit ( [&] ( const Unit &unit ) {
            if ( unit.alliance != alliance ) {
                return;
            }

            if ( !filter || filter ( unit ) ) {
                units.push_back ( &unit );
            }
        } );
        return units;
    }

    /*! @brief Gets a list of actions performed as abilities applied to units.
     * For use with the raw option.
     * @return List of raw actions. */
    const RawActions &GetRawActions ( ) const {
        return raw_actions_;
    }

    /*! @brief Gets a list of actions performed. For use with the feature layer
     * options.
     * @return List of actions. */
    const SpatialActions &GetFeatureLayerActions ( ) const {
        return feature_layer_actions_;
    }

    /*! @brief Gets a list of actions performed. For use with the rendered
     * options.
     * @return List of actions. */
    const SpatialActions &GetRenderedActions ( ) const {
        return rendered_actions_;
    }

    /*! @brief Gets new chat messages.
     * @return List of chat messages. */
    const vector<ChatMessage> &GetChatMessages ( ) const {
        return chat_;
    }

    /*! @brief Gets all power sources associated with the current player.
     * @return List of power sources. */
    const vector<PowerSource> &GetPowerSources ( ) const {
        return power_sources_;
    }

    /*! @brief Gets all active effects in vision of the current player.
     * @return List of effects. */
    const vector<Effect> &GetEffects ( ) const {
        return effects_;
    }

    /*! @brief Gets all upgrades.
     * @return List of upgrades. */
    const vector<UpgradeID> &GetUpgrades ( ) const {
        return upgrades_;
    }

    /*! @brief Gets the detailed current set of scores.
     * @return The current score structure. */
    const Score &GetScore ( ) const {
        return score_;
    }

    /*! @brief Gets metadata of abilities. Array can be indexed directly by
     * AbilityID.
     * @param force_refresh Forces a full query from the game, may otherwise
     * cache data from a previous call.
     * @return  All abilities allowed (`available`) for the current game
     * session. */
    const Abilities &GetAbilityData ( bool force_refresh = false ) const {
        // Checks whether function execution is required.
        if ( force_refresh || abilities_.empty( ) ) {
            abilities_cached_ = false;
        }

        // Returns the cached ability list if it already exists.
        if ( abilities_cached_ ) {
            return abilities_;
        }

        abilities_.clear( );

        // Send a request for ability ids.
        const GameRequestPtr         request      = ProtoFace::MakeRequest( );
        SC2APIProtocol::RequestData *request_data = request->mutable_data( );
        request_data->set_ability_id ( true );

        if ( !ProtoFace::SendRequest ( request ) ) {
            return abilities_;
        }

        const GameResponsePtr response = ProtoFace::WaitForResponse( );
        //!
        ResponseDataPtr       response_data;
        SET_MESSAGE_RESPONSE ( response_data, response, data );

        if (
          response_data.HasErrors( ) || response_data->abilities_size( ) == 0
        )
        {
            return abilities_;
        }

        // Compress to the size of `abilities` to match its size.
        abilities_.resize ( response_data->abilities_size( ) );

        // For each ability
        for ( int i = 0; i < response_data->abilities_size( ); ++i ) {
            AbilityData &ability_data = abilities_[i];
            ability_data.ability_id   = i;

            ability_data.ReadFromProto ( response_data->abilities ( i ) );
        }

        for ( const AbilityData &ability_data : abilities_ ) {
            AbilityID genAbility =
              GetGeneralizedAbilityID ( ability_data.ability_id );
            if ( genAbility == ability_data.ability_id )
                continue;

            if ( genAbility >= abilities_.size( ) ) {
                Error::Log ( ClientError::InvalidAbilityRemap );
                genAbility = 0;
            }
        }

        abilities_cached_ = true;
        return abilities_;
    }

    // // TODO Refactor
    // AbilityID GetGeneralizedAbilityID ( uint32_t ability_id ) const {
    //     if ( ability_id == 0 ) // ABILITY_ID::INVALID
    //     {
    //         return AbilityID ( ability_id );
    //     }
    //
    //     generalize_ability
    //
    //     const Abilities& abilities = GetAbilityData( );
    //     if ( ability_id >= abilities.size( ) )
    //     {
    //         Assert ( 0 );
    //         return AbilityID ( ability_id );
    //     }
    //
    //     if ( const AbilityData& ability = abilities[ability_id];
    //          ability.remaps_to_ability_id != 0 )
    //     {
    //         return AbilityID ( ability.remaps_to_ability_id );
    //     }
    //
    //     return AbilityID ( ability_id );
    // }

    /*! @brief Gets metadata of units. Array can be indexed directly by UnitID.
     * @param force_refresh forces a full query from the game, may otherwise
     * cache data from a previous call.
     * @return @code UnitTypes& @endcode Data about all units possible for the
     * current game session. */
    const UnitTypes &GetUnitTypeData ( bool force_refresh ) const {
        if ( force_refresh || unit_types_.size( ) < 1 ) {
            unit_types_cached = false;
        }

        if ( unit_types_cached ) {
            return unit_types_;
        }

        unit_types_.clear( );

        // Send a request for ability ids.
        const GameRequestPtr         request      = ProtoFace::MakeRequest( );
        SC2APIProtocol::RequestData *request_data = request->mutable_data( );
        request_data->set_unit_type_id ( true );

        if ( !ProtoFace::SendRequest ( request ) ) {
            return unit_types_;
        }

        const GameResponsePtr response = ProtoFace::WaitForResponse( );
        ResponseDataPtr       response_data;
        SET_MESSAGE_RESPONSE ( response_data, response, data );
        if ( response_data.HasErrors( ) ) {
            return unit_types_;
        }

        if ( response_data.HasErrors( ) || response_data->units_size( ) == 0 ) {
            return unit_types_;
        }

        unit_types_.resize ( response_data->units_size( ) );
        for ( int i = 0; i < response_data->units_size( ); ++i ) {
            UnitTypeData &unit = unit_types_[i];
            unit.unit_type_id  = i;
            unit.ReadFromProto ( response_data->units ( i ) );
        }

        unit_types_cached = true;
        return unit_types_;
    }

    /*! @brief Gets metadata of upgrades. Array can be indexed directly by
     * UpgradeID.
     * @param force_refresh forces a full query from the game, may otherwise
     * cache data from a previous call.
     * @return Data about all upgrades possible for the current game session. */
    const Upgrades &GetUpgradeData ( bool force_refresh ) const {
        if ( force_refresh || upgrade_ids_.empty( ) ) {
            upgrades_cached_ = false;
        }

        if ( upgrades_cached_ ) {
            return upgrade_ids_;
        }

        upgrade_ids_.clear( );

        const GameRequestPtr         request      = ProtoFace::MakeRequest( );
        SC2APIProtocol::RequestData *request_data = request->mutable_data( );
        request_data->set_upgrade_id ( true );

        if ( !ProtoFace::SendRequest ( request ) ) {
            return upgrade_ids_;
        }

        const GameResponsePtr response = ProtoFace::WaitForResponse( );
        ResponseDataPtr       response_data;
        SET_MESSAGE_RESPONSE ( response_data, response, data );
        if (
          response_data.HasErrors( ) || response_data->upgrades_size( ) == 0
        )
        {
            return upgrade_ids_;
        }

        upgrade_ids_.resize ( response_data->upgrades_size( ) );
        for ( int i = 0; i < response_data->upgrades_size( ); ++i ) {
            UpgradeData &upgrade = upgrade_ids_[i];
            upgrade.upgrade_id   = i;
            upgrade.ReadFromProto ( response_data->upgrades ( i ) );
        }

        upgrades_cached_ = true;
        return upgrade_ids_;
    }

    /*! @brief Gets metadata of buffs. Array can be indexed directly by BuffID.
     * @param force_refresh forces a full query from the game, may otherwise
     * cache data from a previous call.
     * @return Buffs& - Data about all buffs possible for the current game
     * session. */
    const Buffs &GetBuffData ( bool force_refresh ) const {
        if ( force_refresh || buff_ids_.empty( ) ) {
            buffs_cached_ = false;
        }

        if ( buffs_cached_ ) {
            return buff_ids_;
        }

        buff_ids_.clear( );

        const GameRequestPtr         request      = ProtoFace::MakeRequest( );
        SC2APIProtocol::RequestData *request_data = request->mutable_data( );
        request_data->set_buff_id ( true );

        if ( !ProtoFace::SendRequest ( request ) ) {
            return buff_ids_;
        }

        const GameResponsePtr response = ProtoFace::WaitForResponse( );
        ResponseDataPtr       response_data;
        SET_MESSAGE_RESPONSE ( response_data, response, data );
        if ( response_data.HasErrors( ) ) {
            return buff_ids_;
        }

        if ( response_data.HasErrors( ) || response_data->buffs_size( ) == 0 ) {
            return buff_ids_;
        }

        buff_ids_.resize ( response_data->buffs_size( ) );
        for ( int i = 0; i < response_data->buffs_size( ); ++i ) {
            BuffData &buff = buff_ids_[i];
            buff.buff_id   = i;
            buff.ReadFromProto ( response_data->buffs ( i ) );
        }

        buffs_cached_ = true;
        return buff_ids_;
    }

    /*! @brief Gets metadata of effects. Array can be indexed directly by
     * EffectID.
     * @param force_refresh forces a full query from the game, may otherwise
     * cache data from a previous call.
     * @return Data about all effects possible for the current game session. */
    const Effects &GetEffectData ( bool force_refresh ) const {
        if ( force_refresh || effect_ids_.empty( ) ) {
            effects_cached_ = false;
        }

        if ( effects_cached_ ) {
            return effect_ids_;
        }

        effect_ids_.clear( );

        const GameRequestPtr         request      = ProtoFace::MakeRequest( );
        SC2APIProtocol::RequestData *request_data = request->mutable_data( );
        request_data->set_effect_id ( true );

        if ( !ProtoFace::SendRequest ( request ) ) {
            return effect_ids_;
        }

        const GameResponsePtr response = ProtoFace::WaitForResponse( );
        ResponseDataPtr       response_data;
        SET_MESSAGE_RESPONSE ( response_data, response, data );
        if ( response_data.HasErrors( ) ) {
            return effect_ids_;
        }

        if ( response_data.HasErrors( ) || response_data->effects_size( ) == 0 )
        {
            return effect_ids_;
        }

        effect_ids_.resize ( response_data->effects_size( ) );
        for ( int i = 0; i < response_data->effects_size( ); ++i ) {
            effect_ids_[i].ReadFromProto ( response_data->effects ( i ) );
        }

        effects_cached_ = true;
        return effect_ids_;
    }

    /*! @brief Gets the GameInfo struct for the current map.
     * @return The current GameInfo struct. */
    const GameInfo &GetGameInfo ( ) const {
        if ( game_info_cached_ ) {
            return game_info_;
        }

        const GameRequestPtr request = ProtoFace::MakeRequest( );
        request->mutable_game_info( );

        if ( !ProtoFace::SendRequest ( request ) ) {
            return game_info_;
        }

        const GameResponsePtr response = ProtoFace::WaitForResponse( );
        ResponseGameInfoPtr   response_game_info;
        SET_MESSAGE_RESPONSE ( response_game_info, response, game_info );
        if ( response_game_info.HasErrors( ) ) {
            return game_info_;
        }

        Convert ( response_game_info, game_info_ );

        game_info_cached_ = true;
        return game_info_;
    }

    //! Returns 'true' if the given point has creep.
    //! @param point Position to sample.
    //! @return Creep.
    // bool HasCreep (const Point2D& point) const
    // {
    //     ObservationRawPtr observation_raw;
    //     SET_SUBMESSAGE_RESPONSE (observation_raw, observation_,
    //     raw_data); if ( observation_raw.HasErrors( ) ) {
    //         return false;
    //     }
    //
    //     const SC2APIProtocol::MapState& map_state =
    //             observation_raw->map_state( );
    //     const SC2APIProtocol::ImageData& creep = map_state.creep( );
    //
    //     unsigned char value;
    //     if ( !ImageData (creep, point, value) ) return false;
    //
    //     return value > 0 ? true : false;
    // }

    /*! @brief Returns 'true' if the given point has creep.
     * @param point Position to sample.
     * @return Creep.*/
    bool HasCreep ( const Point2DI &point ) const {
        ObservationRawPtr observation_raw;
        SET_SUBMESSAGE_RESPONSE ( observation_raw, observation_, raw_data );
        if ( observation_raw.HasErrors( ) ) {
            return false;
        }

        return MapState ( observation_raw->map_state( ) ).HasCreep ( point );
    }

    /*! @brief Returns visibility value of the given point for the current
     * player.
     * @param point Position to sample.
     * @return Visibility.*/
    Visibility GetVisibility ( const Point2DI &point ) const {
        ObservationRawPtr observation_raw;
        SET_SUBMESSAGE_RESPONSE ( observation_raw, observation_, raw_data );
        if ( observation_raw.HasErrors( ) ) {
            return Visibility::FullHidden;
        }

        return MapState ( observation_raw->map_state( ) )
          .GetVisibility ( point );
    }

    // TODO

    //     const SC2APIProtocol::MapState& map_state =
    //         observation_raw->map_state( );
    //     const SC2APIProtocol::ImageData& visibility = map_state.visibility(
    //     );
    //
    //     unsigned char* value { };
    //     if ( !ImageData ( visibility ).GetBit<unsigned char*> ( point, value
    //     ) )
    //         return Visibility::FullHidden;
    //     switch ( value )
    //     {
    //         case 0 : return Visibility::Hidden;
    //         case 1 : return Visibility::Fogged;
    //         case 2 : return Visibility::Visible;
    //     }
    //     return Visibility::FullHidden;
    // }

    /*! @brief Returns 'true' if the given point on the terrain is pathable.
     * This does not include pathing blockers like structures. For more accurate
     * pathing results use QueryInterface::PathingDistance.
     * @param point Position to sample.
     * @return Pathable. */
    bool IsPathable ( const Point2DI &point ) const {
        return PathingGrid ( GetGameInfo( ) ).IsPathable ( point );
    }

    /*! @brief Returns 'true' if the given point on the terrain is buildable.
     * This does not include blockers like other structures. For more accurate
     * building placement results use QueryInterface::Placement.
     * @param point Position to sample.
     * @return Placable. */
    bool IsPlacable ( const Point2D &point ) const {
        return PlacementGrid ( GetGameInfo( ) ).IsPlacable ( point );
    }

    /*! @brief Returns terrain height of the given point.
     * @param point Position to sample.
     * @return Height. */
    float TerrainHeight ( const Point2D &point ) const {
        return HeightMap ( GetGameInfo( ) ).TerrainHeight ( point );
    }

    /*! @brief The mineral count of the player.
     * @return The mineral count. */
    uint32_t GetMinerals ( ) const {
        return minerals_;
    }

    /*! @brief The vespene count of the player.
     * @return The vespene count. */
    uint32_t GetVespene ( ) const {
        return vespene_;
    }

    /*! @brief The total supply cap given the players max possible supply.
     * @return Supply cap.
     * @see GetSupplyUsed() GetSupplyArmy() GetSupplyWorkers() */
    uint32_t GetSupplyCap ( ) const {
        return supply_cap_;
    }

    /*! The total supply used by the player as defined:\n
     * GetSupplyArmy() + GetSupplyWorkers().
     * @return Supply used.
     * @see GetSupplyArmy() GetSupplyWorkers() */
    uint32_t GetSupplyUsed ( ) const {
        return supply_used_;
    }

    /*! @brief The total supply consumed by army units alone.
     * @return Supply used by army units.
     * @see GetSupplyUsed() GetSupplyWorkers() */
    uint32_t GetSupplyArmy ( ) const {
        return supply_army_;
    }

    /*! @brief The total supply consumed by workers units alone.
     * @return Supply used by worker units.
     * @see GetSupplyArmy() GetSupplyUsed() */
    uint32_t GetSupplyWorkers ( ) const {
        return supply_workers_;
    }

    /*! @brief The number of workers that currently have no orders.
     * @return Count of idle workers. */
    uint32_t GetIdleWorkerCount ( ) const {
        return idle_worker_count_;
    }

    /*! @brief The number of army units.
     * @return Count of army units. */
    uint32_t GetArmyCount ( ) const {
        return army_count_;
    }

    /*! @brief Number of warp gates owned by the player. This value should only
     * be nonzero for Protoss.
     * @return Count of warp gates. */
    uint32_t GetWarpGateCount ( ) const {
        return warp_gate_count_;
    }

    /*! @brief Number of larva owned by the player. This value should only be
     * nonzero for Zerg.
     * @return Count of larva. */
    uint32_t GetLarvaCount ( ) const {
        return larva_count_;
    }

    /*! @brief Position of the center of the camera.
     * @return Camera position. */
    Point2D GetCameraPos ( ) const {
        return camera_pos_;
    }

    /*! @brief Gets the initial start location of the player.
     * @return Player start position. */
    Point3D GetStartLocation ( ) const {
        return start_location_;
    }

    /*! @brief Gets the results of the game.
     * @return Player results if the game ended, an empty vector otherwise. */
    const vector<PlayerResult> &GetResults ( ) const {
        return player_results_;
    }

    /*! @brief A pointer to the low-level protocol data for the current
     * observation. While it's possible to extract most in-game data from this
     * pointer it is highly discouraged. It should only be used for extracting
     * feature layers because it would be inefficient to copy these each frame.
     * @return A const pointer to the Observation.
     * @see Observation GetObservation() */
    const SC2APIProtocol::Observation *GetRawObservation ( ) const {
        return observation_.get( );
    }

    bool UpdateObservation ( ) {
        // Convert observation into data.
        if ( !Convert ( observation_, score_ ) ) {
            return false;
        }

        const uint32_t next_game_loop = observation_->game_loop( );
        const bool     is_new_frame   = next_game_loop != current_game_loop_;
        previous_game_loop            = current_game_loop_;
        current_game_loop_            = next_game_loop;

        const SC2APIProtocol::PlayerCommon &player_common =
          observation_->player_common( );
        Assert ( player_common.has_player_id( ) );
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
        warp_gate_count_   = player_common.warp_gate_count( );
        larva_count_       = player_common.larva_count( );

        // Actions first, as the actions apply to the previous selection.
        if ( is_new_frame ) {
            raw_actions_.clear( );
            feature_layer_actions_ = SpatialActions( );
            rendered_actions_      = SpatialActions( );
        }

        ConvertRawActions ( response_, raw_actions_ );
        ConvertFeatureLayerActions ( response_, feature_layer_actions_ );
        ConvertRenderedActions ( response_, rendered_actions_ );

        // Remap ability ids.
        {
            for ( ActionRaw &action : raw_actions_ ) {
                action.ability_id =
                  GetGeneralizedAbilityID ( action.ability_id );
            }
            for ( SpatialUnitCommand &spatial_action :
                  feature_layer_actions_.unit_commands )
            {
                spatial_action.ability_id =
                  GetGeneralizedAbilityID ( spatial_action.ability_id );
            }
            for ( SpatialUnitCommand &spatial_action :
                  rendered_actions_.unit_commands )
            {
                spatial_action.ability_id =
                  GetGeneralizedAbilityID ( spatial_action.ability_id );
            }
        }

        chat_.clear( );
        for ( const auto &message : response_->chat( ) ) {
            chat_.push_back (
              { .player_id = message.player_id( ),
                .message   = message.message( ) }
            );
        }

        ObservationRawPtr observation_raw;
        SET_SUBMESSAGE_RESPONSE ( observation_raw, observation_, raw_data );
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
        unit_pool_.ForEachExistingUnit ( [&] ( Unit &unit ) {
            for ( UnitOrder &unit_order : unit.orders ) {
                if ( use_generalized_ability_ ) {
                    unit_order.ability_id =
                      GetGeneralizedAbilityID ( unit_order.ability_id );
                }
            }
        } );

        effects_.clear( );
        effects_.resize ( observation_raw->effects_size( ) );
        for ( int i = 0; i < observation_raw->effects_size( ); ++i ) {
            effects_[i].ReadFromProto ( observation_raw->effects ( i ) );
        }

        if ( !observation_raw->has_player( ) ) {
            return false;
        }

        const SC2APIProtocol::PlayerRaw &player_raw =
          observation_raw->player( );
        if ( !player_raw.has_camera( ) ) {
            return false;
        }

        camera_pos_.x = player_raw.camera( ).x( );
        camera_pos_.y = player_raw.camera( ).y( );

        power_sources_.clear( );
        for ( int i = 0, e = player_raw.power_sources_size( ); i < e; ++i ) {
            const SC2APIProtocol::PowerSource &power_source =
              player_raw.power_sources ( i );
            power_sources_.push_back ( PowerSource (
              Point2D ( power_source.pos( ).x( ), power_source.pos( ).y( ) ),
              power_source.radius( ),
              power_source.tag( )
            ) );
        }

        upgrades_previous_ = upgrades_;
        upgrades_.clear( );
        for ( int i = 0; i < player_raw.upgrade_ids_size( ); ++i ) {
            upgrades_.push_back ( player_raw.upgrade_ids ( i ) );
        }

        player_results_.clear( );
        for ( const auto &player_result : response_->player_result( ) ) {
            player_results_.push_back ( PlayerResult (
              player_result.player_id( ),
              ConvertGameResultFromProto ( player_result.result( ) )
            ) );
        }

        return true;
    }

}; // class ObservationImplementation

// [[maybe_unused]]
// bool ImageData (
//     const string&  data,
//     int            width,
//     int            height,
//     const Point2D& point,
//     unsigned char& result
// ) {
//     const Point2DI pointI = point;
//     // Check to see that the point is within the map space
//     if ( pointI.x >= width || pointI.y >= height ) {
//         return false;
//     }
//
//     // Image data is stored with an upper left origin.
//     Assert ( data.size( ) == width * height );
//     result = data[pointI.x + ( height - 1 - pointI.y ) * width];
//     return true;
// }
//
// [[maybe_unused]]
// bool ImageData (
//     const SC2APIProtocol::ImageData& i_data,
//     const Point2D&                   point,
//     unsigned char&                   result
// ) {
//     return ImageData (
//         i_data.data( ),
//         i_data.size( ).x( ),
//         i_data.size( ).y( ),
//         point,
//         result
//     );
// }

} // namespace sc2
