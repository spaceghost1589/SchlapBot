module;
#include <cmath>
#include <limits>
#include <numbers>
// ReSharper disable once CppUnusedIncludeDirective
#include <typeinfo>
#include <utility>
#include <vector>
export module search;
import debug_interface;
import observation_interface;
import query_interface;
import color;
import point;
import type_enums;
import unit;

export namespace sc2 {
using namespace std;

size_t CalculateQueries (
    const float                             radius,
    const float                             step_size,
    const Point2D                          &center,
    vector<QueryInterface::PlacementQuery> &queries
) {
    Point2D previous_grid (
        numeric_limits<float>::max( ),
        numeric_limits<float>::max( )
    );
    size_t valid_queries = 0;
    // Find a buildable location on the circumference of the sphere
    float  loc           = 0.0F;
    while ( loc < 360.0F ) {
        const Point2D point = Point2D (
            ( radius * cos ( ( loc * numbers::pi_v<float> ) / 180.0F ) ) +
                center.x,
            ( radius * sin ( ( loc * numbers::pi_v<float> ) / 180.0F ) ) +
                center.y
        );

        const QueryInterface::PlacementQuery query (
            ABILITY_ID::BUILD_COMMANDCENTER,
            point
        );

        Point2D current_grid = Point2D ( floor ( point.x ), floor ( point.y ) );

        if ( previous_grid != current_grid ) {
            queries.push_back ( query );
            ++valid_queries;
        }

        previous_grid = current_grid;
        loc          += step_size;
    }

    return valid_queries;
}

/*! @brief Clusters units within some distance of each other and returns a list
 * of them and their center of mass. */
vector<pair<Point3D, vector<Unit>>>
    Cluster ( const Units &units, const float distance_apart ) {
    const float squared_distance_apart = distance_apart * distance_apart;
    vector<pair<Point3D, vector<Unit>>> clusters;
    for ( const Unit *unit : units ) {
        const Unit &u = *unit;

        float                        distance = numeric_limits<float>::max( );
        pair<Point3D, vector<Unit>> *target_cluster = nullptr;
        // Find the cluster this mineral patch is closest to.
        for ( pair<Point3D, vector<Unit>> &cluster : clusters ) {
            if ( const float d = DistanceSquared3D ( cluster.first, u );
                 d < distance )
            {
                distance       = d;
                target_cluster = &cluster;
            }
        }

        // If the target cluster is some distance away don't use it.
        if ( distance > squared_distance_apart ) {
            clusters.push_back ( pair ( u.pos, vector { u } ) );
            continue;
        }

        // Otherwise append to that cluster and update it's center of mass.
        target_cluster->second.push_back ( u );
        const float size =
            static_cast<float> ( target_cluster->second.size( ) );
        target_cluster->first =
            ( target_cluster->first * ( size - 1 ) + u.pos ) / size;
    }

    return clusters;
}

struct ExpansionParameters
{
    // By default we use values that generally work but may require tuning for
    // certain maps.

    //! The various radius to check at from the center of an expansion.
    vector<float> radii_ = { 6.4F, 5.3F };

    //! With what granularity to step the circumference of the circle.
    float circle_step_size_ = 0.5F;

    /*! With what distance to cluster mineral/vespene in, this will be used for
     * center of mass calculation. */
    float cluster_distance_ = 15.0F;

