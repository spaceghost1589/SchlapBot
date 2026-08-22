/*!
*The Client and ClientEvents provides most of the functionality a user would be
interested in for examining game state and scripting bots. A user should prefer
to inherit from either Agent or ReplayObserver, those classes both inherit from
Client.
*/
module;
#include <string>
#include <vector>

#include <s2clientprotocol/debug.pb.h>

#include "api/data.h"
#include "api/proto_to_pods.h"
#include "api/unit.h"
#include "lib/action.h"
#include "lib/type_enums.h"
export module Client;
import control_interface;
import :debug_interface;
import :observation_interface;
import :query_interface;
import enum_db;
import points;
import renderer;
import score;
import map_info;

// enum class UPGRADE_ID;} using UpgradeID = sc2::SC2Type<sc2::UPGRADE_ID>;

namespace {

using std::function, std::numeric_limits;

class ControlInterface;
class ProtocolInterface;
class QueryInterface;
class DebugInterface;

} // namespace

export namespace sc2 {

//------------------------------------------------------------------------------

//   ObservationInterface  -  ObservationInterface  -  ObservationInterface

//------------------------------------------------------------------------------

//! The ObservationInterface reflects the current state of the game.
//! Guaranteed to be valid when OnGameStart or OnStep is called.
class ObservationImplementation : ObservationInterface {
public:
    virtual ~ObservationImplementation ( ) = default;

    ProtocolInterface& protocol_;
    ControlInterface&  control_;

    mutable Abilities abilities_;

    // ObservationInterface (
    //         ProtocolInterface&      proto,
    //         ObservationPtr&         observation,
    //         ResponseObservationPtr& response,
    //         ControlInterface&       control
    // ):
    //         observation_ptr_ (observation),
    //         response_observation_ptr (response),
    //         current_game_loop_ (numeric_limits<uint32_t>::max( )),
    //         previous_game_loop (numeric_limits<uint32_t>::max( )),
    //         protocol_ (proto),
    //         control_ (control) {
    //         ClearFlags();
    // }

    const Abilities& GetAbilityData (bool force_refresh = false) const {
        if ( force_refresh || abilities_.size( ) < 1 ) {
            abilities_cached_ = false;
        }

        if ( abilities_cached_ ) {
            return abilities_;
        }

        abilities_.clear( );

        // Send a request for ability ids.
        const GameRequestPtr         request      = protocol_.MakeRequest( );
        SC2APIProtocol::RequestData* request_data = request->mutable_data( );
        request_data->set_ability_id (true);

        if ( !protocol_.SendRequest (request) ) {
            return abilities_;
        }

        const GameResponsePtr response = control_.WaitForResponse( );
        ResponseDataPtr       response_data;
        SET_MESSAGE_RESPONSE (response_data, response, data);
        if ( response_data.HasErrors( ) ) {
            return abilities_;
        }

        if ( response_data.HasErrors( ) ||
             response_data->abilities_size( ) == 0 ) {
            return abilities_;
        }

        abilities_.resize (response_data->abilities_size( ));
        for ( int i = 0; i < response_data->abilities_size( ); ++i ) {
            AbilityData& ability_data = abilities_[i];
            ability_data.ability_id   = i;
            ability_data.remaps_from_ability_id.clear( );
            ability_data.ReadFromProto (response_data->abilities (i));
        }

        for ( AbilityData& ability_data : abilities_ ) {
            if ( ability_data.remaps_to_ability_id == 0 ) continue;

            if ( ability_data.remaps_to_ability_id >= abilities_.size( ) ) {
                control_.Error (ClientError::InvalidAbilityRemap);
                ability_data.remaps_to_ability_id = 0;
                continue;
            }

            abilities_[ability_data.remaps_to_ability_id]
                    .remaps_from_ability_id.push_back (ability_data.ability_id);
        }

        abilities_cached_ = true;
        return abilities_;
    }

    //! Gets metadata of units. Array can be indexed directly by UnitID.
    //! \param force_refresh forces a full query from the game, may
    //! otherwise cache data from a previous call.
    //! \return Data about all units possible for the current game session.
    const UnitTypes& GetUnitTypeData (bool force_refresh = false) {
        if ( force_refresh || unit_types_.size( ) < 1 ) {
            unit_types_cached = false;
        }

        if ( unit_types_cached ) {
            return unit_types_;
        }

        unit_types_.clear( );

        // Send a request for unit_type ids.
        GameRequestPtr               request      = protocol_.MakeRequest( );
        SC2APIProtocol::RequestData* request_data = request->mutable_data( );
        request_data->set_unit_type_id (true);

        if ( !protocol_.SendRequest (request) ) {
            return unit_types_;
        }

        GameResponsePtr response = control_.WaitForResponse( );
        ResponseDataPtr response_data;
        SET_MESSAGE_RESPONSE (response_data, response, data);
        if ( response_data.HasErrors( ) ) {
            return unit_types_;
        }

        if ( response_data.HasErrors( ) || response_data->units_size( ) == 0 ) {
            return unit_types_;
        }

        unit_types_.resize (response_data->units_size( ));
        for ( int i = 0; i < response_data->units_size( ); ++i ) {
            UnitTypeData& unit = unit_types_[i];
            unit.unit_type_id  = i;
            unit.ReadFromProto (response_data->units (i));
        }

        unit_types_cached = true;
        return unit_types_;
    }

    //! Gets metadata of upgrades. Array can be indexed directly by
    //! UpgradeID.
    //! @param force_refresh forces a full query from the game, may
    //! otherwise cache data from a previous call.
    //! @return Data about all upgrades possible for the current game
    //! session.
    const Upgrades& GetUpgradeData (bool force_refresh = false) const {
        if ( force_refresh || upgrade_ids_.size( ) < 1 ) {
            upgrades_cached_ = false;
        }

        if ( upgrades_cached_ ) {
            return upgrade_ids_;
        }

        upgrade_ids_.clear( );

        GameRequestPtr               request      = proto_face_.MakeRequest( );
        SC2APIProtocol::RequestData* request_data = request->mutable_data( );
        request_data->set_upgrade_id (true);

        if ( !proto_face_.SendRequest (request) ) {
            return upgrade_ids_;
        }

        const GameResponsePtr response = control_face_.WaitForResponse( );
        ResponseDataPtr       response_data;
        SET_MESSAGE_RESPONSE (response_data, response, data);
        if ( response_data.HasErrors( ) ) {
            return upgrade_ids_;
        }

        if ( response_data.HasErrors( ) ||
             response_data->upgrades_size( ) == 0 ) {
            return upgrade_ids_;
        }

        upgrade_ids_.resize (response_data->upgrades_size( ));
        for ( int i = 0; i < response_data->upgrades_size( ); ++i ) {
            UpgradeData& upgrade = upgrade_ids_[i];
            upgrade.upgrade_id   = i;
            upgrade.ReadFromProto (response_data->upgrades (i));
        }

        upgrades_cached_ = true;
        return upgrade_ids_;
    }

    //! Gets metadata of buffs. Array can be indexed directly by BuffID.
    //! \param force_refresh forces a full query from the game, may
    //! otherwise cache data from a previous call.
    //! \return Data about all buffs possible for the current game session.
    const Buffs& GetBuffData (bool force_refresh = false) const {
        if ( force_refresh || buff_ids_.size( ) < 1 ) {
            buffs_cached_ = false;
        }

        if ( buffs_cached_ ) {
            return buff_ids_;
        }

        buff_ids_.clear( );

        GameRequestPtr               request      = protocol_.MakeRequest( );
        SC2APIProtocol::RequestData* request_data = request->mutable_data( );
        request_data->set_buff_id (true);

        if ( !protocol_.SendRequest (request) ) {
            return buff_ids_;
        }

        GameResponsePtr response = control_.WaitForResponse( );
        ResponseDataPtr response_data;
        SET_MESSAGE_RESPONSE (response_data, response, data);
        if ( response_data.HasErrors( ) ) {
            return buff_ids_;
        }

        if ( response_data.HasErrors( ) || response_data->buffs_size( ) == 0 ) {
            return buff_ids_;
        }

        buff_ids_.resize (response_data->buffs_size( ));
        for ( int i = 0; i < response_data->buffs_size( ); ++i ) {
            BuffData& buff = buff_ids_[i];
            buff.buff_id   = i;
            buff.ReadFromProto (response_data->buffs (i));
        }

        buffs_cached_ = true;
        return buff_ids_;
    }

