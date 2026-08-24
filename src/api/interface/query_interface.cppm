module;
#include <s2clientprotocol/sc2api.pb.h>

#include "api/data.h"
#include "api/unit.h"
#include "lib/typeids/5.0.14_typeenums.h"
#include "utils/macro/message_response.h"
export module Client:query_interface;
import protocol_interface;
import enum_db;
import error_handler;

namespace {

class ControlInterface;

} // namespace

namespace sc2 {


/*! The QueryInterface provides additional data not contained in the
 * observation.*/
/*! Performance note:
 * - Always try to batch things up. These queries are effectively synchronous
 * and will block until returned.*/
class QueryInterface
{
public:
    ControlInterface& control_;

    QueryInterface ( );

    virtual ~QueryInterface ( ) = default;

    QueryInterface ( ControlInterface& control ):
        control_ ( control ) {}

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
        bool        ignore_resource_requirements = false,
        bool        use_generalized_ability_id   = true
    ) {
        vector<AvailableAbilities> available_abilities = GetAbilitiesForUnits (
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
    //! \param units
    //! \param ignore_resource_requirements Ignores supply, mineral and gas
    //! costs, as well as cooldowns.
    //! \param use_generalized_ability_id e.g. if true BUILD_TECHLAB_BARRACKS,
    //! BUILD_TECHLAB_FACTORY and BUILD_TECHLAB_STARPORT ability ids are
    //! generalized to BUILD_TECHLAB
    //! \return Abilities for the units.
    vector<AvailableAbilities> GetAbilitiesForUnits (
        const Units& units,
        bool         ignore_resource_requirements,
        bool         use_generalized_ability_id
    ) {
        vector<AvailableAbilities> avail_abil_out;

        // Make the request.
        {
            if ( units.empty( ) )
            {
                return avail_abil_out;
            }

            const GameRequestPtr          request = ProtoFace::MakeRequest( );
            SC2APIProtocol::RequestQuery* query   = request->mutable_query( );
            query->set_ignore_resource_requirements (
                ignore_resource_requirements
            );
            for ( const auto unit : units )
            {
                SC2APIProtocol::RequestQueryAvailableAbilities* request_abil =
                    query->add_abilities( );
                request_abil->set_unit_tag ( unit->tag );
            }

            if ( !ProtoFace::SendRequest ( request ) )
            {
                return avail_abil_out;
            }
        }

        // Process the response.
        const GameResponsePtr response = control_.WaitForResponse( );
        if ( !response.get( ) )
        {
            return avail_abil_out;
        }
        if ( !response->has_query( ) )
        {
            Error::Log ( ClientError::InvalidResponse );
            return avail_abil_out;
        }
        const SC2APIProtocol::ResponseQuery& query = response->query( );
        if ( query.abilities_size( ) < 1 )
        {
            return avail_abil_out;
        }

        AvailableAbilities avail_abil_unit;
        for ( int i = 0; i < query.abilities_size( ); ++i )
        {
            const SC2APIProtocol::ResponseQueryAvailableAbilities&
                response_query_avail_abil = query.abilities ( i );

            avail_abil_unit.unit_tag = response_query_avail_abil.unit_tag( );

            avail_abil_unit.unit_type_id =
                response_query_avail_abil.unit_type_id( );

            if ( response_query_avail_abil.unit_tag( ) != units[i]->tag )
                Error::Log ( ClientError::ErrorSC2 );

            for ( int j = 0; j < response_query_avail_abil.abilities_size( );
                  ++j )
            {
                const SC2APIProtocol::AvailableAbility& ability =
                    response_query_avail_abil.abilities ( j );
                AvailableAbility avail_abil;
                if ( use_generalized_ability_id )
                {
                    avail_abil.ability_id = GetGeneralizedAbilityID (
                        static_cast<ABILITY_ID> ( ability.ability_id( ) )
                    );
                }
                else
                {
                    avail_abil.ability_id = ability.ability_id( );
                }

                avail_abil.requires_point = ability.requires_point( );
                avail_abil_unit.abilities.push_back ( avail_abil );
            }

            avail_abil_out.push_back ( avail_abil_unit );

            avail_abil_unit.abilities.clear( );
        }
        return avail_abil_out;
    }

    struct PathingQuery
    {
        Tag     start_unit_tag_ = NullTag;
        Point2D start_;
        Point2D end_;
    };

    /*! Returns pathing distance between two locations. Takes into account unit
     * movement properties (e.g. Flying).
     * @param start Starting point.
     * @param end End point.
     * @return Distance between the two points.*/
    virtual float PathingDistance ( const Point2D& start, const Point2D& end ) {
        vector<PathingQuery> queries;

        PathingQuery query;
        query.start_ = start;
        query.end_   = end;
        queries.push_back ( query );

        const vector<float> distances = PathingDistance ( queries );
        return distances[0];
    }

    //! Issues multiple pathing queries.
    vector<float> PathingDistance ( const vector<PathingQuery>& queries ) {
        const GameRequestPtr          request       = ProtoFace::MakeRequest( );
        SC2APIProtocol::RequestQuery* request_query = request->mutable_query( );

        for ( const PathingQuery& p_query : queries )
        {
            SC2APIProtocol::RequestQueryPathing* pathing_query =
                request_query->add_pathing( );
            if ( p_query.start_unit_tag_ )
            {
                pathing_query->set_unit_tag ( p_query.start_unit_tag_ );
            }
            else
            {
                SC2APIProtocol::Point2D* startPos =
                    pathing_query->mutable_start_pos( );
                startPos->set_x ( p_query.start_.x );
                startPos->set_y ( p_query.start_.y );
            }
            SC2APIProtocol::Point2D* endPos = pathing_query->mutable_end_pos( );
            endPos->set_x ( p_query.end_.x );
            endPos->set_y ( p_query.end_.y );
        }

        if ( !ProtoFace::SendRequest ( request ) )
        {
            return std::vector<float> ( queries.size( ), 0.0f );
        }

        const GameResponsePtr response = control_.WaitForResponse( );
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

        PlacementQuery ( AbilityID ability_id, Point2D target ):
            ability ( ability_id ), target_pos ( target ) {}

        AbilityID ability;
        Point2D   target_pos;
        Tag       placing_unit_tag = 0ll;
        // Optional. Used for testing placement with add-ons.
    };

    //! Returns whether a building can be placed at a location.
    //! The placing unit field is optional. This is only used for cases where
    //! the placing unit plays a role in the placement grid test (e.g. A flying
    //! barracks building an add-on requires room for both the barracks and
    //! add-on).
    //! \param ability Ability for building or moving a structure.
    //! \param target_pos Position to attempt placement on.
    //! \param unit (Optional) The unit that is moving, if moving a structure.
    //! \return If placement is possible.
    bool Placement (
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

    /*! A batch version of the above Placement query. Takes an array of
     * abilities, positions and optional unit tags and returns a matching array
     * of bools indicating if placement is possible.
     * @param queries Placement queries.
     * @return vector<bool> indicating if placement is possible.*/
    vector<bool> Placement ( const vector<PlacementQuery>& queries ) {
        const GameRequestPtr          request       = ProtoFace::MakeRequest( );
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
            return vector<bool> ( queries.size( ), false );
        }

        const GameResponsePtr response = control_.WaitForResponse( );
        ResponseQueryPtr      response_query;
        SET_MESSAGE_RESPONSE ( response_query, response, query );
        if ( response_query.HasErrors( ) )
        {
            return vector<bool> ( queries.size( ), false );
        }

        if ( response_query->placements_size( ) != queries.size( ) )
        {
            return vector<bool> ( queries.size( ), false );
        }

        vector<bool> results;
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

}; // class QueryInterface

} // namespace sc2