    /*! If filled out CalculateExpansionLocations will render spheres to show
     * what it calculated. */
    DebugInterface *debug_ = nullptr;
};

/*! @brief Calculates expansion locations, this call can take on the order of
 * 100ms since it makes blocking queries to SC2 so call it once and cache the
 * results.*/
vector<Point3D> CalculateExpansionLocations (
    const ObservationInterface *resources,
    const QueryInterface       *query,
    const ExpansionParameters  &parameters
) {
    const Units resources_ = resources->GetUnits ( [] ( const Unit &unit ) {
        return unit.unit_type == UNIT_TYPEID // clang-format off
                                ::NEUTRAL_MINERALFIELD ||
               unit.unit_type == UNIT_TYPEID
                                ::NEUTRAL_MINERALFIELD750 ||
               unit.unit_type == UNIT_TYPEID
                                ::NEUTRAL_RICHMINERALFIELD ||
               unit.unit_type == UNIT_TYPEID
                                ::NEUTRAL_RICHMINERALFIELD750 ||
               unit.unit_type == UNIT_TYPEID
                                ::NEUTRAL_PURIFIERMINERALFIELD ||
               unit.unit_type == UNIT_TYPEID
                                ::NEUTRAL_PURIFIERMINERALFIELD750 ||
               unit.unit_type == UNIT_TYPEID
                                ::NEUTRAL_PURIFIERRICHMINERALFIELD ||
               unit.unit_type == UNIT_TYPEID
                                ::NEUTRAL_PURIFIERRICHMINERALFIELD750 ||
               unit.unit_type == UNIT_TYPEID
                                ::NEUTRAL_LABMINERALFIELD ||
               unit.unit_type == UNIT_TYPEID
                                ::NEUTRAL_LABMINERALFIELD750 ||
               unit.unit_type == UNIT_TYPEID
                                ::NEUTRAL_BATTLESTATIONMINERALFIELD ||
               unit.unit_type == UNIT_TYPEID
                                ::NEUTRAL_BATTLESTATIONMINERALFIELD750 ||
               unit.unit_type == UNIT_TYPEID
                                ::NEUTRAL_VESPENEGEYSER ||
               unit.unit_type == UNIT_TYPEID
                                ::NEUTRAL_PROTOSSVESPENEGEYSER ||
               unit.unit_type == UNIT_TYPEID
                                ::NEUTRAL_SPACEPLATFORMGEYSER ||
               unit.unit_type == UNIT_TYPEID
                                ::NEUTRAL_PURIFIERVESPENEGEYSER ||
               unit.unit_type == UNIT_TYPEID
                                ::NEUTRAL_SHAKURASVESPENEGEYSER ||
               unit.unit_type == UNIT_TYPEID
                                ::NEUTRAL_RICHVESPENEGEYSER;
    } ); // clang-format on

    vector<Point3D>                           expansion_locations;
    const vector<pair<Point3D, vector<Unit>>> clusters =
        Cluster ( resources_, parameters.cluster_distance_ );

    vector<size_t>                         query_size;
    vector<QueryInterface::PlacementQuery> queries;
    for ( const pair<Point3D, vector<Unit>> &cluster : clusters ) {
        if ( parameters.debug_ ) {
            for ( const float radius : parameters.radii_ ) {
                parameters.debug_
                    ->DebugSphereOut ( get<0> ( cluster ), radius, Lime );
            }
        }

        // Get the required queries for this cluster.
        size_t query_count = 0;
        for ( const float radius : parameters.radii_ ) {
            query_count += CalculateQueries (
                radius,
                parameters.circle_step_size_,
                get<0> ( cluster ),
                queries
            );
        }

        query_size.push_back ( query_count );
    }

    vector<bool> results     = query->Placement ( queries );
    size_t       start_index = 0;
    for ( int i = 0; i < static_cast<int>(clusters.size( )); ++i ) { // pt3d, vUnit
        const auto & [exp_loc, resources] = clusters[i];
        float   distance = numeric_limits<float>::max( );
        Point2D closest;

        // For each query for the cluster minimum distance location that is
        // valid.
        for ( size_t j = start_index, e = start_index + query_size[i]; j < e;
              ++j )
        {
            if ( !results[j] ) {
                continue;
            }

            const Point2D &pt = queries[j].target_pos;

            if ( const float d = Distance ( pt, exp_loc ); d < distance )
            {
                distance = d;
                closest  = pt;
            }
        }

        const Point3D expansion (
            closest.x,
            closest.y,
            resources.begin( )->pos.z
        );

        if ( parameters.debug_ ) {
            parameters.debug_->DebugSphereOut ( expansion, 0.35F, Red );
        }

        expansion_locations.push_back ( expansion );
        start_index += query_size[i];
    }

    return expansion_locations;
}

} // namespace sc2