    //! @brief Gets metadata of effects. Array can be indexed directly by
    //! EffectID.
    //! @param force_refresh { forces a full query from the game, may
    //! otherwise cache data from a previous call. }
    //! @return Effects Data about all effects possible for the current game
    //! session.
    const Effects& GetEffectData (bool force_refresh = false) const {
        if ( force_refresh || effect_ids_.empty( ) ) {
            effects_cached_ = false;
        }

        if ( effects_cached_ ) {
            return effect_ids_;
        }

        effect_ids_.clear( );

        GameRequestPtr               request      = protocol_.MakeRequest( );
        SC2APIProtocol::RequestData* request_data = request->mutable_data( );
        request_data->set_effect_id (true);

        if ( !protocol_.SendRequest (request) ) {
            return effect_ids_;
        }

        const GameResponsePtr response = control_.WaitForResponse( );
        ResponseDataPtr       response_data;
        SET_MESSAGE_RESPONSE (response_data, response, data);
        if ( response_data.HasErrors( ) ) {
            return effect_ids_;
        }

        if ( response_data.HasErrors( ) ||
             response_data->effects_size( ) == 0 ) {
            return effect_ids_;
        }

        effect_ids_.resize (response_data->effects_size( ));
        for ( int i = 0; i < response_data->effects_size( ); ++i ) {
            effect_ids_[i].ReadFromProto (response_data->effects (i));
        }

        effects_cached_ = true;
        return effect_ids_;
    }

    //! Gets the GameInfo struct for the current map.
    //! \return The current GameInfo struct.
    const GameInfo& GetGameInfo ( ) const {
        if ( game_info_cached_ ) {
            return game_info_;
        }

        GameRequestPtr request = protocol_.MakeRequest( );
        request->mutable_game_info( );

        if ( !protocol_.SendRequest (request) ) {
            return game_info_;
        }

        const GameResponsePtr response = control_.WaitForResponse( );
        ResponseGameInfoPtr   response_game_info;
        SET_MESSAGE_RESPONSE (response_game_info, response, game_info);
        if ( response_game_info.HasErrors( ) ) {
            return game_info_;
        }

        Convert (response_game_info, game_info_);

        game_info_cached_ = true;
        return game_info_;
    }

}; // class ObservationInterface

//------------------------------------------------------------------------------

//   QueryInterface  -  QueryInterface  -  QueryInterface  -  QueryInterface

//------------------------------------------------------------------------------

//! The QueryInterface provides additional data not contained in the
//! observation.
//!
//! Performance note:
//!  - Always try to batch things up. These queries are effectively synchronous
//!  and will block until returned.
class QueryImplementation : QueryInterface {
public:
    ProtocolInterface&    proto_;
    ControlInterface&     control_;
    ObservationInterface& observation_;

    QueryImplementation ( );

    virtual ~QueryImplementation ( ) = default;

    QueryImplementation (
            ProtocolInterface&    proto,
            ControlInterface&     control,
            ObservationInterface& observation
    ):
        proto_ (proto), control_ (control), observation_ (observation) {}

    //! Returns a list of abilities represented as a uint32_t see the ABILITY_ID
    //! enum for their corresponding, named, representations.
    //! \param unit
    //! \param ignore_resource_requirements Ignores supply, mineral and gas
    //! costs, as well as cooldowns.
    //! \param use_generalized_ability_id e.g. if true BUILD_TECHLAB_BARRACKS,
    //! BUILD_TECHLAB_FACTORY and BUILD_TECHLAB_STARPORT ability ids are
    //! generalized to BUILD_TECHLAB
    //! \return Abilities for the unit.
    AvailableAbilities GetAbilitiesForUnit (
            const Unit* unit,
            bool        ignore_resource_requirements,
            bool        use_generalized_ability_id
    ) override {
        vector<AvailableAbilities> available_abilities = GetAbilitiesForUnits (
                {unit},
                ignore_resource_requirements,
                use_generalized_ability_id
        );
        control_.ErrorIf (
                available_abilities.empty( ),
                ClientError::NoAbilitiesForTag
        );
        if ( available_abilities.empty( ) ) {
            return { };
        }
        return available_abilities[0];
    }

    //! Issues multiple available abilities queries.
    //! Batch version.
    //! \param units
    //! \param ignore_resource_requirements Ignores supply, mineral and gas
    //! costs, as well as cooldowns.
    //! \param use_generalized_ability_id e.g. if true BUILD_TECHLAB_BARRACKS,
    //! BUILD_TECHLAB_FACTORY and BUILD_TECHLAB_STARPORT ability ids are
    //! generalized to BUILD_TECHLAB \return Abilities for the units.
    vector<AvailableAbilities> GetAbilitiesForUnits (
            const Units& units,
            bool         ignore_resource_requirements,
            bool         use_generalized_ability_id
    ) override {
        vector<AvailableAbilities> available_abilities_out;

        // Make the request.
        {
            if ( units.empty( ) ) {
                return available_abilities_out;
            }

            GameRequestPtr                request = proto_.MakeRequest( );
            SC2APIProtocol::RequestQuery* query   = request->mutable_query( );
            query->set_ignore_resource_requirements (
                    ignore_resource_requirements
            );
            for ( const auto unit : units ) {
                SC2APIProtocol::RequestQueryAvailableAbilities*
                        request_abilities = query->add_abilities( );
                request_abilities->set_unit_tag (unit->tag);
            }

            if ( !proto_.SendRequest (request) ) {
                return available_abilities_out;
            }
        }

        // Process the response.
        const GameResponsePtr response = control_.WaitForResponse( );
        if ( !response.get( ) ) {
            return available_abilities_out;
        }
        if ( !response->has_query( ) ) {
            control_.Error (ClientError::InvalidResponse);
            return available_abilities_out;
        }
        const SC2APIProtocol::ResponseQuery& query = response->query( );
        if ( query.abilities_size( ) < 1 ) {
            return available_abilities_out;
        }

        for ( int i = 0; i < query.abilities_size( ); ++i ) {
            const SC2APIProtocol::ResponseQueryAvailableAbilities&
                    response_query_available_abilities = query.abilities (i);
            AvailableAbilities available_abilities_unit;
            available_abilities_unit.unit_tag =
                    response_query_available_abilities.unit_tag( );
            available_abilities_unit.unit_type_id =
                    response_query_available_abilities.unit_type_id( );
            control_.ErrorIf (
                    response_query_available_abilities.unit_tag( ) !=
                            units[i]->tag,
                    ClientError::ErrorSC2
            );
            for ( int j = 0;
                  j < response_query_available_abilities.abilities_size( );
                  ++j ) {
                const SC2APIProtocol::AvailableAbility& ability =
                        response_query_available_abilities.abilities (j);
                AvailableAbility available_ability;
                if ( use_generalized_ability_id ) {
                    available_ability.ability_id =
                            observation_.GetGeneralizedAbilityID (
                                    ability.ability_id( )
                            );
                } else {
                    available_ability.ability_id = ability.ability_id( );
                }

                available_ability.requires_point = ability.requires_point( );
                available_abilities_unit.abilities.push_back (
                        available_ability
                );
            }

            available_abilities_out.push_back (available_abilities_unit);
        }

        return available_abilities_out;
    }

