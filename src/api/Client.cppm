/*! @file Client.cppm
@brief The base class for Agent and ReplayObserver.

The Client and ClientEvents provides most of the functionality a user would be
interested in for examining game state and scripting bots. A user should prefer
to inherit from either Agent or ReplayObserver, those classes both inherit from
Client.
*/
module;
#include <cassert>
#include <fstream>
#include <iostream>
#include <limits>
#include <string>
#include <unordered_map>
#include <vector>

#include <s2clientprotocol/sc2api.pb.h>

#include "api/proto_to_pods.h"
#include "api/unit.h"
#include "lib/type_enums.h"
#include "utils/macro/message_response.h"
#include "utils/manage_process.h"
export module Client;
import common;
import data;
import error_handler;
import game_settings;
import map_info;
import renderer;
import score;

namespace {




sc2::GameResponsePtr
    WaitForResponse ( );

enum class AppTest;

struct MapState
{
    explicit MapState ( const SC2APIProtocol::MapState& map );

    bool
        HasCreep ( const sc2::Point2D& point ) const;

    sc2::Visibility
        GetVisibility ( const sc2::Point2D& point ) const;

private:
    sc2::ImageData creep_data_;
    sc2::ImageData visibility_data_;
};

MapState::MapState (
    const SC2APIProtocol::MapState& map
)
      : creep_data_ ( map.creep( ) ),
        visibility_data_ ( map.visibility( ) )
{}

bool
    MapState::HasCreep (
        const sc2::Point2D& point
    ) const
{
    if ( creep_data_.BPP( ) == 1 )
    {
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

sc2::Visibility
    MapState::GetVisibility (
        const sc2::Point2D& point
    ) const
{
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

} // namespace

export namespace sc2 {

class ControlInterface;


// static GameResponsePtr
//     ControlInterface::WaitForResponse ( );

/*! @brief Used to filter out units when querying. You can use this filter to
 * get all full health units, for example.
 * @param unit The unit in question to filter.
 * @param observation The interface for querying game state to determine whether
 * the unit should be filtered or not.
 * @return Whether or not to filter the unit in or out of the list. true will
 * add the unit, false will leave it out of the list.
 * @sa GetUnits() */
typedef std::function<bool ( const Unit& unit )> Filter;

//------------------------------------------------------------------------------

// ObservationInterface   -   ObservationInterface   -   ObservationInterface

//------------------------------------------------------------------------------

/*! @brief The ObservationInterface reflects the current state of the game.
 * Guaranteed to be valid when OnGameStart or OnStep is called. */
class ObservationInterface
{
public:
    ObservationPtr         observation_;
    ResponseObservationPtr response_;
    // ControlInterface       control_;
    uint32_t               player_id_ { 0 };

    // Game state info.
    UnitPool       unit_pool_;
    uint32_t       current_game_loop_ { std::numeric_limits<uint32_t>::max( ) };
    uint32_t       previous_game_loop { std::numeric_limits<uint32_t>::max( ) };
    RawActions     raw_actions_;
    SpatialActions feature_layer_actions_;
    SpatialActions rendered_actions_;
    std::vector<PowerSource> power_sources_;
    std::vector<Effect>      effects_;
    std::vector<UpgradeID>   upgrades_;
    std::vector<UpgradeID>   upgrades_previous_;
    std::vector<ChatMessage> chat_;

    // Game info.
    mutable GameInfo game_info_;
    mutable bool     game_info_cached_;
    mutable bool     use_generalized_ability_ = true;

    // Player data.
    uint32_t minerals_ { 0 };
    uint32_t vespene_ { 0 };
    uint32_t food_cap_ { 0 };
    uint32_t food_used_ { 0 };
    uint32_t food_army_ { 0 };
    uint32_t food_workers_ { 0 };
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
    mutable bool abilities_cached_;
    mutable bool unit_types_cached;
    mutable bool upgrades_cached_;
    mutable bool buffs_cached_;
    mutable bool effects_cached_;

    std::vector<PlayerResult> player_results_;

    ObservationInterface (
        const ObservationPtr&         observation,
        const ResponseObservationPtr& response
        // ControlInterface              control
    )
          : observation_ ( observation ),
            response_ ( response )
    // control_ ( control )
    {
        ClearFlags( );
    }

    virtual ~ObservationInterface ( ) = default;

    void
        ClearFlags ( )
    {
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
    virtual uint32_t
        GetPlayerID ( ) const
    {
        return player_id_;
    }

    /*! @brief Get the current game loop for this observation.
     * @return The game loop. */
    uint32_t
        GetGameLoop ( ) const
    {
        return current_game_loop_;
    }

    Units
        GetUnits ( ) const
    {
        Units units;
        unit_pool_.ForEachExistingUnit ( [&] ( const Unit& unit ) {
            units.push_back ( &unit );
        } );
        return units;
    }

    /*! @brief Get all units belonging to self that meet the conditions provided
     * by the filter. The unit * structure is const data only. Therefore editing
     * that data will not change any in game state.
     * @see @ActionInterface for changing Unit state.
     * @param filter A functor or lambda used to filter out any unneeded units
     * in the list.
     * @return @code Units @endcode A list of units that meet the conditions
     * provided by the filter. */
    Units
        GetUnits (
            const Filter& filter
        ) const
    {
        Units units;
        unit_pool_.ForEachExistingUnit ( [&] ( const Unit& unit ) {
            if ( !filter || filter ( unit ) )
            {
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
    Units
        GetUnits (
            Unit::Alliance alliance, const Filter& filter
        ) const
    {
        Units units;
        unit_pool_.ForEachExistingUnit ( [&] ( const Unit& unit ) {
            if ( unit.alliance != alliance )
            {
                return;
            }

            if ( !filter || filter ( unit ) )
            {
                units.push_back ( &unit );
            }
        } );
        return units;
    }

    /*! Get the unit state as represented by the last call to GetObservation.
     * @param tag Unique tag of the unit.
     * @return @code Unit @endcode Pointer to the Unit object. */
    const Unit*
        GetUnit (
            Tag tag
        ) const
    {
        return unit_pool_.GetExistingUnit ( tag );
    }

    /*! @brief Gets a list of actions performed as abilities applied to units.
     * For use with the raw option.
     * @return List of raw actions. */
    const RawActions&
        GetRawActions ( ) const
    {
        return raw_actions_;
    }

    /*! @brief Gets a list of actions performed. For use with the feature layer
     * options.
     * @return List of actions. */
    const SpatialActions&
        GetFeatureLayerActions ( ) const
    {
        return feature_layer_actions_;
    }

    /*! @brief Gets a list of actions performed. For use with the rendered
     * options.
     * @return List of actions. */
    const SpatialActions&
        GetRenderedActions ( ) const
    {
        return rendered_actions_;
    }

    /*! @brief Gets new chat messages.
     * @return List of chat messages.*/
    const std::vector<ChatMessage>&
        GetChatMessages ( ) const
    {
        return chat_;
    }

    //! Gets all power sources associated with the current player.
    //! @return List of power sources.
    const std::vector<PowerSource>&
        GetPowerSources ( ) const
    {
        return power_sources_;
    }

    //! Gets all active effects in vision of the current player.
    //! @return List of effects.
    const std::vector<Effect>&
        GetEffects ( ) const
    {
        return effects_;
    }

    //! Gets all upgrades.
    //! @return List of upgrades.
    const std::vector<UpgradeID>&
        GetUpgrades ( ) const
    {
        return upgrades_;
    }

    //! Gets the detailed current set of scores.
    //! @return The current score structure.
    const Score&
        GetScore ( ) const
    {
        return score_;
    }

    /*! Gets metadata of abilities. Array can be indexed directly by AbilityID.
     * @param force_refresh Forces a full query from the game, may otherwise
     * cache data from a previous call.
     * @return @code Abilities @endcode - All abilities allowed (`available`)
     * for the current game session.
     */
    const Abilities&
        GetAbilityData (
            bool force_refresh = false
        ) const
    {
        // Checks whether function execution is required.
        if ( force_refresh || abilities_.size( ) < 1 )
        {
            abilities_cached_ = false;
        }

        // Returns the cached ability list if it already exists.
        if ( abilities_cached_ )
        {
            return abilities_;
        }

        abilities_.clear( );

        // Send a request for ability ids.
        const GameRequestPtr         request      = ProtoFace::MakeRequest( );
        SC2APIProtocol::RequestData* request_data = request->mutable_data( );
        request_data->set_ability_id ( true );

        if ( !ProtoFace::SendRequest ( request ) )
        {
            return abilities_;
        }

        const GameResponsePtr response = ProtoFace::WaitForResponse( );
        //!
        ResponseDataPtr       response_data;
        SET_MESSAGE_RESPONSE ( response_data, response, data );

        if ( response_data.HasErrors( ) ||
             response_data->abilities_size( ) == 0 )
        {
            return abilities_;
        }

        // Compress to the size of `abilities` to match its size.
        abilities_.resize ( response_data->abilities_size( ) );

        // For each ability
        for ( int i = 0; i < response_data->abilities_size( ); ++i )
        {
            AbilityData& ability_data = abilities_[i];
            ability_data.ability_id   = i;

            ability_data.ReadFromProto ( response_data->abilities ( i ) );
        }

        for ( AbilityData& ability_data : abilities_ )
        {
            if ( ability_data.remaps_to_ability_id == 0 )
                continue;

            if ( ability_data.remaps_to_ability_id >= abilities_.size( ) )
            {
                Error::Log ( ClientError::InvalidAbilityRemap );
                ability_data.remaps_to_ability_id = 0;
                continue;
            }
        }

        abilities_cached_ = true;
        return abilities_;
    }

    //! Gets metadata of units. Array can be indexed directly by UnitID.
    //! @param force_refresh forces a full query from the game, may otherwise
    //! cache data from a previous call.
    //! @return Data about all units possible for the current game session.
    const UnitTypes&
        GetUnitTypeData (
            bool force_refresh
        ) const
    {
        if ( force_refresh || unit_types_.size( ) < 1 )
        {
            unit_types_cached = false;
        }

        if ( unit_types_cached )
        {
            return unit_types_;
        }

        unit_types_.clear( );

        // Send a request for ability ids.
        GameRequestPtr               request      = ProtoFace::MakeRequest( );
        SC2APIProtocol::RequestData* request_data = request->mutable_data( );
        request_data->set_unit_type_id ( true );

        if ( !ProtoFace::SendRequest ( request ) )
        {
            return unit_types_;
        }

        GameResponsePtr response = ProtoFace::WaitForResponse( );
        ResponseDataPtr response_data;
        SET_MESSAGE_RESPONSE ( response_data, response, data );
        if ( response_data.HasErrors( ) )
        {
            return unit_types_;
        }

        if ( response_data.HasErrors( ) || response_data->units_size( ) == 0 )
        {
            return unit_types_;
        }

        unit_types_.resize ( response_data->units_size( ) );
        for ( int i = 0; i < response_data->units_size( ); ++i )
        {
            UnitTypeData& unit = unit_types_[i];
            unit.unit_type_id  = i;
            unit.ReadFromProto ( response_data->units ( i ) );
        }

        unit_types_cached = true;
        return unit_types_;
    }

    //! Gets metadata of upgrades. Array can be indexed directly by UpgradeID.
    //! @param force_refresh forces a full query from the game, may otherwise
    //! cache data from a previous call.
    //! @return Data about all upgrades possible for the current game session.
    const Upgrades&
        GetUpgradeData (
            bool force_refresh
        ) const
    {
        if ( force_refresh || upgrade_ids_.size( ) < 1 )
        {
            upgrades_cached_ = false;
        }

        if ( upgrades_cached_ )
        {
            return upgrade_ids_;
        }

        upgrade_ids_.clear( );

        GameRequestPtr               request      = ProtoFace::MakeRequest( );
        SC2APIProtocol::RequestData* request_data = request->mutable_data( );
        request_data->set_upgrade_id ( true );

        if ( !ProtoFace::SendRequest ( request ) )
        {
            return upgrade_ids_;
        }

        GameResponsePtr response = ProtoFace::WaitForResponse( );
        ResponseDataPtr response_data;
        SET_MESSAGE_RESPONSE ( response_data, response, data );
        if ( response_data.HasErrors( ) )
        {
            return upgrade_ids_;
        }

        if ( response_data.HasErrors( ) ||
             response_data->upgrades_size( ) == 0 )
        {
            return upgrade_ids_;
        }

        upgrade_ids_.resize ( response_data->upgrades_size( ) );
        for ( int i = 0; i < response_data->upgrades_size( ); ++i )
        {
            UpgradeData& upgrade = upgrade_ids_[i];
            upgrade.upgrade_id   = i;
            upgrade.ReadFromProto ( response_data->upgrades ( i ) );
        }

        upgrades_cached_ = true;
        return upgrade_ids_;
    }

    //! Gets metadata of buffs. Array can be indexed directly by BuffID.
    //! @param force_refresh forces a full query from the game, may otherwise
    //! cache data from a previous call.
    //! @return Data about all buffs possible for the current game session.
    const Buffs&
        GetBuffData (
            bool force_refresh
        ) const
    {
        if ( force_refresh || buff_ids_.size( ) < 1 )
        {
            buffs_cached_ = false;
        }

        if ( buffs_cached_ )
        {
            return buff_ids_;
        }

        buff_ids_.clear( );

        GameRequestPtr               request      = ProtoFace::MakeRequest( );
        SC2APIProtocol::RequestData* request_data = request->mutable_data( );
        request_data->set_buff_id ( true );

        if ( !ProtoFace::SendRequest ( request ) )
        {
            return buff_ids_;
        }

        GameResponsePtr response = ProtoFace::WaitForResponse( );
        ResponseDataPtr response_data;
        SET_MESSAGE_RESPONSE ( response_data, response, data );
        if ( response_data.HasErrors( ) )
        {
            return buff_ids_;
        }

        if ( response_data.HasErrors( ) || response_data->buffs_size( ) == 0 )
        {
            return buff_ids_;
        }

        buff_ids_.resize ( response_data->buffs_size( ) );
        for ( int i = 0; i < response_data->buffs_size( ); ++i )
        {
            BuffData& buff = buff_ids_[i];
            buff.buff_id   = i;
            buff.ReadFromProto ( response_data->buffs ( i ) );
        }

        buffs_cached_ = true;
        return buff_ids_;
    }

    //! Gets metadata of effects. Array can be indexed directly by EffectID.
    //! @param force_refresh forces a full query from the game, may otherwise
    //! cache data from a previous call.
    //! @return Data about all effects possible for the current game session.
    const Effects&
        GetEffectData (
            bool force_refresh
        ) const
    {
        if ( force_refresh || effect_ids_.empty( ) )
        {
            effects_cached_ = false;
        }

        if ( effects_cached_ )
        {
            return effect_ids_;
        }

        effect_ids_.clear( );

        GameRequestPtr               request      = ProtoFace::MakeRequest( );
        SC2APIProtocol::RequestData* request_data = request->mutable_data( );
        request_data->set_effect_id ( true );

        if ( !ProtoFace::SendRequest ( request ) )
        {
            return effect_ids_;
        }

        const GameResponsePtr response = ProtoFace::WaitForResponse( );
        ResponseDataPtr       response_data;
        SET_MESSAGE_RESPONSE ( response_data, response, data );
        if ( response_data.HasErrors( ) )
        {
            return effect_ids_;
        }

        if ( response_data.HasErrors( ) || response_data->effects_size( ) == 0 )
        {
            return effect_ids_;
        }

        effect_ids_.resize ( response_data->effects_size( ) );
        for ( int i = 0; i < response_data->effects_size( ); ++i )
        {
            effect_ids_[i].ReadFromProto ( response_data->effects ( i ) );
        }

        effects_cached_ = true;
        return effect_ids_;
    }

    //! Gets the GameInfo struct for the current map.
    //! @return The current GameInfo struct.
    const GameInfo&
        GetGameInfo ( ) const
    {
        if ( game_info_cached_ )
        {
            return game_info_;
        }

        GameRequestPtr request = ProtoFace::MakeRequest( );
        request->mutable_game_info( );

        if ( !ProtoFace::SendRequest ( request ) )
        {
            return game_info_;
        }

        const GameResponsePtr response = ProtoFace::WaitForResponse( );
        ResponseGameInfoPtr   response_game_info;
        SET_MESSAGE_RESPONSE ( response_game_info, response, game_info );
        if ( response_game_info.HasErrors( ) )
        {
            return game_info_;
        }

        Convert ( response_game_info, game_info_ );

        game_info_cached_ = true;
        return game_info_;
    }

    //! The mineral count of the player.
    //! @return The mineral count.
    uint32_t
        GetMinerals ( ) const
    {
        return minerals_;
    }

    //! The vespene count of the player.
    //! @return The vespene count.
    uint32_t
        GetVespene ( ) const
    {
        return vespene_;
    }

    //! The total supply cap given the players max possible supply.
    //! @return Food cap.
    //! \see GetFoodUsed() GetFoodArmy() GetFoodWorkers()
    uint32_t
        GetFoodCap ( ) const
    {
        return food_cap_;
    }

    //! The total supply used by the player as defined: GetFoodArmy() +
    //! GetFoodWorkers().
    //! @return Food used.
    //! \sa GetFoodArmy() GetFoodWorkers()
    uint32_t
        GetFoodUsed ( ) const
    {
        return food_used_;
    }

    //! The total supply consumed by army units alone.
    //! \sa GetFoodUsed() GetFoodWorkers()
    //! @return Food used by army units.
    uint32_t
        GetFoodArmy ( ) const
    {
        return food_army_;
    }

    //! The total supply consumed by workers units alone.
    //! \sa GetFoodArmy() GetFoodUsed()
    //! @return Food used by worker units.
    uint32_t
        GetFoodWorkers ( ) const
    {
        return food_workers_;
    }

    //! The number of workers that currently have no orders.
    //! @return Count of idle workers.
    uint32_t
        GetIdleWorkerCount ( ) const
    {
        return idle_worker_count_;
    }

    //! The number of army units.
    //! @return Count of army units.
    uint32_t
        GetArmyCount ( ) const
    {
        return army_count_;
    }

    //! Number of warp gates owned by the player. This value should only be
    //! nonzero for Protoss.
    //! @return Count of warp gates.
    uint32_t
        GetWarpGateCount ( ) const
    {
        return warp_gate_count_;
    }

    //! Number of larva owned by the player. This value should only be nonzero
    //! for Zerg.
    //! @return Count of larva.
    uint32_t
        GetLarvaCount ( ) const
    {
        return larva_count_;
    }

    //! Position of the center of the camera.
    //! @return Camera position.
    Point2D
        GetCameraPos ( ) const
    {
        return camera_pos_;
    }

    //! Gets the initial start location of the player.
    //! @return Player start position.
    Point3D
        GetStartLocation ( ) const
    {
        return start_location_;
    }

    //! Gets the results of the game.
    //! @return Player results if the game ended, an empty vector otherwise.
    const std::vector<PlayerResult>&
        GetResults ( ) const
    {
        return player_results_;
    }

    //! Returns 'true' if the given point has creep.
    //! @param point Position to sample.
    //! @return Creep.
    bool
        HasCreep (
            const Point2D& point
        ) const
    {
        ObservationRawPtr observation_raw;
        SET_SUBMESSAGE_RESPONSE ( observation_raw, observation_, raw_data );
        if ( observation_raw.HasErrors( ) )
        {
            return false;
        }

        return MapState ( observation_raw->map_state( ) ).HasCreep ( point );
    }

    //! Returns visibility value of the given point for the current player.
    //! @param point Position to sample.
    //! @return Visibility.
    Visibility
        GetVisibility (
            const Point2D& point
        ) const
    {
        ObservationRawPtr observation_raw;
        SET_SUBMESSAGE_RESPONSE ( observation_raw, observation_, raw_data );
        if ( observation_raw.HasErrors( ) )
        {
            return Visibility::FullHidden;
        }

        return MapState ( observation_raw->map_state( ) )
            .GetVisibility ( point );
    }

    //! Returns 'true' if the given point on the terrain is pathable. This does
    //! not
    // include pathing blockers like structures. For more accurate pathing
    // results use QueryInterface::PathingDistance.
    //! @param point Position to sample.
    //! @return Pathable.
    bool
        IsPathable (
            const Point2D& point
        ) const
    {
        return PathingGrid ( GetGameInfo( ) ).IsPathable ( point );
    }

    //! Returns 'true' if the given point on the terrain is buildable. This does
    //! not
    // include blockers like other structures. For more accurate building
    // placement results use QueryInterface::Placement.
    //! @param point Position to sample.
    //! @return Placable.
    bool
        IsPlacable (
            const Point2D& point
        ) const
    {
        return PlacementGrid ( GetGameInfo( ) ).IsPlacable ( point );
    }

    //! Returns terrain height of the given point.
    //! @param point Position to sample.
    //! @return Height.
    float
        TerrainHeight (
            const Point2D& point
        ) const
    {
        return HeightMap ( GetGameInfo( ) ).TerrainHeight ( point );
    }

    //! A pointer to the low-level protocol data for the current observation.
    //! While it's possible to extract most in-game data from this pointer
    // it is highly discouraged. It should only be used for extracting feature
    // layers because it would be inefficient to copy these each frame.
    //! @return A const pointer to the Observation.
    //! \sa Observation GetObservation()
    const SC2APIProtocol::Observation*
        GetRawObservation ( ) const
    {
        return observation_.get( );
    }

    bool
        UpdateObservation ( )
    {
        // Convert observation into data.
        if ( !Convert ( observation_, score_ ) )
        {
            return false;
        }

        uint32_t next_game_loop = observation_->game_loop( );
        bool     is_new_frame   = next_game_loop != current_game_loop_;
        previous_game_loop      = current_game_loop_;
        current_game_loop_      = next_game_loop;

        const SC2APIProtocol::PlayerCommon& player_common =
            observation_->player_common( );
        assert ( player_common.has_player_id( ) );
        if ( player_common.has_player_id( ) )
        {
            player_id_ = player_common.player_id( );
        }

        // Fill out game data.
        minerals_          = player_common.minerals( );
        vespene_           = player_common.vespene( );
        food_used_         = player_common.food_used( );
        food_cap_          = player_common.food_cap( );
        food_army_         = player_common.food_army( );
        food_workers_      = player_common.food_workers( );
        idle_worker_count_ = player_common.idle_worker_count( );
        army_count_        = player_common.army_count( );
        warp_gate_count_   = player_common.warp_gate_count( );
        larva_count_       = player_common.larva_count( );

        // Actions first, as the actions apply to the previous selection.
        if ( is_new_frame )
        {
            raw_actions_.clear( );
            feature_layer_actions_ = SpatialActions( );
            rendered_actions_      = SpatialActions( );
        }

        ConvertRawActions ( response_, raw_actions_ );
        ConvertFeatureLayerActions ( response_, feature_layer_actions_ );
        ConvertRenderedActions ( response_, rendered_actions_ );

        // Remap ability ids.
        {
            for ( ActionRaw& action : raw_actions_ )
            {
                action.ability_id =
                    GetGeneralizedAbilityID ( action.ability_id );
            }
            for ( SpatialUnitCommand& spatial_action :
                  feature_layer_actions_.unit_commands )
            {
                spatial_action.ability_id =
                    GetGeneralizedAbilityID ( spatial_action.ability_id );
            }
            for ( SpatialUnitCommand& spatial_action :
                  rendered_actions_.unit_commands )
            {
                spatial_action.ability_id =
                    GetGeneralizedAbilityID ( spatial_action.ability_id );
            }
        }

        chat_.clear( );
        for ( const auto& message : response_->chat( ) )
        {
            chat_.push_back (
                { .player_id = message.player_id( ),
                  .message   = message.message( ) }
            );
        }

        ObservationRawPtr observation_raw;
        SET_SUBMESSAGE_RESPONSE ( observation_raw, observation_, raw_data );
        if ( observation_raw.HasErrors( ) )
        {
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
        unit_pool_.ForEachExistingUnit ( [&] ( Unit& unit ) {
            for ( UnitOrder& unit_order : unit.orders )
            {
                if ( use_generalized_ability_ )
                {
                    unit_order.ability_id =
                        GetGeneralizedAbilityID ( unit_order.ability_id );
                }
            }
        } );

        effects_.clear( );
        effects_.resize ( observation_raw->effects_size( ) );
        for ( int i = 0; i < observation_raw->effects_size( ); ++i )
        {
            effects_[i].ReadFromProto ( observation_raw->effects ( i ) );
        }

        if ( !observation_raw->has_player( ) )
        {
            return false;
        }

        const SC2APIProtocol::PlayerRaw& player_raw =
            observation_raw->player( );
        if ( !player_raw.has_camera( ) )
        {
            return false;
        }

        camera_pos_.x = player_raw.camera( ).x( );
        camera_pos_.y = player_raw.camera( ).y( );

        power_sources_.clear( );
        for ( int i = 0, e = player_raw.power_sources_size( ); i < e; ++i )
        {
            const SC2APIProtocol::PowerSource& power_source =
                player_raw.power_sources ( i );
            power_sources_.push_back ( PowerSource (
                Point2D ( power_source.pos( ).x( ), power_source.pos( ).y( ) ),
                power_source.radius( ),
                power_source.tag( )
            ) );
        }

        upgrades_previous_ = upgrades_;
        upgrades_.clear( );
        for ( int i = 0; i < player_raw.upgrade_ids_size( ); ++i )
        {
            upgrades_.push_back ( player_raw.upgrade_ids ( i ) );
        }

        player_results_.clear( );
        for ( const auto& player_result : response_->player_result( ) )
        {
            player_results_.push_back ( PlayerResult (
                player_result.player_id( ),
                ConvertGameResultFromProto ( player_result.result( ) )
            ) );
        }

        return true;
    }
};

//------------------------------------------------------------------------------

// QueryInterface.

//------------------------------------------------------------------------------

//! The QueryInterface provides additional data not contained in the
//! observation.
//!
//! Performance note:
//!  - Always try and batch things up. These queries are effectively synchronous
//!  and will block until returned.
class QueryInterface
{
public:
    ObservationInterface& observation_;

    QueryInterface (
        ObservationInterface& observation
    )
          : observation_ ( observation )
    {}

    virtual ~QueryInterface ( ) = default;

    //! Returns a list of abilities represented as a uint32_t see the ABILITY_ID
    //! enum for their corresponding, named, representations.
    //! @param unit Tag of unit.
    //! @param ignore_resource_requirements Ignores food, mineral and gas
    //! costs, as well as cooldowns.
    //! @param use_generalized_ability_id e.g. if true BUILD_TECHLAB_BARRACKS,
    //! BUILD_TECHLAB_FACTORY and BUILD_TECHLAB_STARPORT ability ids are
    //! generalized to BUILD_TECHLAB @return Abilities for the unit.
    AvailableAbilities
        GetAbilitiesForUnit (
            const Unit* unit,
            bool        ignore_resource_requirements,
            bool        use_generalized_ability_id
        )
    {
        std::vector<AvailableAbilities> available_abilities =
            GetAbilitiesForUnits (
                { unit },
                ignore_resource_requirements,
                use_generalized_ability_id
            );
        if ( available_abilities.empty( ) )
            Error::Log ( ClientError::NoAbilitiesForTag );
        if ( available_abilities.empty( ) )
        {
            return { };
        }
        return available_abilities[0];
    }

    //! Issues multiple available abilities queries.
    //! Batch version.
    //! @param units Tags of units.
    //! @param ignore_resource_requirements Ignores food, mineral and gas
    //! costs, as well as cooldowns.
    //! @param use_generalized_ability_id e.g. if true BUILD_TECHLAB_BARRACKS,
    //! BUILD_TECHLAB_FACTORY and BUILD_TECHLAB_STARPORT ability ids are
    //! generalized to BUILD_TECHLAB @return Abilities for the units.
    std::vector<AvailableAbilities>
        GetAbilitiesForUnits (
            const Units& units,
            bool         ignore_resource_requirements,
            bool         use_generalized_ability_id
        )
    {
        std::vector<AvailableAbilities> available_abilities_out;

        // Make the request.
        {
            if ( units.empty( ) )
            {
                return available_abilities_out;
            }

            GameRequestPtr                request = ProtoFace::MakeRequest( );
            SC2APIProtocol::RequestQuery* query   = request->mutable_query( );
            query->set_ignore_resource_requirements (
                ignore_resource_requirements
            );
            for ( const auto unit : units )
            {
                SC2APIProtocol::RequestQueryAvailableAbilities*
                    request_abilities = query->add_abilities( );
                request_abilities->set_unit_tag ( unit->tag );
            }

            if ( !ProtoFace::SendRequest ( request ) )
            {
                return available_abilities_out;
            }
        }

        // Process the response.
        const GameResponsePtr response = ProtoFace::WaitForResponse( );
        if ( !response.get( ) )
        {
            return available_abilities_out;
        }
        if ( !response->has_query( ) )
        {
            Error::Log ( ClientError::InvalidResponse );
            return available_abilities_out;
        }
        const SC2APIProtocol::ResponseQuery& query = response->query( );
        if ( query.abilities_size( ) < 1 )
        {
            return available_abilities_out;
        }

        for ( int i = 0; i < query.abilities_size( ); ++i )
        {
            const SC2APIProtocol::ResponseQueryAvailableAbilities&
                response_query_available_abilities = query.abilities ( i );
            AvailableAbilities available_abilities_unit;
            available_abilities_unit.unit_tag =
                response_query_available_abilities.unit_tag( );
            available_abilities_unit.unit_type_id =
                response_query_available_abilities.unit_type_id( );
            if ( response_query_available_abilities.unit_tag( ) !=
                 units[i]->tag )
                Error::Log ( ClientError::ErrorSC2 );
            for ( int j = 0;
                  j < response_query_available_abilities.abilities_size( );
                  ++j )
            {
                const SC2APIProtocol::AvailableAbility& ability =
                    response_query_available_abilities.abilities ( j );
                AvailableAbility available_ability;
                if ( use_generalized_ability_id )
                {
                    available_ability.ability_id = GetGeneralizedAbilityID (
                        static_cast<ABILITY_ID> ( ability.ability_id( ) )
                    );
                } else
                {
                    available_ability.ability_id = ability.ability_id( );
                }

                available_ability.requires_point = ability.requires_point( );
                available_abilities_unit.abilities.push_back (
                    available_ability
                );
            }

            available_abilities_out.push_back ( available_abilities_unit );
        }

        return available_abilities_out;
    }

    struct PathingQuery
    {
        Tag     start_unit_tag_ = NullTag;
        Point2D start_;
        Point2D end_;
    };

    //! Returns pathing distance between two locations. Takes into account unit
    //! movement properties (e.g. Flying).
    //! @param start Starting point.
    //! @param end End point.
    //! @return Distance between the two points.
    float
        PathingDistance (
            const Point2D& start, const Point2D& end
        )
    {
        std::vector<PathingQuery> queries;

        PathingQuery query;
        query.start_ = start;
        query.end_   = end;
        queries.push_back ( query );

        std::vector<float> distances = PathingDistance ( queries );
        return distances[0];
    }

    //! Returns pathing distance between a unit and a target location. Takes
    //! into account unit movement properties (e.g. Flying). Batch version.
    //! @param start_unit Starting points.
    //! @param end End points.
    //! @return Distances between the two points.
    float
        PathingDistance (
            const Unit* start_unit, const Point2D& end
        )
    {
        std::vector<PathingQuery> queries;

        PathingQuery query;
        query.start_unit_tag_ = start_unit->tag;
        query.end_            = end;
        queries.push_back ( query );

        std::vector<float> distances = PathingDistance ( queries );
        return distances[0];
    }

    //! Issues multiple pathing queries.
    std::vector<float>
        PathingDistance (
            const std::vector<PathingQuery>& queries
        )
    {
        GameRequestPtr                request       = ProtoFace::MakeRequest( );
        SC2APIProtocol::RequestQuery* request_query = request->mutable_query( );

        for ( const PathingQuery& query : queries )
        {
            SC2APIProtocol::RequestQueryPathing* pathing_query =
                request_query->add_pathing( );
            if ( query.start_unit_tag_ )
            {
                pathing_query->set_unit_tag ( query.start_unit_tag_ );
            } else
            {
                SC2APIProtocol::Point2D* startPos =
                    pathing_query->mutable_start_pos( );
                startPos->set_x ( query.start_.x );
                startPos->set_y ( query.start_.y );
            }
            SC2APIProtocol::Point2D* endPos = pathing_query->mutable_end_pos( );
            endPos->set_x ( query.end_.x );
            endPos->set_y ( query.end_.y );
        }

        if ( !ProtoFace::SendRequest ( request ) )
        {
            return std::vector<float> ( queries.size( ), 0.0f );
        }

        const GameResponsePtr response = ProtoFace::WaitForResponse( );
        ResponseQueryPtr      response_query;
        SET_MESSAGE_RESPONSE ( response_query, response, query );
        if ( response_query.HasErrors( ) )
        {
            return std::vector<float> ( queries.size( ), 0.0f );
        }

        if ( response_query->pathing_size( ) != queries.size( ) )
        {
            return std::vector<float> ( queries.size( ), 0.0f );
        }

        std::vector<float> distances;
        distances.reserve ( queries.size( ) );

        for ( int i = 0; i < response_query->pathing_size( ); ++i )
        {
            const SC2APIProtocol::ResponseQueryPathing& result =
                response_query->pathing ( i );
            distances.push_back ( result.distance( ) );
        }

        return distances;
    }

    struct PlacementQuery
    {
        PlacementQuery ( ) = default;

        PlacementQuery (
            AbilityID ability_id, Point2D target
        )
              : ability ( ability_id ),
                target_pos ( target )
        {}

        AbilityID ability;
        Point2D   target_pos;
        //! Optional. Used for testing placement with add-ons.
        Tag       placing_unit_tag = 0ll;
    };

    /*! @brief Returns whether a building can be placed at a location.
     * @param ability Ability for building or moving a structure.
     * @param target_pos Position to attempt placement on.
     * @param unit (Optional) This is only used for cases where the placing unit
     * plays a role in the placement grid test (e.g. A flying barracks building
     * an add-on requires room for both the barracks and add-on).
     * @return If placement is possible. */
    bool
        Placement (
            const AbilityID& ability,
            const Point2D&   target_pos,
            const Unit*      unit = nullptr
        ) const
    {
        std::vector<PlacementQuery> queries;

        PlacementQuery query;
        query.ability          = ability;
        query.target_pos       = target_pos;
        query.placing_unit_tag = unit ? unit->tag : NullTag;
        queries.push_back ( query );

        std::vector<bool> results = Placement ( queries );
        return results[0];
    }

    //! A batch version of the above Placement query. Takes an array of
    //! abilities, positions and optional unit tags and returns a matching array
    //! of bools indicating if placement is possible.
    //! @param queries Placement queries.
    //! @return Array of bools indicating if placement is possible.
    std::vector<bool>
        Placement (
            const std::vector<PlacementQuery>& queries
        ) const
    {
        GameRequestPtr                request       = ProtoFace::MakeRequest( );
        SC2APIProtocol::RequestQuery* request_query = request->mutable_query( );

        for ( const PlacementQuery& query : queries )
        {
            SC2APIProtocol::RequestQueryBuildingPlacement* placement_query =
                request_query->add_placements( );

            placement_query->set_placing_unit_tag ( query.placing_unit_tag );
            placement_query->set_ability_id ( query.ability );

            SC2APIProtocol::Point2D* target =
                placement_query->mutable_target_pos( );
            target->set_x ( query.target_pos.x );
            target->set_y ( query.target_pos.y );
        }

        if ( !ProtoFace::SendRequest ( request ) )
        {
            return std::vector<bool> ( queries.size( ), false );
        }

        const GameResponsePtr response = ProtoFace::WaitForResponse( );
        ResponseQueryPtr      response_query;
        SET_MESSAGE_RESPONSE ( response_query, response, query );
        if ( response_query.HasErrors( ) )
        {
            return std::vector<bool> ( queries.size( ), false );
        }

        if ( response_query->placements_size( ) != queries.size( ) )
        {
            return std::vector<bool> ( queries.size( ), false );
        }

        std::vector<bool> results;
        results.reserve ( queries.size( ) );

        for ( int i = 0; i < response_query->placements_size( ); ++i )
        {
            const SC2APIProtocol::ResponseQueryBuildingPlacement& result =
                response_query->placements ( i );
            results.push_back (
                result.result( ) == SC2APIProtocol::ActionResult::Success
            );
        }

        return results;
    }
};

//------------------------------------------------------------------------------

// DebugInterface.

//------------------------------------------------------------------------------

//! DebugInterface draws debug text, lines and shapes. Available at any time
//! after the game starts. Guaranteed to be valid when the OnStep event is
//! called. All debug actions are queued and dispatched when SendDebug is
//! called. All drawn primitives continue to draw without resending until
//! another SendDebug is called.
class DebugInterface
{
public:
    ObservationInterface& observation_;

    // Debug display.

    struct DebugText
    {
        string   text;
        bool     has_coords;
        bool     is_3d;
        Point3D  pt;
        Color    color;
        uint32_t size = 0;
    };

    vector<DebugText> debug_text_;

    struct DebugLine
    {
        Point3D p0;
        Point3D p1;
        Color   color;
    };

    std::vector<DebugLine> debug_line_;

    struct DebugBox
    {
        Point3D p_min;
        Point3D p_max;
        Color   color;
    };

    std::vector<DebugBox> debug_box_;

    struct DebugSphere
    {
        Point3D p_;
        float   r_;
        Color   color_;
    };

    std::vector<DebugSphere> debug_sphere_;

    std::vector<SC2APIProtocol::DebugGameState> debug_state_;

    struct DebugSetUnitValue
    {
        enum class UnitValue { Energy, Life, Shields };
        UnitValue unit_value;
        float     value;
        Tag       tag;
    };

    std::vector<DebugSetUnitValue> debug_unit_values_;

    struct DebugUnit
    {
        UnitTypeID unit_type;
        Point2D    pos;
        uint32_t   player_id;
        uint32_t   count;
    };

    std::vector<DebugUnit> debug_unit_;

    Tags debug_kill_tag_;

    bool    has_move_camera { false };
    Point2D debug_move_camera_;

    bool    app_test_set_ { false };
    AppTest app_test_ { };
    int     app_test_delay_ms_ { 0 };
    bool    endgame_surrender_ { false };
    bool    endgame_victory_ { false };
    bool    set_score_ { false };
    float   score_ { 0.0f };

    DebugInterface (
        ObservationInterface& observation
    )
          : observation_ ( observation )
    // control_ ( control )
    {}

    virtual ~DebugInterface ( ) = default;

    // Debug drawing primitives.

    //! Outputs text at the top, left of the screen.
    //! @param out The string of text to display.
    //! @param color (Optional) Color of the text.
    void
        DebugTextOut (
            const std::string& out, Color color = White
        )
    {
        DebugText debug_text;
        debug_text.text       = out;
        debug_text.has_coords = false;
        debug_text.color      = color;
        debug_text_.push_back ( debug_text );
    }

    //! Outputs text at any 2D point on the screen. Coordinate ranges are 0..1
    //! in X and Y.
    //! @param out The string of text to display.
    //! @param pt_virtual_2D The screen position to draw text at.
    //! @param color (Optional) Color of the text.
    //! @param size (Optional) Pixel height of the text.
    void
        DebugTextOut (
            const std::string& out,
            const Point2D&     pt_virtual_2D,
            Color              color = White,
            uint32_t           size  = 8
        )
    {
        DebugText debug_text;
        debug_text.text       = out;
        debug_text.has_coords = true;
        debug_text.is_3d      = false;
        debug_text.pt.x       = pt_virtual_2D.x;
        debug_text.pt.y       = pt_virtual_2D.y;
        debug_text.color      = color;
        debug_text.size       = size;
        debug_text_.push_back ( debug_text );
    }

    //! Outputs text at any 3D point in the game world. Map coordinates are
    //! used.
    //! @param out The string of text to display.
    //! @param pt3D The world position to draw text at.
    //! @param color (Optional) Color of the text.
    //! @param size (Optional) Pixel height of the text.
    void
        DebugTextOut (
            const std::string& out,
            const Point3D&     pt3D,
            Color              color = White,
            uint32_t           size  = 8
        )
    {
        DebugText debug_text;
        debug_text.text       = out;
        debug_text.has_coords = true;
        debug_text.is_3d      = true;
        debug_text.pt.x       = pt3D.x;
        debug_text.pt.y       = pt3D.y;
        debug_text.pt.z       = pt3D.z;
        debug_text.color      = color;
        debug_text.size       = size;
        debug_text_.push_back ( debug_text );
    }

    //! Outputs a line between two 3D points in the game world. Map coordinates
    //! are used.
    //! @param p0 The starting position of the line.
    //! @param p1 The ending position of the line.
    //! @param color (Optional) Color of the line.
    void
        DebugLineOut (
            const Point3D& p0, const Point3D& p1, Color color = White
        )
    {
        DebugLine line;
        line.p0    = p0;
        line.p1    = p1;
        line.color = color;
        debug_line_.push_back ( line );
    }

    //! Outputs a box specified as two 3D points in the game world. Map
    //! coordinates are used.
    //! @param p_min One corner of the box.
    //! @param p_max The far corner of the box.
    //! @param color (Optional) Color of the lines.
    void
        DebugBoxOut (
            const Point3D& p_min, const Point3D& p_max, Color color = White
        )
    {
        DebugBox box;
        box.p_min = p_min;
        box.p_max = p_max;
        box.color = color;
        debug_box_.push_back ( box );
    }

    //! Outputs a sphere specified as a 3D point in the game world and a radius.
    //! Map coordinates are used.
    //! @param p Center of the sphere.
    //! @param r Radius of the sphere.
    //! @param color (Optional) Color of the lines.
    void
        DebugSphereOut (
            const Point3D& p, float r, Color color = White
        )
    {
        DebugSphere sphere;
        sphere.p_     = p;
        sphere.r_     = r;
        sphere.color_ = color;
        debug_sphere_.push_back ( sphere );
    }

    // Cheats.

    //! Creates a unit at the given position.
    //! @param unit_type Type of unit to create.
    //! @param p Position to create the unit at.
    //! @param player_id Player the unit should belong to.
    //! @param count Number of units to create.
    void
        DebugCreateUnit (
            UnitTypeID     unit_type,
            const Point2D& p,
            uint32_t       player_id = 1,
            uint32_t       count     = 1
        )
    {
        DebugUnit create_unit;
        create_unit.unit_type = unit_type;
        create_unit.pos       = p;
        create_unit.player_id = player_id = 1;
        create_unit.count = count = 1;
        debug_unit_.push_back ( create_unit );
    }

    //! Destroy a unit.
    //! @param unit Unit to destroy.
    void
        DebugKillUnit (
            const Unit* unit
        )
    {
        if ( !unit )
        {
            return;
        }
        debug_kill_tag_.push_back ( unit->tag );
    }

    //! Makes the entire map visible, i.e., removes the fog-of-war.
    void
        DebugShowMap ( )
    {
        debug_state_.push_back ( SC2APIProtocol::DebugGameState::show_map );
    }

    //! Enables commands to be issued to enemy units.
    void
        DebugEnemyControl ( )
    {
        debug_state_.push_back (
            SC2APIProtocol::DebugGameState::control_enemy
        );
    }

    //! Disables the food check.
    void
        DebugIgnoreFood ( )
    {
        debug_state_.push_back ( SC2APIProtocol::DebugGameState::food );
    }

    //! Disables resource checks.
    void
        DebugIgnoreResourceCost ( )
    {
        debug_state_.push_back ( SC2APIProtocol::DebugGameState::free );
    }

    //! Gives a bunch of minerals and gas.
    void
        DebugGiveAllResources ( )
    {
        debug_state_.push_back (
            SC2APIProtocol::DebugGameState::all_resources
        );
    }

    //! Makes the units of a player indestructible.
    void
        DebugGodMode ( )
    {
        debug_state_.push_back ( SC2APIProtocol::DebugGameState::god );
    }

    //! Ignores mineral costs.
    void
        DebugIgnoreMineral ( )
    {
        debug_state_.push_back ( SC2APIProtocol::DebugGameState::minerals );
    }

    //! Ignores gas costs.
    void
        DebugIgnoreGas ( )
    {
        debug_state_.push_back ( SC2APIProtocol::DebugGameState::gas );
    }

    //! Cooldowns become instant.
    void
        DebugNoCooldowns ( )
    {
        debug_state_.push_back ( SC2APIProtocol::DebugGameState::cooldown );
    }

    //! All tech becomes available.
    void
        DebugGiveAllTech ( )
    {
        debug_state_.push_back ( SC2APIProtocol::DebugGameState::tech_tree );
    }

    //! All upgrades are available.
    void
        DebugGiveAllUpgrades ( )
    {
        debug_state_.push_back ( SC2APIProtocol::DebugGameState::upgrade );
    }

    //! Structures and units are built much faster.
    void
        DebugFastBuild ( )
    {
        debug_state_.push_back ( SC2APIProtocol::DebugGameState::fast_build );
    }

    //! Sets the scripted "curriculum" score.
    void
        DebugSetScore (
            float score
        )
    {
        set_score_ = true;
        score_     = score;
    }

    //! Ends a game.
    //! @param victory If true, this player is victorious. If false, this
    //! player surrenders.
    void
        DebugEndGame (
            bool victory
        )
    {
        if ( victory )
        {
            endgame_surrender_ = false;
            endgame_victory_   = true;
        } else
        {
            endgame_surrender_ = true;
            endgame_victory_   = false;
        }
    }

    //! Sets the energy level on a unit.
    //! @param value The new energy level.
    //! @param unit The unit.
    // TODO allow percentage
    void
        DebugSetEnergy (
            float value, const Unit* unit
        )
    {
        if ( !unit )
        {
            return;
        }
        DebugSetUnitValue unit_value;
        unit_value.unit_value = DebugSetUnitValue::UnitValue::Energy;
        unit_value.value      = value;
        unit_value.tag        = unit->tag;
        debug_unit_values_.push_back ( unit_value );
    }

    //! Sets the life on a unit.
    //! @param value The new life value.
    //! @param unit The unit.
    // TODO allow percentage
    void
        DebugSetLife (
            float value, const Unit* unit
        )
    {
        if ( !unit )
        {
            return;
        }
        DebugSetUnitValue unit_value;
        unit_value.unit_value = DebugSetUnitValue::UnitValue::Life;
        unit_value.value      = value;
        unit_value.tag        = unit->tag;
        debug_unit_values_.push_back ( unit_value );
    }

    //! Sets shields on a unit.
    //! @param value The new shields.
    //! @param unit The unit.
    // TODO allow percentage
    void
        DebugSetShields (
            float value, const Unit* unit
        )
    {
        if ( !unit )
        {
            return;
        }
        DebugSetUnitValue unit_value;
        unit_value.unit_value = DebugSetUnitValue::UnitValue::Shields;
        unit_value.value      = value;
        unit_value.tag        = unit->tag;
        debug_unit_values_.push_back ( unit_value );
    }

    //! Sets the position of the camera.
    //! @param pos The camera position in world space.
    void
        DebugMoveCamera (
            const Point2D& pos
        )
    {
        has_move_camera    = true;
        debug_move_camera_ = pos;
    }

    enum class AppTest { hang = 1, crash = 2, exit = 3 };

    //! @brief Cause the game to fail; useful to test library behavior.
    //! @param app_test State to put the game into.
    //! @param delay_ms Time to elapse before invoking the game state.
    void
        DebugTestApp (
            ::AppTest app_test, int delay_ms = 0
        )
    {
        app_test_set_      = true;
        app_test_          = app_test;
        app_test_delay_ms_ = delay_ms;
    }

    //! Dispatch all queued debug commands. No debug commands will be sent until
    //! this is called. This will also clear or set new debug primitives like
    //! text and lines.
    void
        SendDebug ( )
    {
        GameRequestPtr                request       = ProtoFace::MakeRequest( );
        SC2APIProtocol::RequestDebug* request_debug = request->mutable_debug( );

        for ( const DebugText& entry : debug_text_ )
        {
            SC2APIProtocol::DebugCommand* command = request_debug->add_debug( );
            SC2APIProtocol::DebugText*    debug_text =
                command->mutable_draw( )->add_text( );
            debug_text->set_text ( entry.text );
            debug_text->set_size ( entry.size );
            if ( entry.has_coords )
            {
                if ( entry.is_3d )
                {
                    SC2APIProtocol::Point* pos =
                        debug_text->mutable_world_pos( );
                    pos->set_x ( entry.pt.x );
                    pos->set_y ( entry.pt.y );
                    pos->set_z ( entry.pt.z );
                } else
                {
                    SC2APIProtocol::Point* pos =
                        debug_text->mutable_virtual_pos( );
                    pos->set_x ( entry.pt.x );
                    pos->set_y ( entry.pt.y );
                }
            }
            SC2APIProtocol::Color* color_text = debug_text->mutable_color( );
            color_text->set_r ( entry.color.R );
            color_text->set_g ( entry.color.G );
            color_text->set_b ( entry.color.B );
        }

        for ( const DebugLine& line : debug_line_ )
        {
            SC2APIProtocol::DebugCommand* command = request_debug->add_debug( );
            SC2APIProtocol::DebugLine*    debug_line =
                command->mutable_draw( )->add_lines( );
            SC2APIProtocol::Line* proto_line = debug_line->mutable_line( );

            SC2APIProtocol::Point* p0 = proto_line->mutable_p0( );
            p0->set_x ( line.p0.x );
            p0->set_y ( line.p0.y );
            p0->set_z ( line.p0.z );

            SC2APIProtocol::Point* p1 = proto_line->mutable_p1( );
            p1->set_x ( line.p1.x );
            p1->set_y ( line.p1.y );
            p1->set_z ( line.p1.z );

            SC2APIProtocol::Color* color_line = debug_line->mutable_color( );
            color_line->set_r ( line.color.R );
            color_line->set_g ( line.color.G );
            color_line->set_b ( line.color.B );
        }

        for ( const DebugBox& box : debug_box_ )
        {
            SC2APIProtocol::DebugCommand* command = request_debug->add_debug( );
            SC2APIProtocol::DebugBox*     debug_box =
                command->mutable_draw( )->add_boxes( );

            SC2APIProtocol::Point* p_min = debug_box->mutable_min( );
            p_min->set_x ( box.p_min.x );
            p_min->set_y ( box.p_min.y );
            p_min->set_z ( box.p_min.z );

            SC2APIProtocol::Point* p_max = debug_box->mutable_max( );
            p_max->set_x ( box.p_max.x );
            p_max->set_y ( box.p_max.y );
            p_max->set_z ( box.p_max.z );

            SC2APIProtocol::Color* color_box = debug_box->mutable_color( );
            color_box->set_r ( box.color.R );
            color_box->set_g ( box.color.G );
            color_box->set_b ( box.color.B );
        }

        for ( const DebugSphere& sphere : debug_sphere_ )
        {
            SC2APIProtocol::DebugCommand* command = request_debug->add_debug( );
            SC2APIProtocol::DebugSphere*  debug_sphere =
                command->mutable_draw( )->add_spheres( );

            SC2APIProtocol::Point* p = debug_sphere->mutable_p( );
            p->set_x ( sphere.p_.x );
            p->set_y ( sphere.p_.y );
            p->set_z ( sphere.p_.z );

            debug_sphere->set_r ( sphere.r_ );

            SC2APIProtocol::Color* color_sphere =
                debug_sphere->mutable_color( );
            color_sphere->set_r ( sphere.color_.R );
            color_sphere->set_g ( sphere.color_.G );
            color_sphere->set_b ( sphere.color_.B );
        }

        for ( const DebugSetUnitValue& set_unit_value : debug_unit_values_ )
        {
            SC2APIProtocol::DebugCommand* command = request_debug->add_debug( );
            SC2APIProtocol::DebugSetUnitValue* unit_value =
                command->mutable_unit_value( );
            switch ( set_unit_value.unit_value )
            {
                case DebugSetUnitValue::UnitValue::Energy :
                    unit_value->set_unit_value (
                        SC2APIProtocol::DebugSetUnitValue_UnitValue_Energy
                    );
                    break;
                case DebugSetUnitValue::UnitValue::Life :
                    unit_value->set_unit_value (
                        SC2APIProtocol::DebugSetUnitValue_UnitValue_Life
                    );
                    break;
                case DebugSetUnitValue::UnitValue::Shields :
                    unit_value->set_unit_value (
                        SC2APIProtocol::DebugSetUnitValue_UnitValue_Shields
                    );
                    break;
            }
            unit_value->set_value ( set_unit_value.value );
            unit_value->set_unit_tag ( set_unit_value.tag );
        }

        for ( const SC2APIProtocol::DebugGameState& state : debug_state_ )
        {
            SC2APIProtocol::DebugCommand* command = request_debug->add_debug( );
            command->set_game_state ( state );
        }

        for ( const DebugUnit& unit : debug_unit_ )
        {
            if ( unit.count < 1 )
            {
                continue;
            }

            SC2APIProtocol::DebugCommand* command = request_debug->add_debug( );
            SC2APIProtocol::DebugCreateUnit* create_unit =
                command->mutable_create_unit( );
            create_unit->set_unit_type ( unit.unit_type );
            create_unit->set_owner ( unit.player_id );
            SC2APIProtocol::Point2D* pt = create_unit->mutable_pos( );
            pt->set_x ( unit.pos.x );
            pt->set_y ( unit.pos.y );
            create_unit->set_quantity ( unit.count );
        }

        if ( !debug_kill_tag_.empty( ) )
        {
            SC2APIProtocol::DebugCommand* command = request_debug->add_debug( );
            SC2APIProtocol::DebugKillUnit* debug_kill_unit =
                command->mutable_kill_unit( );
            for ( auto tag : debug_kill_tag_ )
            {
                debug_kill_unit->add_tag ( tag );
            }
        }

        if ( app_test_set_ )
        {
            SC2APIProtocol::DebugCommand* command = request_debug->add_debug( );
            SC2APIProtocol::DebugTestProcess* test_process =
                command->mutable_test_process( );
            test_process->set_test (
                static_cast<SC2APIProtocol::DebugTestProcess_Test> ( app_test_ )
            );
            test_process->set_delay_ms ( app_test_delay_ms_ );
        }

        if ( set_score_ )
        {
            SC2APIProtocol::DebugCommand* command = request_debug->add_debug( );
            SC2APIProtocol::DebugSetScore* set_score =
                command->mutable_score( );
            set_score->set_score ( score_ );
        }
        set_score_ = false;
        score_     = 0.0f;

        if ( endgame_surrender_ )
        {
            SC2APIProtocol::DebugCommand* command = request_debug->add_debug( );
            SC2APIProtocol::DebugEndGame* end_game =
                command->mutable_end_game( );
            end_game->set_end_result (
                SC2APIProtocol::DebugEndGame_EndResult_Surrender
            );
        }
        endgame_surrender_ = false;

        if ( endgame_victory_ )
        {
            SC2APIProtocol::DebugCommand* command = request_debug->add_debug( );
            SC2APIProtocol::DebugEndGame* end_game =
                command->mutable_end_game( );
            end_game->set_end_result (
                SC2APIProtocol::DebugEndGame_EndResult_DeclareVictory
            );
        }
        endgame_victory_ = false;

        ProtoFace::SendRequest ( request );
        debug_text_.clear( );
        debug_line_.clear( );
        debug_box_.clear( );
        debug_sphere_.clear( );

        debug_state_.clear( );
        debug_unit_.clear( );
        debug_kill_tag_.clear( );
        debug_unit_values_.clear( );

        // Wait for the response.
        ProtoFace::WaitForResponse( );

        if ( has_move_camera )
        {
            GameRequestPtr camera_request = ProtoFace::MakeRequest( );
            SC2APIProtocol::RequestAction* request_action =
                camera_request->mutable_action( );
            SC2APIProtocol::Action*    action = request_action->add_actions( );
            SC2APIProtocol::ActionRaw* action_raw =
                action->mutable_action_raw( );
            SC2APIProtocol::ActionRawCameraMove* camera_move =
                action_raw->mutable_camera_move( );

            SC2APIProtocol::Point* point =
                camera_move->mutable_center_world_space( );
            point->set_x ( debug_move_camera_.x );
            point->set_y ( debug_move_camera_.y );

            has_move_camera = false;
            ProtoFace::SendRequest ( camera_request );
            ProtoFace::WaitForResponse( );
        }
    }
};

//------------------------------------------------------------------------------

// ControlInterface.

//------------------------------------------------------------------------------

// Advanced Forward Declaration
class Client {
public:
    Client();
private:
    //! Pointer to the control interface.
    ControlInterface* ctrl_face_{nullptr};
};

class ControlInterface
{
public:
    Client* client_;

    bool is_multiplayer_ { false };

    // Observation from last step.
    ObservationPtr         observation_;
    ResponseObservationPtr response_;

    std::unique_ptr<ObservationInterface> observation_face_ { nullptr };
    std::unique_ptr<QueryInterface>       query_face_ { nullptr };
    std::unique_ptr<DebugInterface>       debug_face_ { nullptr };
    // ProcessInfo                           pi_;

    // Errors that may have occurred during calls to the various interfaces.
    std::vector<ClientError> client_errors_;
    std::vector<std::string> protocol_errors_;

    std::mutex error_mutex_;

    explicit ControlInterface ( Client* client )
          : client_ ( client )
    {
        observation_face_ =
            std::make_unique<ObservationInterface> ( observation_, response_ );
        query_face_ = std::make_unique<QueryInterface> ( *observation_face_ );
        debug_face_ = std::make_unique<DebugInterface> ( *observation_face_ );
    }

    // explicit ControlInterface (const ::sc2::Client& client );

    virtual ~ControlInterface ( )
    {
        ProtoFace::Quit( );
    }

    virtual bool
        Connect (
            const std::string& address, int port, int timeout_ms
        )
    {
        // Keep retrying the connection until the timeout is hit.
        bool         connected = false;
        unsigned int timeout_seconds =
            ( static_cast<unsigned int> ( timeout_ms ) + 1500 ) / 1000;
        if ( timeout_seconds < 1 )
        {
            timeout_seconds = 1;
        }

        std::cout << "Connecting to " << address << ":" << port << "...\n";

        for ( unsigned int count_seconds = 0; count_seconds < timeout_seconds;
              ++count_seconds )
        {
            if ( ProtoFace::ConnectToGame ( address, port, timeout_ms ) )
            {
                connected = true;
                break;
            }
            SleepFor ( 1000 );
        }

        if ( !connected )
        {
            std::cerr << "Unable to connect to game\n";
            return false;
        }

        std::cout << "Connected to " << address << ":" << port << std::endl;

        return true;
    }

    virtual bool
        RemoteSaveMap (
            const void* data, int data_size, std::string remote_path
        )
    {
        // Request.
        {
            GameRequestPtr                  request = ProtoFace::MakeRequest( );
            SC2APIProtocol::RequestSaveMap* request_save_map =
                request->mutable_save_map( );
            request_save_map->set_map_path ( remote_path );
            request_save_map->set_map_data ( data, data_size );

            if ( !ProtoFace::SendRequest ( request ) )
            {
                return false;
            }
        }

        // Response.
        const GameResponsePtr response = WaitForResponse( );
        if ( !response.get( ) )
        {
            return false;
        }

        if ( !response->has_save_map( ) )
        {
            std::cerr << "Error in ResponseSaveMap" << std::endl;
            return false;
        }
        const SC2APIProtocol::ResponseSaveMap& response_save_game =
            response->save_map( );

        bool success = true;
        if ( response_save_game.has_error( ) )
        {
            success               = false;
            std::string errorCode = "Unknown";
            switch ( response_save_game.error( ) )
            {
                case SC2APIProtocol::ResponseSaveMap::InvalidMapData : {
                    errorCode = "Invalid Map Data";
                    break;
                }
                default : {
                    break;
                }
            }
        }

        return success;
    }

    virtual bool
        CreateGame (
            const std::string&              map_name,
            const std::vector<PlayerSetup>& players,
            bool                            realtime
        )
    {
        GameRequestPtr                     request = ProtoFace::MakeRequest( );
        SC2APIProtocol::RequestCreateGame* request_create_game =
            request->mutable_create_game( );
        ResolveMap ( map_name, request_create_game );
        for ( const PlayerSetup& setup : players )
        {
            SC2APIProtocol::PlayerSetup* playerSetup =
                request_create_game->add_player_setup( );
            playerSetup->set_type (
                static_cast<SC2APIProtocol::PlayerType> ( setup.type )
            );
            playerSetup->set_race (
                static_cast<SC2APIProtocol::Race> (
                    static_cast<int> ( setup.race ) + 1
                )
            );
            playerSetup->set_player_name ( setup.player_name );
            playerSetup->set_difficulty (
                static_cast<SC2APIProtocol::Difficulty> ( setup.difficulty )
            );
            playerSetup->set_ai_build (
                static_cast<SC2APIProtocol::AIBuild> ( setup.ai_build )
            );
        }

        request_create_game->set_realtime ( realtime );

        if ( !ProtoFace::SendRequest ( request ) )
        {
            return false;
        }

        const GameResponsePtr response = WaitForResponse( );
        if ( !response.get( ) )
        {
            return false;
        }

        if ( !response->has_create_game( ) )
        {
            std::cerr << "Error in ResponseCreateGame" << std::endl;
            return false;
        }

        const SC2APIProtocol::ResponseCreateGame& response_create_game =
            response->create_game( );

        bool success { true };
        if ( response_create_game.has_error( ) )
        {
            std::string errorCode;
            switch ( response_create_game.error( ) )
            {
                case SC2APIProtocol::ResponseCreateGame::MissingMap : {
                    errorCode = "Missing Map";
                    break;
                }
                case SC2APIProtocol::ResponseCreateGame::InvalidMapPath : {
                    errorCode = "Invalid Map Path";
                    break;
                }
                case SC2APIProtocol::ResponseCreateGame::InvalidMapData : {
                    errorCode = "Invalid Map Data";
                    break;
                }
                case SC2APIProtocol::ResponseCreateGame::InvalidMapName : {
                    errorCode = "Invalid Map Name";
                    break;
                }
                case SC2APIProtocol::ResponseCreateGame::InvalidMapHandle : {
                    errorCode = "Invalid Map Handle";
                    break;
                }
                case SC2APIProtocol::ResponseCreateGame::MissingPlayerSetup : {
                    errorCode = "Missing Player Setup";
                    break;
                }
                case SC2APIProtocol::ResponseCreateGame::InvalidPlayerSetup : {
                    errorCode = "Invalid Player Setup";
                    break;
                }
                default :
                    errorCode = "Unknown";
                    {
                        break;
                    }
            }

            std::cerr << "CreateGame request returned an error code: "
                      << errorCode << std::endl;
            success = false;
        }

        if ( response_create_game.has_error_details( ) &&
             response_create_game.error_details( ).length( ) > 0 )
        {
            std::cerr << "CreateGame request returned error details: "
                      << response_create_game.error_details( ) << std::endl;
            success = false;
        }

        return success;
    }

    virtual bool
        RequestJoinGame (
            PlayerSetup              setup,
            const InterfaceSettings& settings,
            const Ports&             ports,
            bool                     raw_affects_selection
        )
    {
        observation_face_->ClearFlags( );

        is_multiplayer_ = ports.IsValid( );

        GameRequestPtr                   request = ProtoFace::MakeRequest( );
        SC2APIProtocol::RequestJoinGame* request_join_game =
            request->mutable_join_game( );

        request_join_game->set_race (
            static_cast<SC2APIProtocol::Race> (
                static_cast<int> ( setup.race ) + 1
            )
        );
        request_join_game->set_player_name ( setup.player_name );

        if ( is_multiplayer_ )
        {
            // Set shared port.
            request_join_game->set_shared_port ( ports.shared_port );

            // Set server ports.
            SC2APIProtocol::PortSet* server_ports =
                request_join_game->mutable_server_ports( );
            server_ports->set_game_port ( ports.server_ports.game_port );
            server_ports->set_base_port ( ports.server_ports.base_port );

            // Set client ports. Right now only 1v1 is supported.
            for ( const PortSet& client_ports : ports.client_ports )
            {
                SC2APIProtocol::PortSet* client_port =
                    request_join_game->add_client_ports( );
                client_port->set_game_port ( client_ports.game_port );
                client_port->set_base_port ( client_ports.base_port );
            }
        }

        SC2APIProtocol::InterfaceOptions* options =
            request_join_game->mutable_options( );

        options->set_raw ( true );
        options->set_score ( true );
        options->set_show_cloaked ( true );
        options->set_show_burrowed_shadows ( true );
        options->set_show_placeholders ( true );

        // If raw_affects_selection == true, will not generate a deselect
        // command after sending a command to a unit
        options->set_raw_affects_selection ( raw_affects_selection );

        if ( settings.use_feature_layers )
        {
            SC2APIProtocol::SpatialCameraSetup* setupProto =
                options->mutable_feature_layer( );
            setupProto->set_width (
                settings.feature_layer_settings.camera_width
            );
            SC2APIProtocol::Size2DI* resolution =
                setupProto->mutable_resolution( );
            resolution->set_x ( settings.feature_layer_settings.map_x );
            resolution->set_y ( settings.feature_layer_settings.map_y );
            SC2APIProtocol::Size2DI* minimap_resolution =
                setupProto->mutable_minimap_resolution( );
            minimap_resolution->set_x (
                settings.feature_layer_settings.minimap_x
            );
            minimap_resolution->set_y (
                settings.feature_layer_settings.minimap_y
            );
        }
        if ( settings.use_render )
        {
            SC2APIProtocol::SpatialCameraSetup* setupProto =
                options->mutable_render( );
            SC2APIProtocol::Size2DI* resolution =
                setupProto->mutable_resolution( );
            resolution->set_x ( settings.render_settings.map_x );
            resolution->set_y ( settings.render_settings.map_y );
            SC2APIProtocol::Size2DI* minimap_resolution =
                setupProto->mutable_minimap_resolution( );
            minimap_resolution->set_x ( settings.render_settings.minimap_x );
            minimap_resolution->set_y ( settings.render_settings.minimap_y );
        }

        return ProtoFace::SendRequest ( request );
    }

    virtual bool
        WaitJoinGame ( )
    {
        std::cout << "Waiting for the JoinGame response." << std::endl;
        const GameResponsePtr response = WaitForResponse( );
        if ( !response.get( ) )
        {
            std::cout << "Did not get a JoinGame response." << std::endl;
            return false;
        }
        if ( !response->has_join_game( ) )
        {
            std::cout << "Response received is not JoinGame response."
                      << std::endl;
            return false;
        }

        if ( response->error_size( ) > 0 )
        {
            std::cout << "Error in joining the game." << std::endl;
            assert ( 0 );
            return false;
        }

        observation_face_->player_id_ = response->join_game( ).player_id( );

        std::cout << "WaitJoinGame finished successfully." << std::endl;
        return true;
    }

    virtual bool
        RequestLeaveGame ( )
    {
        if ( !is_multiplayer_ )
        {
            return false;
        }

        GameRequestPtr request = ProtoFace::MakeRequest( );
        request->mutable_leave_game( );
        return ProtoFace::SendRequest ( request );
    }

    virtual bool
        PollLeaveGame ( )
    {
        if ( !is_multiplayer_ )
        {
            return false;
        }

        if ( ProtoFace::GetResponsePending( ) !=
             SC2APIProtocol::Response::kLeaveGame )
        {
            /* If not in a game, then it is in the end state trying to leave the
             * game. */
            if ( HasResponsePending( ) )
                Error::Log ( ClientError::ResponseNotConsumed );
            return !IsInGame( );
        }

        // React to receiving a leave response.
        if ( !PollResponse( ) )
        {
            return true;
        }

        // Wait for the end response to be received before proceeding.
        // TODO (?): Add error handling.
        WaitForResponse( );
        return true;
    }

    virtual bool
        Step (
            int count
        )
    {
        if ( app_state != AppState::Normal )
        {
            return false;
        }

        GameRequestPtr               request = ProtoFace::MakeRequest( );
        SC2APIProtocol::RequestStep* step    = request->mutable_step( );
        step->set_count ( count );
        return ProtoFace::SendRequest ( request );
    }

    virtual bool
        WaitStep ( )
    {
        const GameResponsePtr response = WaitForResponse( );
        if ( !response.get( ) ||
             !response->has_step( ) ||
             response->error_size( ) > 0 )
        {
            return false;
        }

        return GetObservation( );
    }

    virtual bool
        SaveReplay (
            const std::string& path
        )
    {
        GameRequestPtr request = ProtoFace::MakeRequest( );
        request->mutable_save_replay( );
        if ( !ProtoFace::SendRequest ( request ) )
        {
            return false;
        }

        const GameResponsePtr response = WaitForResponse( );
        if ( !response.get( ) ||
             !response->has_save_replay( ) ||
             response->error_size( ) > 0 )
        {
            return false;
        }

        const SC2APIProtocol::ResponseSaveReplay& response_replay =
            response->save_replay( );

        if ( response_replay.data( ).empty( ) )
        {
            return false;
        }

        std::ofstream file;
        file.open ( path, std::fstream::binary );
        if ( !file.is_open( ) )
        {
            return false;
        }

        file.write (
            &response_replay.data( )[0],
            response_replay.data( ).size( )
        );
        return true;
    }

    virtual bool
        Ping ( )
    {
        return ProtoFace::PingGame( );
    }

    // General.
    virtual GameResponsePtr
        WaitForResponse ( )
    {
        assert ( app_state == AppState::Normal );

        GameResponsePtr response = ProtoFace::WaitForResponseInternal( );

        if ( response.get( ) && response->error_size( ) < 1 )
        {
            // Everything is good. No need for any error handling.
            return response;
        }

        if ( response.get( ) && response->error_size( ) > 0 )
        {
            std::vector<std::string> errors;
            for ( int i = 0; i < response->error_size( ); ++i )
            {
                errors.push_back ( response->error ( i ) );
            }

            Error::Log ( ClientError::SC2ProtocolError, errors );
            return response;
        }
        assert ( !response.get( ) );

        // The game application did not responded, the previous request was
        // either not sent or the app is non-responsive.

        // Step 1: distinguish between a hang and a crash. Lots of time has
        // elapsed, so if there was a crash it should have finished by now.
        assert ( pi_.process_id );
        if ( !IsProcessRunning ( pi_.process_id ) )
        {
            app_state = AppState::Crashed;
            std::cout << "Game application has terminated unexpectedly."
                      << std::endl;
            Error::Log ( ClientError::SC2AppFailure );
            return response;
        }

        // Step 2: distinguish between a non-responsive app and a failure to
        // deliver a valid request.
        {
            GameRequestPtr ping_request = ProtoFace::MakeRequest( );
            ping_request->mutable_ping( );

            if ( !ProtoFace::SendRequest ( ping_request, true ) )
            {
                // Mark the game app as unresponsive.
                app_state = AppState::Timeout;
                Error::Log ( ClientError::SC2ProtocolTimeout );
            } else
            {
                // Wait for a ping response. If this fails, the game is
                // unresponsive.
                // TODO (?): Implement a timeout parameter for this wait.
                const GameResponsePtr response_ping =
                    ProtoFace::WaitForResponseInternal( );
                if ( response_ping )
                {
                    if ( ProtoFace::GetLastStatus( ) ==
                         SC2APIProtocol::Status::unknown )
                    {
                        Error::Log ( ClientError::SC2UnknownStatus );
                    }

                    // The game is responsive, but there was another problem.
                    // This isn't the right place to handle another type of
                    // problem. Just return the nullptr.
                    Error::Log ( ClientError::SC2UnknownStatus );
                    return response;
                }

                app_state = AppState::Timeout;
                Error::Log ( ClientError::SC2ProtocolTimeout );
            }
        }

        // The game application has hanged. Try and terminate it.
        app_state = AppState::Timeout;
        for ( int i = 0; i < 10 && IsProcessRunning ( pi_.process_id ); ++i )
        {
            TerminateProcess ( pi_.process_id );
            SleepFor ( 2000 );
        }

        if ( IsProcessRunning ( pi_.process_id ) )
        {
            // Failed to kill the running process.
            app_state = AppState::Timeout_Zombie;
        }

        std::cout
            << "Game application has been terminated due to unresponsiveness."
            << std::endl;
        Error::Log ( ClientError::SC2AppFailure );
        return response;
    }

    virtual void
        SetProcessInfo (
            const ProcessInfo& pi
        )
    {
        pi_ = pi;
    }

    virtual const ProcessInfo&
        GetProcessInfo ( ) const
    {
        return pi_;
    }

    // Game status.
    virtual SC2APIProtocol::Status
        GetLastStatus ( ) const
    {
        return ProtoFace::GetLastStatus( );
    }

    // virtual AppState
    //     GetAppState ( ) const
    // {
    //     return app_state;
    // }

    virtual bool
        IsInGame ( ) const
    {
        if ( app_state != AppState::Normal )
        {
            return false;
        }

        return GetLastStatus( ) == SC2APIProtocol::Status::in_game ||
               GetLastStatus( ) == SC2APIProtocol::Status::in_replay;
    }

    virtual bool
        IsFinishedGame ( ) const
    {
        if ( app_state != AppState::Normal )
        {
            return true;
        }

        if ( IsInGame( ) )
        {
            return false;
        }

        if ( HasResponsePending( ) )
        {
            return false;
        }

        return true;
    }

    virtual bool
        IsReadyForCreateGame ( ) const
    {
        if ( app_state != AppState::Normal )
        {
            return false;
        }

        // Make sure the pipes are clear first.
        if ( HasResponsePending( ) )
        {
            return false;
        }

        // TODO (?): For multiplayer, it may be possible to be in the ended
        // state but not yet left the game. Must leave the game before create
        // game can be ready again.
        return GetLastStatus( ) == SC2APIProtocol::Status::launched ||
               GetLastStatus( ) == SC2APIProtocol::Status::ended;
    }

    virtual bool
        HasResponsePending ( ) const
    {
        return ProtoFace::HasResponsePending( );
    }

    virtual bool
        GetObservation ( )
    {
        if ( app_state != AppState::Normal )
        {
            return false;
        }

        GameRequestPtr request = ProtoFace::MakeRequest( );
        request->mutable_observation( );
        if ( !ProtoFace::SendRequest ( request ) )
        {
            return false;
        }

        const GameResponsePtr  response = WaitForResponse( );
        ResponseObservationPtr response_observation;
        SET_MESSAGE_RESPONSE ( response_observation, response, observation );
        if ( response_observation.HasErrors( ) )
        {
            std::cerr << std::endl
                      << "Error in returning observation:" << std::endl;
            std::cerr << "The main response is of type: "
                      << std::to_string ( response->response_case( ) )
                      << std::endl;
            if ( response_observation.HasResponse( ) )
            {
                std::cerr << "There is no ResponseObservation/message!"
                          << std::endl;
            }
            if ( response->error_size( ) > 0 )
            {
                for ( int i = 0; i < response->error_size( ); ++i )
                {
                    std::cerr << "Error string: " << response->error ( i )
                              << std::endl;
                }
            } else
            {
                std::cerr << "No error strings in result." << std::endl;
            }
            std::cerr << std::endl;
            return false;
        }

        ObservationPtr observation;
        SET_SUBMESSAGE_RESPONSE (
            observation,
            response_observation,
            observation
        );
        if ( observation.HasErrors( ) )
        {
            return false;
        }

        observation_ = observation;
        response_    = response_observation;

        observation_face_->UpdateObservation( );

        return true;
    }

    virtual bool
        PollResponse ( )
    {
        return ProtoFace::PollResponse( );
    }

    virtual bool
        ConsumeResponse ( )
    {
        const GameResponsePtr response = WaitForResponse( );
        return response.get( );
    }

    virtual void
        OnGameStart ( )
    {
        const Units units = observation_face_->GetUnits (
            Unit::Alliance::Self,
            [] ( const Unit& unit ) {
            return unit.unit_type == UNIT_TYPEID::TERRAN_COMMANDCENTER ||
                   unit.unit_type == UNIT_TYPEID::PROTOSS_NEXUS ||
                   unit.unit_type == UNIT_TYPEID::ZERG_HATCHERY;
        }
        );

        if ( units.empty( ) )
        {
            return;
        }

        // For now, until the api supports allies, the first (and only) building
        // in this list should be the start location
        observation_face_->start_location_ = units[0]->pos;

        // Clear start locations here since ControlInterface::OnGameStart is
        // called before the clients OnGameStart.
        observation_face_->game_info_.start_locations.clear( );
        observation_face_->game_info_.start_locations.push_back (
            observation_face_->start_location_
        );
    }

    virtual bool
        IssueEvents (
            const Tags& commands
        )
    {
        if ( observation_face_->current_game_loop_ ==
             observation_face_->previous_game_loop )
        {
            return false;
        }

        IssueUnitDestroyedEvents( );
        IssueUnitAddedEvents( );
        IssueBuildingCompletedEvents( );
        IssueIdleEvents ( commands );
        IssueUpgradeEvents( );
        IssueAlertEvents( );
        IssueUnitDamagedEvents( );

        // Run the users OnStep function after events have been issued.
        client_.OnStep( );

        return true;
    }

    void
        IssueUnitDestroyedEvents ( )
    {
        if ( !observation_->has_raw_data( ) )
        {
            return;
        }

        const SC2APIProtocol::ObservationRaw& raw = observation_->raw_data( );
        if ( raw.has_event( ) )
        {
            const SC2APIProtocol::Event& event = raw.event( );
            for ( const auto& tag : event.dead_units( ) )
            {
                const Unit* unit =
                    observation_face_->unit_pool_.GetUnit ( tag );

                if ( !unit )
                {
                    continue;
                }

                observation_face_->unit_pool_.MarkDead ( tag );
                client_.OnUnitDestroyed ( unit );
            }
        }
    }

    void
        IssueUnitAddedEvents ( )
    {
        for ( auto unit : observation_face_->unit_pool_.GetNewUnits( ) )
        {
            if ( unit->alliance == Unit::Alliance::Self )
            {
                client_.OnUnitCreated ( unit );
            } else if ( unit->alliance == Unit::Alliance::Neutral &&
                        unit->display_type == Unit::DisplayType::Visible )
            {
                client_.OnNeutralUnitCreated ( unit );
            }
        }

        for ( auto unit :
              observation_face_->unit_pool_.GetUnitsEnteringVision( ) )
        {
            if ( unit->alliance == Unit::Alliance::Enemy &&
                 unit->display_type == Unit::DisplayType::Visible )
            {
                client_.OnUnitEnterVision ( unit );
            }
        }
    }

    void
        IssueIdleEvents (
            const Tags& commands
        )
    {
        auto& unit_pool = observation_face_->unit_pool_;
        // identify idled units where commands were issued last step, but units
        // have no orders now (maybe failed, maybe executed instantly)
        for ( auto t : commands )
        {
            if ( const auto* unit = unit_pool.GetExistingUnit ( t );
                 unit && unit->orders.empty( ) )
            {
                unit_pool.AddUnitIdled ( unit );
            }
        }

        // add newly created units (if they are completed)
        for ( const auto* u : unit_pool.GetNewUnits( ) )
        {
            if ( u->build_progress >= 1.0f && u->orders.empty( ) )
            {
                unit_pool.AddUnitIdled ( u );
            }
        }

        // send only one idle event for any unit in any frame
        for ( const auto* u : unit_pool.GetIdledUnits( ) )
        {
            client_.OnUnitIdle ( u );
        }
    }

    void
        IssueBuildingCompletedEvents ( )
    {
        for ( auto unit :
              observation_face_->unit_pool_.GetCompletedBuildings( ) )
        {
            if ( unit->alliance == Unit::Alliance::Self )
            {
                client_.OnBuildingConstructionComplete ( unit );
            }
        }
    }

    void
        IssueUnitDamagedEvents ( )
    {
        for ( const auto& [unit, health, shields] : observation_face_->unit_pool_.GetDamagedUnits( ) )
        {
            client_.OnUnitDamaged ( unit, health, shields );
        }
    }

    void
        IssueAlertEvents ( )
    {
        // Iterate the alerts and issue relevant events.
        for ( const auto alert : observation_->alerts( ) )
        {
            switch ( alert )
            {
                case SC2APIProtocol::Alert::NuclearLaunchDetected : {
                    client_.OnNuclearLaunchDetected( );
                    break;
                }
                case SC2APIProtocol::Alert::NydusWormDetected : {
                    client_.OnNydusDetected( );
                    break;
                }
                default : {
                    break;
                }
            }
        }
    }

    void
        IssueUpgradeEvents ( )
    {
        std::set<uint32_t> previous;
        for ( UpgradeID upgrade : observation_face_->upgrades_previous_ )
        {
            previous.insert ( upgrade );
        }

        for ( UpgradeID upgrade : observation_face_->upgrades_ )
        {
            if ( !previous.contains ( upgrade ) )
            {
                client_.OnUpgradeCompleted ( upgrade );
            }
        }

        // Diagnostic.
        void DumpProtoUsage( )
        {
            const std::vector<uint32_t>& stats = ProtoFace::GetStats( );
            std::cout
                << "******************************************************"
                << std::endl;
            std::cout << "Protocol use by message type:" << std::endl;
            for ( std::size_t i = 0; i < stats.size( ); ++i )
            {
                if ( stats[i] == 0 )
                {
                    continue;
                }

                std::cout << std::to_string ( i ) << ": "
                          << std::to_string ( stats[i] ) << std::endl;
            }

            std::cout
                << "******************************************************"
                << std::endl;
        }

        void ResolveMap (
            const std::string&                 map_name,
            SC2APIProtocol::RequestCreateGame* request
        )
        {
            // BattleNet map
            if ( !HasExtension ( map_name, ".SC2Map" ) )
            {
                request->set_battlenet_map_name ( map_name );
                return;
            }

            // Absolute path
            SC2APIProtocol::LocalMap* local_map = request->mutable_local_map( );
            if ( DoesFileExist ( map_name ) )
            {
                local_map->set_map_path ( map_name );
                return;
            }

            // Relative path - Game maps directory
            const std::string game_relative =
                GetGameMapsDirectory ( pi_.process_path ) + map_name;
            if ( DoesFileExist ( game_relative ) )
            {
                local_map->set_map_path ( map_name );
                return;
            }

            // Relative path - Library maps directory
            if ( std::string library_relative =
                     GetLibraryMapsDirectory( ) + map_name;
                 DoesFileExist ( library_relative ) )
            {
                local_map->set_map_path ( library_relative );
                return;
            }

            // Relative path - Remotely saved maps directory
            local_map->set_map_path ( map_name );
        }

        const std::vector<ClientError>& GetClientErrors( ) const
        {
            return client_errors_;
        }

        vector<string> GetProtocolErrors( ) const
        {
            return protocol_errors_;
        }

        void ClearClientErrors( )
        {
            client_errors_.clear( );
        }

        void ClearProtocolErrors( )
        {
            protocol_errors_.clear( );
        }

        void UseGeneralizedAbility ( bool value )
        {
            observation_face_->use_generalized_ability_ = value;
        }

        // Save/Load.
        void Save( )
        {
            GameRequestPtr request = ProtoFace::MakeRequest( );
            request->mutable_quick_save( );
            if ( !ProtoFace::SendRequest ( request ) )
            {
                return;
            }
            WaitForResponse( );
        }

        void Load( )
        {
            GameRequestPtr request = ProtoFace::MakeRequest( );
            request->mutable_quick_load( );
            if ( !ProtoFace::SendRequest ( request ) )
            {
                return;
            }
            WaitForResponse( );
        }
    }
};

//------------------------------------------------------------------------------

// ClientEvents

//------------------------------------------------------------------------------

//! A set of common events a user can override in their derived bot or
//! replay observer class.
class ClientEvents {
public:
    virtual ~ClientEvents ( ) = default;

    /*! Called when a game is started after a load. Fast restarting will not
     * call this. */
    virtual void
        OnGameFullStart ( )
    {}

    //! Called when a game is started or restarted.
    virtual void
        OnGameStart ( )
    {}

    //! Called when a game has ended.
    virtual void
        OnGameEnd ( )
    {}

    /*! In non realtime games this function gets called after each step as
     * indicated by step size. In realtime this function gets called as
     * often as possible after request/responses are received from the game
     * gathering observation state. */
    virtual void
        OnStep ( )
    {}

    //! Called whenever one of the player's units has been destroyed.
    //! @param unit The destroyed unit.
    virtual void
        OnUnitDestroyed (
            const Unit* unit
        )
    {}

    //!  Called when a neutral unit is created. For example, mineral fields
    //!  observed for the first time
    //! @param unit The observed unit.
    virtual void
        OnNeutralUnitCreated (
            const Unit* unit
        )
    {}

    //! Called when a Unit has been created by the player.
    //! @param unit The created unit.
    virtual void
        OnUnitCreated (
            const Unit* unit
        )
    {}

    /*! Called when a unit becomes idle, this will only occur as an event so
     * will only be called when the unit becomes idle and not a second time.
     * Being idle is defined by having orders in the previous step and not
     * currently having orders or if it did not exist in the previous step
     * and now does, a unit being created, for instance, will call both
     * OnUnitCreated and OnUnitIdle if it does not have a rally set. */
    //! @param unit The idle unit.
    virtual void
        OnUnitIdle (
            const Unit* unit
        )
    {}

    /*! Called when an upgrade is finished, warp gate, ground weapons,
     * baneling speed, etc.
     * @param upgrade The completed upgrade. */
    virtual void
        OnUpgradeCompleted (
            UpgradeID upgrade
        )
    {}

    //! Called when the unit in the previous step had a build progress less
    //! than 1.0 but is greater than or equal to 1.0 in
    // !the current step.
    //! @param unit The constructed unit.
    virtual void
        OnBuildingConstructionComplete (
            const Unit* unit
        )
    {}

    //! Called when the unit in the current observation has lower health or
    //! shields than in the previous observation.
    //! @param unit The damaged unit.
    //! @param health The change in health (damage is positive)
    //! @param shields The change in shields (damage is positive)
    virtual void
        OnUnitDamaged (
            const Unit* unit, float health, float shields
        )
    {}

    //! Called when a nydus is placed.
    virtual void
        OnNydusDetected ( )
    {}

    //! Called when a nuclear launch is detected.
    virtual void
        OnNuclearLaunchDetected ( )
    {}

    /*! Called when an enemy unit enters vision from out of fog of war.
    < @param unit The unit entering vision.*/
    virtual void
        OnUnitEnterVision (
            const Unit* unit
        )
    {}

    /*! Called for various errors the library can encounter. See ClientError
     * enum for possible errors. */
    virtual void
        OnError (
            const vector<ClientError>& /*client_errors*/,
            const vector<string>& /*protocol_errors*/ = { }
        )
    {}
};

//------------------------------------------------------------------------------

// Client

//------------------------------------------------------------------------------

//! The base class for Agent (then Bot) and ReplayObserver.
class Client : public ClientEvents
{
public:
    Client ( )
          : ctrl_face_
    {
        ctrl_face_ = new ControlInterface ( *this );
    }

    ~Client ( ) override
    {
        delete ctrl_face_;
    }

    //! @brief The ObservationInterface is used to query game state.
    const ObservationInterface*
        Observation ( ) const
    {
        // TODO (?): Should this return a nullptr if the interface is not
        // valid (e.g., before a game is started)?
        return ctrl_face_->observation_face_.get( );
    }

    //! @brief The UnitQuery interface is used to issue commands to units.
    QueryInterface*
        Query ( ) const
    {
        // TODO (?): Should this return a nullptr if the interface is not
        // valid (e.g., before a game is started)?
        return ctrl_face_->query_face_.get( );
    }

    /*! @brief The DebugInterface allows a derived class to print text, draw
     * primitive shapes and spawn/destroy units. */
    DebugInterface*
        Debug ( ) const
    {
        return ctrl_face_->debug_face_.get( );
    }

    /*! @brief The ControlInterface is only meant to be used by the
     * coordinator as it provides functionality for connecting to
     * Starcraft2, setting up a websocket connection and issuing blocking
     * commands via SC2's protocol. */
    ControlInterface*
        Control ( )
    {
        return ctrl_face_;
    }

    const ControlInterface*
        Control ( ) const
    {
        return ctrl_face_;
    }

    virtual void
        Reset ( )
    {
        delete ctrl_face_;
        ctrl_face_ = new ControlInterface ( *this );
    }

private:
    //! Pointer to the control interface.
    ControlInterface* ctrl_face_ { nullptr };

}; // Class Client

} // namespace sc2
