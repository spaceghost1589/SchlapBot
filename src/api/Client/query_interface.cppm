module;
#include <s2clientprotocol/sc2api.pb.h>

#include "utils/macro/message_response.h"
export module query_interface;
import observation_interface;
import protocol_interface;
import common;
import data;
import error_handler;
import game_types;
import type_enums;
import unit;


export namespace sc2 {
using namespace std;

/*! @brief The QueryInterface provides additional data not contained in the
 * observation.\n\n
 * @attention Performance note: Always try and batch things up. These queries
 * are effectively synchronous and will block until returned. */
class QueryInterface {
public:
    ObservationInterface& observation_;

    QueryInterface ( ObservationInterface& observation )
          : observation_ ( observation ) {}

    virtual ~QueryInterface ( ) = default;

    /*! @brief Returns a list of abilities represented as a uint32_t see the
     * ABILITY_ID enum for their corresponding, named, representations.
     * @param unit Tag of unit.
     * @param ignore_resource_requirements Ignores supply, mineral and gas
     * costs, as well as cooldowns.
     * @param use_generalized_ability_id e.g. if true BUILD_TECHLAB_BARRACKS,
     * BUILD_TECHLAB_FACTORY and BUILD_TECHLAB_STARPORT ability ids are
     * generalized to BUILD_TECHLAB
     * @return Abilities for the unit. */
    static AvailableAbilities GetAbilitiesForUnit (
        const Unit* unit,
        bool        ignore_resource_requirements,
        bool        use_generalized_ability_id
    ) {
        vector<AvailableAbilities> available_abilities = GetAbilitiesForUnits (
            { unit },
            ignore_resource_requirements,
            use_generalized_ability_id
        );
        if ( available_abilities.empty( ) )
            Error::Log ( ClientError::NoAbilitiesForTag );
        if ( available_abilities.empty( ) ) {
            return { };
        }
        return available_abilities[0];
    }