    //! Issues multiple pathing queries.
    vector<float> PathingDistance (
            const vector<PathingQuery>& queries
    ) override {
        const GameRequestPtr          request       = proto_.MakeRequest( );
        SC2APIProtocol::RequestQuery* request_query = request->mutable_query( );

        for ( const PathingQuery& p_query : queries ) {
            SC2APIProtocol::RequestQueryPathing* pathing_query =
                    request_query->add_pathing( );
            if ( p_query.start_unit_tag_ ) {
                pathing_query->set_unit_tag (p_query.start_unit_tag_);
            } else {
                SC2APIProtocol::Point2D* startPos =
                        pathing_query->mutable_start_pos( );
                startPos->set_x (p_query.start_.x);
                startPos->set_y (p_query.start_.y);
            }
            SC2APIProtocol::Point2D* endPos = pathing_query->mutable_end_pos( );
            endPos->set_x (p_query.end_.x);
            endPos->set_y (p_query.end_.y);
        }

        if ( !proto_.SendRequest (request) ) {
            return std::vector<float> (queries.size( ), 0.0f);
        }

        const GameResponsePtr response = control_.WaitForResponse( );
        ResponseQueryPtr      response_query;
        SET_MESSAGE_RESPONSE (response_query, response, query);
        if ( response_query.HasErrors( ) ) {
            return std::vector<float> (queries.size( ), 0.0f);
        }

        if ( response_query->pathing_size( ) != queries.size( ) ) {
            return std::vector<float> (queries.size( ), 0.0f);
        }

        std::vector<float> distances;
        distances.reserve (queries.size( ));

        for ( int i = 0; i < response_query->pathing_size( ); ++i ) {
            const SC2APIProtocol::ResponseQueryPathing& result =
                    response_query->pathing (i);
            distances.push_back (result.distance( ));
        }

        return distances;
    }

    //! A batch version of the above Placement query. Takes an array of
    //! abilities, positions and optional unit tags and returns a matching array
    //! of bools indicating if placement is possible.
    //! \param queries Placement queries.
    //! \return Array of bools indicating if placement is possible.
    vector<bool> Placement (const vector<PlacementQuery>& queries) {
        const GameRequestPtr          request       = proto_.MakeRequest( );
        SC2APIProtocol::RequestQuery* request_query = request->mutable_query( );

        for ( const PlacementQuery& query : queries ) {
            SC2APIProtocol::RequestQueryBuildingPlacement* placement_query =
                    request_query->add_placements( );

            placement_query->set_placing_unit_tag (query.placing_unit_tag);
            placement_query->set_ability_id (query.ability);

            SC2APIProtocol::Point2D* target =
                    placement_query->mutable_target_pos( );
            target->set_x (query.target_pos.x);
            target->set_y (query.target_pos.y);
        }

        if ( !proto_.SendRequest (request) ) {
            return vector<bool> (queries.size( ), false);
        }

        const GameResponsePtr response = control_.WaitForResponse( );
        ResponseQueryPtr      response_query;
        SET_MESSAGE_RESPONSE (response_query, response, query);
        if ( response_query.HasErrors( ) ) {
            return vector<bool> (queries.size( ), false);
        }

        if ( response_query->placements_size( ) != queries.size( ) ) {
            return vector<bool> (queries.size( ), false);
        }

        vector<bool> results;
        results.reserve (queries.size( ));

        for ( int i = 0; i < response_query->placements_size( ); ++i ) {
            const SC2APIProtocol::ResponseQueryBuildingPlacement& result =
                    response_query->placements (i);
            results.push_back (
                    result.result( ) == SC2APIProtocol::ActionResult::Success
            );
        }

        return results;
    }
} // class QueryInterface

//------------------------------------------------------------------------------

//   DebugInterface  -  DebugInterface  -  DebugInterface  -  DebugInterface

//------------------------------------------------------------------------------

class DebugImplementation : DebugInterface {
public:
    ProtocolInterface&    proto_;
    ObservationInterface& observation_;
    ControlInterface&     control_;

    DebugImplementation (
            ProtocolInterface&    proto,
            ObservationInterface& observation,
            ControlInterface&     control
    ):
        proto_ (proto),
        observation_ (observation),
        control_ (control),
        has_move_camera (false),
        app_test_set_ (false),
        endgame_surrender_ (false),
        endgame_victory_ (false),
        set_score_ (false),
        score_ (0.0f) {}

    DebugImplementation (
            ProtocolInterface&    proto,
            ObservationInterface& observation,
            ControlInterface&     control
    );



    //! Dispatch all queued debug commands. No debug commands will be sent until
    //! this is called. This will also clear or set new debug primitives like
    //! text and lines.
    void SendDebug ( ) {
        GameRequestPtr                request       = proto_.MakeRequest( );
        SC2APIProtocol::RequestDebug* request_debug = request->mutable_debug( );

        for ( const DebugText& entry : debug_text_ ) {
            SC2APIProtocol::DebugCommand* command = request_debug->add_debug( );
            SC2APIProtocol::DebugText*    debug_text =
                    command->mutable_draw( )->add_text( );
            debug_text->set_text (entry.text);
            debug_text->set_size (entry.size);
            if ( entry.has_coords ) {
                if ( entry.is_3d ) {
                    SC2APIProtocol::Point* pos =
                            debug_text->mutable_world_pos( );
                    pos->set_x (entry.pt.x);
                    pos->set_y (entry.pt.y);
                    pos->set_z (entry.pt.z);
                } else {
                    SC2APIProtocol::Point* pos =
                            debug_text->mutable_virtual_pos( );
                    pos->set_x (entry.pt.x);
                    pos->set_y (entry.pt.y);
                }
            }
            SC2APIProtocol::Color* color_text = debug_text->mutable_color( );
            color_text->set_r (entry.color.r);
            color_text->set_g (entry.color.g);
            color_text->set_b (entry.color.b);
        }

        for ( const DebugLine& line : debug_line_ ) {
            SC2APIProtocol::DebugCommand* command = request_debug->add_debug( );
            SC2APIProtocol::DebugLine*    debug_line =
                    command->mutable_draw( )->add_lines( );
            SC2APIProtocol::Line* proto_line = debug_line->mutable_line( );

            SC2APIProtocol::Point* p0 = proto_line->mutable_p0( );
            p0->set_x (line.p0.x);
            p0->set_y (line.p0.y);
            p0->set_z (line.p0.z);

            SC2APIProtocol::Point* p1 = proto_line->mutable_p1( );
            p1->set_x (line.p1.x);
            p1->set_y (line.p1.y);
            p1->set_z (line.p1.z);

            SC2APIProtocol::Color* color_line = debug_line->mutable_color( );
            color_line->set_r (line.color.r);
            color_line->set_g (line.color.g);
            color_line->set_b (line.color.b);
        }

        for ( const DebugBox& box : debug_box_ ) {
            SC2APIProtocol::DebugCommand* command = request_debug->add_debug( );
            SC2APIProtocol::DebugBox*     debug_box =
                    command->mutable_draw( )->add_boxes( );

            SC2APIProtocol::Point* p_min = debug_box->mutable_min( );
            p_min->set_x (box.p_min.x);
            p_min->set_y (box.p_min.y);
            p_min->set_z (box.p_min.z);

            SC2APIProtocol::Point* p_max = debug_box->mutable_max( );
            p_max->set_x (box.p_max.x);
            p_max->set_y (box.p_max.y);
            p_max->set_z (box.p_max.z);

            SC2APIProtocol::Color* color_box = debug_box->mutable_color( );
            color_box->set_r (box.color.r);
            color_box->set_g (box.color.g);
            color_box->set_b (box.color.b);
        }

        for ( const DebugSphere& sphere : debug_sphere_ ) {
            SC2APIProtocol::DebugCommand* command = request_debug->add_debug( );
            SC2APIProtocol::DebugSphere*  debug_sphere =
                    command->mutable_draw( )->add_spheres( );

            SC2APIProtocol::Point* p = debug_sphere->mutable_p( );
            p->set_x (sphere.p_.x);
            p->set_y (sphere.p_.y);
            p->set_z (sphere.p_.z);

            debug_sphere->set_r (sphere.r_);

            SC2APIProtocol::Color* color_sphere =
                    debug_sphere->mutable_color( );
            color_sphere->set_r (sphere.color_.r);
            color_sphere->set_g (sphere.color_.g);
            color_sphere->set_b (sphere.color_.b);
        }

        for ( const DebugSetUnitValue& set_unit_value : debug_unit_values_ ) {
            SC2APIProtocol::DebugCommand* command = request_debug->add_debug( );
            SC2APIProtocol::DebugSetUnitValue* unit_value =
                    command->mutable_unit_value( );
            switch ( set_unit_value.unit_value ) {
                case DebugSetUnitValue::UnitValue::Energy:
                    unit_value->set_unit_value (
                            SC2APIProtocol::DebugSetUnitValue_UnitValue_Energy
                    );
                    break;
                case DebugSetUnitValue::UnitValue::Life:
                    unit_value->set_unit_value (
                            SC2APIProtocol::DebugSetUnitValue_UnitValue_Life
                    );
                    break;
                case DebugSetUnitValue::UnitValue::Shields:
                    unit_value->set_unit_value (
                            SC2APIProtocol::DebugSetUnitValue_UnitValue_Shields
                    );
                    break;
            }
            unit_value->set_value (set_unit_value.value);
            unit_value->set_unit_tag (set_unit_value.tag);
        }

        for ( const SC2APIProtocol::DebugGameState& state : debug_state_ ) {
            SC2APIProtocol::DebugCommand* command = request_debug->add_debug( );
            command->set_game_state (state);
        }

        for ( const DebugUnit& unit : debug_unit_ ) {
            if ( unit.count < 1 ) {
                continue;
            }

            SC2APIProtocol::DebugCommand* command = request_debug->add_debug( );
            SC2APIProtocol::DebugCreateUnit* create_unit =
                    command->mutable_create_unit( );
            create_unit->set_unit_type (unit.unit_type);
            create_unit->set_owner (unit.player_id);
            SC2APIProtocol::Point2D* pt = create_unit->mutable_pos( );
            pt->set_x (unit.pos.x);
            pt->set_y (unit.pos.y);
            create_unit->set_quantity (unit.count);
        }

        if ( !debug_kill_tag_.empty( ) ) {
            SC2APIProtocol::DebugCommand* command = request_debug->add_debug( );
            SC2APIProtocol::DebugKillUnit* debug_kill_unit =
                    command->mutable_kill_unit( );
            for ( auto tag : debug_kill_tag_ ) {
                debug_kill_unit->add_tag (tag);
            }
        }

        if ( app_test_set_ ) {
            SC2APIProtocol::DebugCommand* command = request_debug->add_debug( );
            SC2APIProtocol::DebugTestProcess* test_process =
                    command->mutable_test_process( );
            test_process->set_test (
                    static_cast<SC2APIProtocol::DebugTestProcess_Test> (
                            app_test_
                    )
            );
            test_process->set_delay_ms (app_test_delay_ms_);
        }

        if ( set_score_ ) {
            SC2APIProtocol::DebugCommand* command = request_debug->add_debug( );
            SC2APIProtocol::DebugSetScore* set_score =
                    command->mutable_score( );
            set_score->set_score (score_);
        }
        set_score_ = false;
        score_     = 0.0f;

        if ( endgame_surrender_ ) {
            SC2APIProtocol::DebugCommand* command = request_debug->add_debug( );
            SC2APIProtocol::DebugEndGame* end_game =
                    command->mutable_end_game( );
            end_game->set_end_result (
                    SC2APIProtocol::DebugEndGame_EndResult_Surrender
            );
        }
        endgame_surrender_ = false;

        if ( endgame_victory_ ) {
            SC2APIProtocol::DebugCommand* command = request_debug->add_debug( );
            SC2APIProtocol::DebugEndGame* end_game =
                    command->mutable_end_game( );
            end_game->set_end_result (
                    SC2APIProtocol::DebugEndGame_EndResult_DeclareVictory
            );
        }
        endgame_victory_ = false;

        proto_.SendRequest (request);
        debug_text_.clear( );
        debug_line_.clear( );
        debug_box_.clear( );
        debug_sphere_.clear( );

        debug_state_.clear( );
        debug_unit_.clear( );
        debug_kill_tag_.clear( );
        debug_unit_values_.clear( );

        // Wait for the response.
        control_.WaitForResponse( );

        if ( has_move_camera ) {
            const GameRequestPtr camera_request = proto_.MakeRequest( );
            SC2APIProtocol::RequestAction* request_action =
                    camera_request->mutable_action( );
            SC2APIProtocol::Action*    action = request_action->add_actions( );
            SC2APIProtocol::ActionRaw* action_raw =
                    action->mutable_action_raw( );
            SC2APIProtocol::ActionRawCameraMove* camera_move =
                    action_raw->mutable_camera_move( );

            SC2APIProtocol::Point* point =
                    camera_move->mutable_center_world_space( );
            point->set_x (debug_move_camera_.x);
            point->set_y (debug_move_camera_.y);

            has_move_camera = false;
            proto_.SendRequest (camera_request);
            control_.WaitForResponse( );
        }
    }
};

// ControlInterface  - ControlInterface - ControlInterface -  ControlInterface

class ControlInterface {
public:
    AppState app_state_;
    bool     is_multiplayer_;

    // Protocol and socket interface to the game.
    ProtocolInterface protocol_interface;

    // Client& client_;
    //
    // explicit ControlImpl(sc2::Client& client);
    // ~ControlImpl() override;

    // Observation from last step.
    ObservationPtr         observation_ptr;
    ResponseObservationPtr response_observation_ptr;

    unique_ptr<ObservationInterface> observation_impl_;
    unique_ptr<QueryInterface>       query_impl_;
    unique_ptr<DebugImpl>            debug_impl_;
    ProcessInfo                      process_info_;

    // Errors that may have occurred during calls to the various interfaces.
    vector<ClientError> client_errors_;
    vector<std::string> protocol_errors_;

    std::mutex error_mutex_;

    ControlInterface::ControlInterface (Client& client):
        client_ (client),
        app_state_ (AppState::normal),
        is_multiplayer_ (false),
        observation_impl_ (nullptr),
        query_impl_ (nullptr),
        debug_impl_ (nullptr) {
        protocol_interface.SetControl (this);
        observation_impl_ = std::make_unique<ObservationInterface> (
                protocol_interface,
                observation_ptr,
                response_observation_ptr,
                *this
        );
        query_impl_ = std::make_unique<QueryImpl> (
                protocol_interface,
                *this,
                *observation_impl_
        );
        debug_impl_ = std::make_unique<DebugImpl> (
                protocol_interface,
                *observation_impl_,
                *this
        );
    }

    ControlInterface::~ControlInterface ( ) {
        protocol_interface.Quit( );
    }

    ProtocolInterface& ControlInterface::Proto ( ) {
        return protocol_interface;
    }

    bool ControlInterface::Connect (
            const std::string& address, int port, int timeout_ms
    ) {
        // Keep retrying the connection until the timeout is hit.
        bool         connected = false;
        unsigned int timeout_seconds =
                ((unsigned int) timeout_ms + 1500) / 1000;
        if ( timeout_seconds < 1 ) {
            timeout_seconds = 1;
        }

        std::cout << "Connecting to " << address << ":" << port << "...\n";

        for ( unsigned int count_seconds = 0; count_seconds < timeout_seconds;
              ++count_seconds ) {
            if ( protocol_interface
                         .ConnectToGame (address, port, timeout_ms) ) {
                connected = true;
                break;
            }
            SleepFor (1000);
        }

        if ( !connected ) {
            std::cerr << "Unable to connect to game\n";
            return false;
        }

        std::cout << "Connected to " << address << ":" << port << '\n';

        return true;
    }