    /*! @brief Issues multiple available abilities queries.\n [Batch version]
     * @param units Tags of units.
     * @param ignore_resource_requirements Ignores supply, mineral and gas
     * costs, as well as cooldowns.
     * @param use_generalized_ability_id e.g. if true BUILD_TECHLAB_BARRACKS,
     * BUILD_TECHLAB_FACTORY and BUILD_TECHLAB_STARPORT ability ids are
     * generalized to BUILD_TECHLAB
     * @return Abilities for the units. */
    static vector<AvailableAbilities> GetAbilitiesForUnits (
        const Units& units,
        bool         ignore_resource_requirements,
        bool         use_generalized_ability_id
    ) {
        vector<AvailableAbilities> available_abilities_out;

        // Make the request.
        {
            if ( units.empty( ) ) {
                return available_abilities_out;
            }

            const GameRequestPtr          request = ProtoFace::MakeRequest( );
            SC2APIProtocol::RequestQuery* query   = request->mutable_query( );
            query->set_ignore_resource_requirements (
                ignore_resource_requirements
            );
            for ( const auto unit : units ) {
                SC2APIProtocol::RequestQueryAvailableAbilities*
                    request_abilities = query->add_abilities( );
                request_abilities->set_unit_tag ( unit->tag );
            }

            if ( !ProtoFace::SendRequest ( request ) ) {
                return available_abilities_out;
            }
        }

        // Process the response.
        const GameResponsePtr response = ProtoFace::WaitForResponse( );
        if ( !response.get( ) ) {
            return available_abilities_out;
        }
        if ( !response->has_query( ) ) {
            Error::Log ( ClientError::InvalidResponse );
            return available_abilities_out;
        }
        const SC2APIProtocol::ResponseQuery& query = response->query( );
        if ( query.abilities_size( ) < 1 ) {
            return available_abilities_out;
        }

        for ( int i = 0; i < query.abilities_size( ); ++i ) {
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
                if ( use_generalized_ability_id ) {
                    available_ability.ability_id =
                        GetGeneralizedAbilityID ( ability.ability_id( ) );
                } else {
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

    /*! @brief Returns pathing distance between two locations. Takes into
     * account unit movement properties (e.g. Flying).
     * @param start Starting point.
     * @param end End point.
     * @return Distance between the two points. */
    static float PathingDistance ( const Point2D& start, const Point2D& end ) {
        vector<PathingQuery> queries;

        PathingQuery query;
        query.start_ = start;
        query.end_   = end;
        queries.push_back ( query );

        const vector<float> distances = PathingDistance ( queries );
        return distances[0];
    }

    /*! @brief Returns pathing distance between a unit and a target location.
     * Takes into account unit movement properties (e.g. Flying). Batch version.
     * @param start_unit Starting points.
     * @param end End points.
     * @return Distances between the two points. */
    static float PathingDistance (
        const Unit* start_unit, const Point2D& end
    ) {
        vector<PathingQuery> queries;

        PathingQuery query;
        query.start_unit_tag_ = start_unit->tag;
        query.end_            = end;
        queries.push_back ( query );

        const vector<float> distances = PathingDistance ( queries );
        return distances[0];
    }

    /*! Issues multiple pathing queries. */
    static vector<float> PathingDistance (
        const vector<PathingQuery>& queries
    ) {
        const GameRequestPtr          request       = ProtoFace::MakeRequest( );
        SC2APIProtocol::RequestQuery* request_query = request->mutable_query( );

        for ( const PathingQuery& query : queries ) {
            SC2APIProtocol::RequestQueryPathing* pathing_query =
                request_query->add_pathing( );
            if ( query.start_unit_tag_ ) {
                pathing_query->set_unit_tag ( query.start_unit_tag_ );
            } else {
                SC2APIProtocol::Point2D* startPos =
                    pathing_query->mutable_start_pos( );
                startPos->set_x ( query.start_.x );
                startPos->set_y ( query.start_.y );
            }
            SC2APIProtocol::Point2D* endPos = pathing_query->mutable_end_pos( );
            endPos->set_x ( query.end_.x );
            endPos->set_y ( query.end_.y );
        }

        if ( !ProtoFace::SendRequest ( request ) ) {
            return vector<float> ( queries.size( ), 0.0f );
        }

        const GameResponsePtr response = ProtoFace::WaitForResponse( );
        ResponseQueryPtr      response_query;
        SET_MESSAGE_RESPONSE ( response_query, response, query );
        if ( response_query.HasErrors( ) ) {
            return vector<float> ( queries.size( ), 0.0f );
        }

        if ( response_query->pathing_size( ) != queries.size( ) ) {
            return vector<float> ( queries.size( ), 0.0f );
        }

        vector<float> distances;
        distances.reserve ( queries.size( ) );

        for ( int i = 0; i < response_query->pathing_size( ); ++i ) {
            const SC2APIProtocol::ResponseQueryPathing& result =
                response_query->pathing ( i );
            distances.push_back ( result.distance( ) );
        }

        return distances;
    }

    struct PlacementQuery
    {
        AbilityID ability;
        Point2D   target_pos;
        //! Optional. Used for testing placement with add-ons.
        Tag       placing_unit_tag = 0ll;

        PlacementQuery ( ) = default;

        PlacementQuery ( AbilityID ability_id, Point2D target )
              : ability ( ability_id ),
                target_pos ( target ) {}
    };

    /*! @brief Returns whether a building can be placed at a location.
     * @param ability Ability for building or moving a structure.
     * @param target_pos Position to attempt placement on.
     * @param unit (Optional) This is only used for cases where the placing unit
     * plays a role in the placement grid test (e.g. A flying barracks building
     * an add-on requires room for both the barracks and add-on).
     * @return If placement is possible. */
    static bool Placement (
        const AbilityID& ability,
        const Point2D&   target_pos,
        const Unit*      unit = nullptr
    ) {
        vector<PlacementQuery> queries;

        PlacementQuery query;
        query.ability          = ability;
        query.target_pos       = target_pos;
        query.placing_unit_tag = unit ? unit->tag : NullTag;
        queries.push_back ( query );

        vector<bool> results = Placement ( queries );
        return results[0];
    }

    /*! @brief A batch version of the above Placement query. Takes an array of
     * abilities, positions and optional unit tags and returns a matching array
     * of bools indicating if placement is possible.
     * @param queries Placement queries.
     * @return Array of bools indicating if placement is possible. */
    static vector<bool> Placement ( const vector<PlacementQuery>& queries ) {
        const GameRequestPtr          request       = ProtoFace::MakeRequest( );
        SC2APIProtocol::RequestQuery* request_query = request->mutable_query( );

        for ( const PlacementQuery& query : queries ) {
            SC2APIProtocol::RequestQueryBuildingPlacement* placement_query =
                request_query->add_placements( );

            placement_query->set_placing_unit_tag ( query.placing_unit_tag );
            placement_query->set_ability_id ( query.ability );

            SC2APIProtocol::Point2D* target =
                placement_query->mutable_target_pos( );
            target->set_x ( query.target_pos.x );
            target->set_y ( query.target_pos.y );
        }

        if ( !ProtoFace::SendRequest ( request ) ) {
            return vector<bool> ( queries.size( ), false );
        }

        const GameResponsePtr response = ProtoFace::WaitForResponse( );
        ResponseQueryPtr      response_query;
        SET_MESSAGE_RESPONSE ( response_query, response, query );
        if ( response_query.HasErrors( ) ) {
            return vector<bool> ( queries.size( ), false );
        }

        if ( response_query->placements_size( ) != queries.size( ) ) {
            return vector<bool> ( queries.size( ), false );
        }

        vector<bool> results;
        results.reserve ( queries.size( ) );

        for ( int i = 0; i < response_query->placements_size( ); ++i ) {
            const SC2APIProtocol::ResponseQueryBuildingPlacement& result =
                response_query->placements ( i );
            results.push_back (
                result.result( ) == SC2APIProtocol::ActionResult::Success
            );
        }

        return results;
    }
}; // class QueryInterface

} // namespace sc2