    bool ControlInterface::RemoteSaveMap (
            const void* data, int data_size, std::string remote_path
    ) {
        // Request.
        {
            GameRequestPtr request = protocol_interface.MakeRequest( );
            SC2APIProtocol::RequestSaveMap* request_save_map =
                    request->mutable_save_map( );
            request_save_map->set_map_path (remote_path);
            request_save_map->set_map_data (data, data_size);

            if ( !protocol_interface.SendRequest (request) ) {
                return false;
            }
        }

        // Response.
        const GameResponsePtr response = WaitForResponse( );
        if ( !response.get( ) ) {
            return false;
        }

        if ( !response->has_save_map( ) ) {
            std::cerr << "Error in ResponseSaveMap" << '\n';
            return false;
        }
        const SC2APIProtocol::ResponseSaveMap& response_save_game =
                response->save_map( );

        bool success = true;
        if ( response_save_game.has_error( ) ) {
            success               = false;
            std::string errorCode = "Unknown";
            switch ( response_save_game.error( ) ) {
                case SC2APIProtocol::ResponseSaveMap::InvalidMapData: {
                    errorCode = "Invalid Map Data";
                    break;
                }
                default: {
                    break;
                }
            }
        }

        return success;
    }

    bool ControlInterface::CreateGame (
            const std::string&         map_name,
            const vector<PlayerSetup>& players,
            bool                       realtime
    ) {
        GameRequestPtr request = protocol_interface.MakeRequest( );
        SC2APIProtocol::RequestCreateGame* request_create_game =
                request->mutable_create_game( );
        ResolveMap (map_name, request_create_game);
        for ( const PlayerSetup& setup : players ) {
            SC2APIProtocol::PlayerSetup* playerSetup =
                    request_create_game->add_player_setup( );
            playerSetup->set_type (SC2APIProtocol::PlayerType (setup.type));
            playerSetup->set_race (SC2APIProtocol::Race (int (setup.race)));
            playerSetup->set_player_name (setup.player_name);
            playerSetup->set_difficulty (
                    SC2APIProtocol::Difficulty (setup.difficulty)
            );
            playerSetup->set_ai_build (
                    SC2APIProtocol::AIBuild (setup.ai_build)
            );
        }

        request_create_game->set_realtime (realtime);

        if ( !protocol_interface.SendRequest (request) ) {
            return false;
        }

        const GameResponsePtr response = WaitForResponse( );
        if ( !response.get( ) ) {
            return false;
        }

        if ( !response->has_create_game( ) ) {
            std::cerr << "Error in ResponseCreateGame" << '\n';
            return false;
        }

        const SC2APIProtocol::ResponseCreateGame& response_create_game =
                response->create_game( );

        bool success = true;
        if ( response_create_game.has_error( ) ) {
            std::string errorCode = "Unknown";
            switch ( response_create_game.error( ) ) {
                case SC2APIProtocol::ResponseCreateGame::MissingMap: {
                    errorCode = "Missing Map";
                    break;
                }
                case SC2APIProtocol::ResponseCreateGame::InvalidMapPath: {
                    errorCode = "Invalid Map Path";
                    break;
                }
                case SC2APIProtocol::ResponseCreateGame::InvalidMapData: {
                    errorCode = "Invalid Map Data";
                    break;
                }
                case SC2APIProtocol::ResponseCreateGame::InvalidMapName: {
                    errorCode = "Invalid Map Name";
                    break;
                }
                case SC2APIProtocol::ResponseCreateGame::InvalidMapHandle: {
                    errorCode = "Invalid Map Handle";
                    break;
                }
                case SC2APIProtocol::ResponseCreateGame::MissingPlayerSetup: {
                    errorCode = "Missing Player Setup";
                    break;
                }
                case SC2APIProtocol::ResponseCreateGame::InvalidPlayerSetup: {
                    errorCode = "Invalid Player Setup";
                    break;
                }
                default: {
                    break;
                }
            }

            std::cerr << "CreateGame request returned an error code: "
                      << errorCode << '\n';
            success = false;
        }

        if ( response_create_game.has_error_details( ) &&
             response_create_game.error_details( ).length( ) > 0 ) {
            std::cerr << "CreateGame request returned error details: "
                      << response_create_game.error_details( ) << '\n';
            success = false;
        }

        return success;
    }

    // General.

    bool ControlInterface::IssueEvents (const Tags& commands = { }) {
        if ( observation_impl_->current_game_loop_ ==
             observation_impl_->previous_game_loop ) {
            return false;
        }

        void ControlInterface::IssueUnitDestroyedEvents( ) const {
            if ( !observation_ptr->has_raw_data( ) ) {
                return;
            }

            const SC2APIProtocol::ObservationRaw& raw =
                    observation_ptr->raw_data( );
            if ( raw.has_event( ) ) {
                const SC2APIProtocol::Event& event = raw.event( );
                for ( const auto& tag : event.dead_units( ) ) {
                    const Unit* unit =
                            observation_impl_->unit_pool_.GetUnit (tag);

                    if ( !unit ) {
                        continue;
                    }

                    observation_impl_->unit_pool_.MarkDead (tag);
                    client_.OnUnitDestroyed (unit);
                }
            }
        }

        void ControlInterface::IssueUnitAddedEvents( ) const {
            for ( auto unit : observation_impl_->unit_pool_.GetNewUnits( ) ) {
                if ( unit->alliance == Unit::Alliance::Self ) {
                    client_.OnUnitCreated (unit);
                } else if ( unit->alliance == Unit::Alliance::Neutral &&
                            unit->display_type == Unit::DisplayType::Visible ) {
                    client_.OnNeutralUnitCreated (unit);
                }
            }

            for ( auto unit :
                  observation_impl_->unit_pool_.GetUnitsEnteringVision( ) ) {
                if ( unit->alliance == Unit::Alliance::Enemy &&
                     unit->display_type == Unit::DisplayType::Visible ) {
                    client_.OnUnitEnterVision (unit);
                }
            }
        }

        void ControlInterface::IssueBuildingCompletedEvents( ) const {
            for ( auto unit :
                  observation_impl_->unit_pool_.GetCompletedBuildings( ) ) {
                if ( unit->alliance == Unit::Alliance::Self ) {
                    client_.OnBuildingConstructionComplete (unit);
                }
            }
        }

        void ControlInterface::IssueIdleEvents (const Tags& commands) const {
            auto& unit_pool = observation_impl_->unit_pool_;
            // identify idled units where commands were issued last step, but
            // units have no orders now (maybe failed, maybe executed instantly)
            for ( auto t : commands ) {
                const auto* unit = unit_pool.GetExistingUnit (t);
                if ( unit && unit->orders.empty( ) ) {
                    unit_pool.AddUnitIdled (unit);
                }
            }

            // add newly created units (if they are completed)
            for ( const auto* u : unit_pool.GetNewUnits( ) ) {
                if ( u->build_progress >= 1.0f && u->orders.empty( ) ) {
                    unit_pool.AddUnitIdled (u);
                }
            }

            // send only one idle event for any unit in any frame
            for ( const auto* u : unit_pool.GetIdledUnits( ) ) {
                client_.OnUnitIdle (u);
            }
        }

        void ControlInterface::IssueUpgradeEvents( ) const {
            set<uint32_t> previous;
            for ( UpgradeID upID : observation_impl_->upgrades_previous_ ) {
                previous.insert (upID);
            }

            for ( UpgradeID upID : observation_impl_->upgrades_ ) {
                if ( previous.find (upID) == previous.end( ) ) {
                    client_.OnUpgradeCompleted (upID);
                }
            }
        }

        void ControlInterface::IssueAlertEvents( ) const {
            // Iterate the alerts and issue relevant events.
            for ( const auto alert : observation_ptr->alerts( ) ) {
                switch ( alert ) {
                    case SC2APIProtocol::Alert::NuclearLaunchDetected: {
                        client_.OnNuclearLaunchDetected( );
                        break;
                    }
                    case SC2APIProtocol::Alert::NydusWormDetected: {
                        client_.OnNydusDetected( );
                        break;
                    }
                    default: {
                        break;
                    }
                }
            }
        }

        void ControlInterface::IssueUnitDamagedEvents( ) const {
            for ( const auto& u :
                  observation_impl_->unit_pool_.GetDamagedUnits( ) ) {
                client_.OnUnitDamaged (u.unit, u.health, u.shields);
            }
        }

        // Run the users OnStep function after events have been issued.
        client_.OnStep( );

        return true;
    }

    void ControlInterface::OnGameStart ( ) {
        Units units = observation_impl_->GetUnits (
                Unit::Alliance::Self,
                [] (const Unit& unit) {
            return unit.unit_type == UNIT_TYPEID::TERRAN_COMMANDCENTER ||
                   unit.unit_type == UNIT_TYPEID::PROTOSS_NEXUS ||
                   unit.unit_type == UNIT_TYPEID::ZERG_HATCHERY;
        }
        );

        if ( units.empty( ) ) {
            return;
        }

        // For now, until the api supports allies, the first (and only) building
        // in this list should be the start location
        observation_impl_->start_location_ = units[0]->pos;

        // Clear start locations here since ControlInterface::OnGameStart is
        // called before the clients OnGameStart.
        observation_impl_->game_info_.start_locations.clear( );
        observation_impl_->game_info_.start_locations.push_back (
                observation_impl_->start_location_
        );
    }

    // Diagnostic.
    void ControlInterface::DumpProtocolUsage ( ) {
        const vector<uint32_t>& stats = protocol_interface.GetStats( );
        std::cout << "******************************************************"
                  << '\n';
        std::cout << "Protocol use by message type:" << '\n';
        for ( std::size_t i = 0; i < stats.size( ); ++i ) {
            if ( stats[i] == 0 ) {
                continue;
            }

            std::cout << std::to_string (i) << ": " << std::to_string (stats[i])
                      << '\n';
        }

        std::cout << "******************************************************"
                  << '\n';
    }

    void ControlInterface::Error (
            ClientError error, const vector<string>& errors
    ) {
        // An ConnectionClosed error can come off a civetweb worker thread.
        const std::lock_guard guard (error_mutex_);

        // Cache all the errors that happen
        client_errors_.push_back (error);
        for ( const string& e : errors ) {
            protocol_errors_.push_back (e);
        }

#ifdef SC2API_ASSERT_ON_ERROR
        assert (0);
#endif
    }

    void ControlInterface::ErrorIf (
            bool                                        condition,
            ClientError                                 error,
            [[maybe_unused]] const vector<std::string>& errors
    ) {
        if ( condition ) {
            Error (error, errors);
        }
    }

    // Save/Load.
    void ControlInterface::Save ( ) {
        GameRequestPtr request = Proto( ).MakeRequest( );
        request->mutable_quick_save( );
        if ( !Proto( ).SendRequest (request) ) {
            return;
        }
        WaitForResponse( );
    }

    void ControlInterface::Load ( ) {
        GameRequestPtr request = Proto( ).MakeRequest( );
        request->mutable_quick_load( );
        if ( !Proto( ).SendRequest (request) ) {
            return;
        }
        WaitForResponse( );
    }

    bool ControlInterface::RequestJoinGame (
            PlayerSetup              setup,
            const InterfaceSettings& settings,
            const Ports&             ports,
            bool                     raw_affects_selection
    ) {
        observation_impl_->ClearFlags( );

        is_multiplayer_ = ports.IsValid( );

        GameRequestPtr request = protocol_interface.MakeRequest( );
        SC2APIProtocol::RequestJoinGame* request_join_game =
                request->mutable_join_game( );

        request_join_game->set_race (SC2APIProtocol::Race (int (setup.race)));
        request_join_game->set_player_name (setup.player_name);

        if ( is_multiplayer_ ) {
            // Set shared port.
            request_join_game->set_shared_port (ports.shared_port);

            // Set server ports.
            SC2APIProtocol::PortSet* server_ports =
                    request_join_game->mutable_server_ports( );
            server_ports->set_game_port (ports.server_ports.game_port);
            server_ports->set_base_port (ports.server_ports.base_port);

            // Set client ports. Right now only 1v1 is supported.
            for ( const PortSet& client_ports : ports.client_ports ) {
                SC2APIProtocol::PortSet* client_port =
                        request_join_game->add_client_ports( );
                client_port->set_game_port (client_ports.game_port);
                client_port->set_base_port (client_ports.base_port);
            }
        }

        SC2APIProtocol::InterfaceOptions* options =
                request_join_game->mutable_options( );

        options->set_raw (true);
        options->set_score (true);
        options->set_show_cloaked (true);
        options->set_show_burrowed_shadows (true);
        options->set_show_placeholders (true);

        // If raw_affects_selection == true, will not generate a deselect
        // command after sending a command to a unit
        options->set_raw_affects_selection (raw_affects_selection);

        if ( settings.use_feature_layers ) {
            SC2APIProtocol::SpatialCameraSetup* setupProto =
                    options->mutable_feature_layer( );
            setupProto->set_width (
                    settings.feature_layer_settings.camera_width
            );
            SC2APIProtocol::Size2DI* resolution =
                    setupProto->mutable_resolution( );
            resolution->set_x (settings.feature_layer_settings.map_x);
            resolution->set_y (settings.feature_layer_settings.map_y);
            SC2APIProtocol::Size2DI* minimap_resolution =
                    setupProto->mutable_minimap_resolution( );
            minimap_resolution->set_x (
                    settings.feature_layer_settings.minimap_x
            );
            minimap_resolution->set_y (
                    settings.feature_layer_settings.minimap_y
            );
        }
        if ( settings.use_render ) {
            SC2APIProtocol::SpatialCameraSetup* setupProto =
                    options->mutable_render( );
            SC2APIProtocol::Size2DI* resolution =
                    setupProto->mutable_resolution( );
            resolution->set_x (settings.render_settings.map_x);
            resolution->set_y (settings.render_settings.map_y);
            SC2APIProtocol::Size2DI* minimap_resolution =
                    setupProto->mutable_minimap_resolution( );
            minimap_resolution->set_x (settings.render_settings.minimap_x);
            minimap_resolution->set_y (settings.render_settings.minimap_y);
        }

        return protocol_interface.SendRequest (request);
    }

    bool ControlInterface::WaitJoinGame ( ) {
        std::cout << "Waiting for the JoinGame response." << '\n';
        const GameResponsePtr response = WaitForResponse( );
        if ( !response.get( ) ) {
            std::cout << "Did not get a JoinGame response." << '\n';
            return false;
        }
        if ( !response->has_join_game( ) ) {
            std::cout << "Response received is not JoinGame response." << '\n';
            return false;
        }

        if ( response->error_size( ) > 0 ) {
            std::cout << "Error in joining the game." << '\n';
            assert (0);
            return false;
        }

        observation_impl_->player_id_ = response->join_game( ).player_id( );

        std::cout << "WaitJoinGame finished successfully." << '\n';
        return true;
    }

    bool ControlInterface::RequestLeaveGame ( ) {
        if ( !is_multiplayer_ ) {
            return false;
        }

        GameRequestPtr request = protocol_interface.MakeRequest( );
        request->mutable_leave_game( );
        return protocol_interface.SendRequest (request);
    }

    bool ControlInterface::PollLeaveGame ( ) {
        if ( !is_multiplayer_ ) {
            return false;
        }

        if ( protocol_interface.GetResponsePending( ) !=
             SC2APIProtocol::Response::kLeaveGame ) {
            // If not in a game, then it is in the end state trying to leave the
            // game.
            ErrorIf (HasResponsePending( ), ClientError::ResponseNotConsumed);
            return !IsInGame( );
        }

        // React to receiving a leave response.
        if ( !PollResponse( ) ) {
            return true;
        }

        // Wait for the end response to be received before proceeding.
        // TODO (?): Add error handling.
        WaitForResponse( );
        return true;
    }

    bool ControlInterface::Step (int count) {
        if ( app_state_ != AppState::normal ) {
            return false;
        }

        GameRequestPtr request            = protocol_interface.MakeRequest( );
        SC2APIProtocol::RequestStep* step = request->mutable_step( );
        step->set_count (count);
        return protocol_interface.SendRequest (request);
    }

    bool ControlInterface::WaitStep ( ) {
        const GameResponsePtr response = WaitForResponse( );
        if ( !response.get( ) ||
             !response->has_step( ) ||
             response->error_size( ) > 0 ) {
            return false;
        }

        return GetObservation( );
    }

    bool ControlInterface::SaveReplay (const std::string& path) {
        GameRequestPtr request = protocol_interface.MakeRequest( );
        request->mutable_save_replay( );
        if ( !protocol_interface.SendRequest (request) ) {
            return false;
        }

        const GameResponsePtr response = WaitForResponse( );
        if ( !response.get( ) ||
             !response->has_save_replay( ) ||
             response->error_size( ) > 0 ) {
            return false;
        }

        const SC2APIProtocol::ResponseSaveReplay& response_replay =
                response->save_replay( );

        if ( response_replay.data( ).empty( ) ) {
            return false;
        }

        std::ofstream file;
        file.open (path, std::fstream::binary);
        if ( !file.is_open( ) ) {
            return false;
        }

        file.write (
                &response_replay.data( )[0],
                response_replay.data( ).size( )
        );
        return true;
    }

    bool ControlInterface::Ping ( ) {
        return protocol_interface.PingGame( );
    }

    GameResponsePtr ControlInterface::WaitForResponse ( ) {
        assert (app_state_ == AppState::normal);

        GameResponsePtr response =
                protocol_interface.WaitForResponseInternal( );

        if ( response.get( ) && response->error_size( ) < 1 ) {
            // Everything is good. No need for any error handling.
            return response;
        }

        if ( response.get( ) && response->error_size( ) > 0 ) {
            vector<std::string> errors;
            for ( int i = 0; i < response->error_size( ); ++i ) {
                errors.push_back (response->error (i));
            }

            Error (ClientError::SC2ProtocolError, errors);
            return response;
        }
        assert (!response.get( ));

        // The game application did not responded, the previous request was
        // either not sent or the app is non-responsive.

        // Step 1: distinguish between a hang and a crash. Lots of time has
        // elapsed, so if there was a crash it should have finished by now.
        assert (pi_.process_id);
        if ( !IsProcessRunning (process_info_.process_id) ) {
            app_state_ = AppState::crashed;
            std::cout << "Game application has terminated unexpectedly."
                      << '\n';
            Error (ClientError::SC2AppFailure);
            return response;
        }

        // Step 2: distinguish between a non-responsive app and a failure to
        // deliver a valid request.
        {
            GameRequestPtr ping_request = protocol_interface.MakeRequest( );
            ping_request->mutable_ping( );

            if ( !protocol_interface.SendRequest (ping_request, true) ) {
                // Mark the game app as unresponsive.
                app_state_ = AppState::timeout;
                Error (ClientError::SC2ProtocolTimeout);
            } else {
                // Wait for a ping response. If this fails, the game is
                // unresponsive.
                // TODO (?): Implement a timeout parameter for this wait.
                const GameResponsePtr response_ping =
                        protocol_interface.WaitForResponseInternal( );
                if ( response_ping ) {
                    if ( protocol_interface.GetLastStatus( ) ==
                         SC2APIProtocol::Status::unknown ) {
                        Error (ClientError::SC2UnknownStatus);
                    }

                    // The game is responsive, but there was another problem.
                    // This isn't the right place to handle another type of
                    // problem. Just return the nullptr.
                    Error (ClientError::SC2UnknownStatus);
                    return response;
                }

                app_state_ = AppState::timeout;
                Error (ClientError::SC2ProtocolTimeout);
            }
        }

        // The game application has hanged. Try and terminate it.
        app_state_ = AppState::timeout;
        for ( int i = 0; i < 10 && IsProcessRunning (process_info_.process_id);
              ++i ) {
            TerminateProcess (process_info_.process_id);
            SleepFor (2000);
        }

        if ( IsProcessRunning (process_info_.process_id) ) {
            // Failed to kill the running process.
            app_state_ = AppState::timeout_zombie;
        }

        std::cout << "Game application has been terminated due to "
                     "unresponsiveness."
                  << '\n';
        Error (ClientError::SC2AppFailure);
        return response;
    }

    void ControlInterface::SetProcessInfo (const ProcessInfo& pi) {
        process_info_ = pi;
    }

    const ProcessInfo& ControlInterface::GetProcessInfo ( ) const {
        return process_info_;
    }

    // Game status.
    SC2APIProtocol::Status ControlInterface::GetLastStatus ( ) const {
        return protocol_interface.GetLastStatus( );
    }

    AppState ControlInterface::GetAppState ( ) const {
        return app_state_;
    }

    bool ControlInterface::IsInGame ( ) const {
        if ( app_state_ != AppState::normal ) {
            return false;
        }

        return GetLastStatus( ) == SC2APIProtocol::Status::in_game ||
               GetLastStatus( ) == SC2APIProtocol::Status::in_replay;
    }

    bool ControlInterface::IsFinishedGame ( ) const {
        if ( app_state_ != AppState::normal ) {
            return true;
        }

        if ( IsInGame( ) ) {
            return false;
        }

        if ( HasResponsePending( ) ) {
            return false;
        }

        return true;
    }

    bool ControlInterface::IsReadyForCreateGame ( ) const {
        if ( app_state_ != AppState::normal ) {
            return false;
        }

        // Make sure the pipes are clear first.
        if ( HasResponsePending( ) ) {
            return false;
        }

        // TODO (?): For multiplayer, it may be possible to be in the ended
        // state but not yet left the game. Must leave the game before create
        // game can be ready again.
        return GetLastStatus( ) == SC2APIProtocol::Status::launched ||
               GetLastStatus( ) == SC2APIProtocol::Status::ended;
    }

    bool ControlInterface::HasResponsePending ( ) const {
        return protocol_interface.HasResponsePending( );
    }

    bool ControlInterface::GetObservation ( ) {
        if ( app_state_ != AppState::normal ) {
            return false;
        }

        GameRequestPtr request = protocol_interface.MakeRequest( );
        request->mutable_observation( );
        if ( !protocol_interface.SendRequest (request) ) {
            return false;
        }

        const GameResponsePtr  response = WaitForResponse( );
        ResponseObservationPtr response_observation;
        SET_MESSAGE_RESPONSE (response_observation, response, observation);
        if ( response_observation.HasErrors( ) ) {
            std::cerr << '\n' << "Error in returning observation:" << '\n';
            std::cerr << "The main response is of type: "
                      << std::to_string (response->response_case( )) << '\n';
            if ( response_observation.HasResponse( ) ) {
                std::cerr << "There is no ResponseObservation/message!" << '\n';
            }
            if ( response->error_size( ) > 0 ) {
                for ( int i = 0; i < response->error_size( ); ++i ) {
                    std::cerr << "Error string: " << response->error (i)
                              << '\n';
                }
            } else {
                std::cerr << "No error strings in result." << '\n';
            }
            std::cerr << '\n';
            return false;
        }

        ObservationPtr observation;
        SET_SUBMESSAGE_RESPONSE (
                observation,
                response_observation,
                observation
        );
        if ( observation.HasErrors( ) ) {
            return false;
        }

        observation_ptr          = observation;
        response_observation_ptr = response_observation;

        observation_impl_->UpdateObservation( );

        return true;
    }

    bool ControlInterface::PollResponse ( ) {
        return protocol_interface.PollResponse( );
    }

    bool ControlInterface::ConsumeResponse ( ) {
        const GameResponsePtr response = WaitForResponse( );
        return response.get( );
    }

    void ControlInterface::ResolveMap (
            const std::string&                 map_name,
            SC2APIProtocol::RequestCreateGame* request
    ) {
        // BattleNet map
        std::cout << "Resolving BattleNet map..." << '\n';
        if ( !HasExtension (map_name, ".SC2Map") ) {
            request->set_battlenet_map_name (map_name);
            return;
        }
        std::cout << "No BattleNet map..." << '\n';

        // Absolute path
        std::cout << "Resolving Absolute map path..." << '\n';
        SC2APIProtocol::LocalMap* local_map = request->mutable_local_map( );
        if ( DoesFileExist (map_name) ) {
            local_map->set_map_path (map_name);
            return;
        }

        // Relative path - Game maps directory
        std::cout << "Resolving Relative map path..." << '\n';
        const std::string game_relative =
                GetGameMapsDirectory (process_info_.process_path) + map_name;
        if ( DoesFileExist (game_relative) ) {
            local_map->set_map_path (map_name);
            return;
        }

        // Relative path - Library maps directory
        std::cout << "Resolving Relative map path..." << '\n';
        std::string library_relative = GetLibraryMapsDirectory( ) + map_name;
        if ( DoesFileExist (library_relative) ) {
            local_map->set_map_path (library_relative);
            return;
        }

        // Relative path - Remotely saved maps directory
        local_map->set_map_path (map_name);
    }

    const vector<ClientError>& GetClientErrors ( ) const final {
        return client_errors_;
    }

    const vector<std::string>& GetProtocolErrors ( ) const final {
        return protocol_errors_;
    }

    void ClearClientErrors ( ) override {
        client_errors_.clear( );
    }

    void ClearProtocolErrors ( ) override {
        protocol_errors_.clear( );
    }

    void UseGeneralizedAbility (bool value) override {
        observation_impl_->use_generalized_ability_ = value;
    }
};

// Client  -  Client  -  Client  -  Client  -  Client  -  Client  -  Client  -


//! The base class for Agent and ReplayObserver.
//! A set of common events a user can override in their derived bot or replay
//! observer class.
class Client : ObservationImplementation {
public:
    Client::Client ( ):
        Control_Interface_ (nullptr) {
        Control_Interface_ = new ControlImp (*this);
    }

    virtual Client::~Client ( ) {
        delete Control_Interface_;
    }

    const ObservationInterface* Observation_Interface ( ) const {
        // TODO (?): Should this return a nullptr if the interface is not valid
        // (e.g., before a game is started)?
        return Control_Interface_->observation_impl_.get( );
    }

    //! The UnitQuery interface is used to issue commands to units.
    QueryInterface* Query_Interface ( ) const {
        // TODO (?): Should this return a nullptr if the interface is not valid
        // (e.g., before a game is started)?
        return Control_Interface_->query_impl_.get( );
    }

    //! The ControlInterface is only meant to be used by the CCoordinator as it
    //! provides functionality for connecting to Starcraft2, setting up a
    //! websocket connection and issuing blocking commands via SC2's protocol.
    ControlInterface* Control_Interface ( ) {
        return Control_Interface_;
    }

    const ControlInterface* Control_Interface ( ) const {
        return Control_Interface_;
    }

    //! The DebugInterface allows a derived class to print text, draw primitive
    //! shapes and spawn/destroy units.
    DebugInterface* Debug_Interface ( ) const {
        return Control_Interface_->debug_impl_.get( );
    }

    const ObservationInterface* Client::Observation ( ) const {
        // TODO (?): Should this return a nullptr if the interface is not valid
        // (e.g., before a game is started)?
        return Control_Interface_->observation_imp_.get( );
    }

    QueryInterface* Client::Query ( ) {
        // TODO (?): Should this return a nullptr if the interface is not valid
        // (e.g., before a game is started)?
        return Control_Interface_->query_imp_.get( );
    }

    DebugInterface* Client::Debug ( ) {
        return Control_Interface_->debug_imp_.get( );
    }

    ControlInterface* Client::Control ( ) {
        return Control_Interface_;
    }

    const ControlInterface* Client::Control ( ) const {
        return Control_Interface_;
    }

    void Client::Reset ( ) {
        delete Control_Interface_;
        Control_Interface_ = new ControlInterface (*this);
    }

    //! Called when a game is started after a load. Fast restarting will not
    //! call this.
    virtual void OnGameFullStart ( ) {}

    //! Called when a game is started or restarted.
    virtual void OnGameStart ( ) {}

    //! In non realtime games this function gets called after each step as
    //! indicated by step size. In realtime this function gets called as often
    //! as possible after request/responses are received from the game gathering
    //! observation state.
    virtual void OnStep ( ) {}

    //! Called when a game has ended.
    virtual void OnGameEnd ( ) {}

    //! Called whenever one of the player's units has been destroyed.
    //! \param unit The destroyed unit.
    virtual void OnUnitDestroyed (const Unit* unit) {}

    //! Called when a neutral unit is created. For example, mineral fields
    //! observed for the first time
    //! \param unit The observed unit.
    virtual void OnNeutralUnitCreated (const Unit* unit) {}

    //! Called when a Unit has been created by the player.
    //! \param unit The created unit.
    virtual void OnUnitCreated (const Unit* unit) {}

    //! Called when a unit becomes idle, this will only occur as an event so
    //! will only be called when the unit becomes idle and not a second time.
    //! Being idle is defined by having orders in the previous step and not
    //! currently having orders or if it did not exist in the previous step and
    //! now does, a unit being created, for instance, will call both
    //! OnUnitCreated and OnUnitIdle if it does not have a rally set.
    //!< \param unit The idle unit.
    virtual void OnUnitIdle (const Unit* unit) {}

    //! Called when an upgrade is finished, warp gate, ground weapons, baneling
    //! speed, etc.
    //!< \param upID The completed upgrade.
    virtual void OnUpgradeCompleted (UpgradeID upID) {}

    //! Called when the unit in the previous step had a build progress less
    //! than 1.0 but is greater than or equal to 1.0 in the current step.
    //! \param unit The constructed unit.
    virtual void OnBuildingConstructionComplete (const Unit* unit) {}

    //! Called when the unit in the current observation has lower health or
    //! shields than in the previous observation.
    //! \param unit The damaged unit.
    //! \param health The change in health (damage is positive)
    //! \param shields The change in shields (damage is positive)
    virtual void OnUnitDamaged (const Unit* unit, float health, float shields) {
    }

    //! Called when a nydus is placed.
    virtual void OnNydusDetected ( ) {}

    //! Called when a nuclear launch is detected.
    virtual void OnNuclearLaunchDetected ( ) {}

    //! Called when an enemy unit enters vision from out of fog of war.
    //!< \param unit The unit entering vision.
    virtual void OnUnitEnterVision (const Unit* unit) {}

    //! Called for various errors the library can encounter. See ClientError
    //! enum for possible errors.
    virtual void OnError (
            const std::vector<ClientError>& /*client_errors*/,
            const std::vector<std::string>& /*protocol_errors*/ = { }
    ) {}

private:
    //! Pointer to the control interface.
    ControlInterface* Control_Interface_;
};

} // namespace sc2
