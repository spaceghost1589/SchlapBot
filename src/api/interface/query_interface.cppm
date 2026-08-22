module;
#include "api/data.h"
#include "api/unit.h"
export module Client:query_interface;
import enum_db;

namespace {

class ProtocolInterface;
class ObservationInterface;
class ControlInterface;

} // namespace

namespace sc2 {

class QueryInterface {
public:
    ProtocolInterface&    proto_;
    ControlInterface&     control_;
    ObservationInterface& observation_;

    QueryInterface ( );

    virtual ~QueryInterface ( ) = default;

    QueryInterface (
            ProtocolInterface&    proto,
            ControlInterface&     control,
            ObservationInterface& observation
    ):
        proto_ (proto), control_ (control), observation_ (observation) {}

    virtual AvailableAbilities GetAbilitiesForUnit (
            const Unit* unit,
            bool        ignore_resource_requirements,
            bool        use_generalized_ability_id
    );

    virtual vector<AvailableAbilities> GetAbilitiesForUnits (
            const Units& units,
            bool         ignore_resource_requirements,
            bool         use_generalized_ability_id
    );

    struct PathingQuery {
        Tag     start_unit_tag_ = NullTag;
        Point2D start_;
        Point2D end_;
    };

    //! Returns pathing distance between two locations. Takes into account unit
    //! movement properties (e.g. Flying).
    //! \param start Starting point.
    //! \param end End point.
    //! \return Distance between the two points.
    virtual float PathingDistance (const Point2D& start, const Point2D& end) {
        vector<PathingQuery> queries;

        PathingQuery query;
        query.start_ = start;
        query.end_   = end;
        queries.push_back (query);

        const vector<float> distances = PathingDistance (queries);
        return distances[0];
    }

    //! Issues multiple pathing queries.
    virtual vector<float> PathingDistance (const vector<PathingQuery>& queries);

    struct PlacementQuery {
        PlacementQuery ( ) = default;

        PlacementQuery (AbilityID ability_id, Point2D target):
            ability (ability_id), target_pos (target) {}

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
        queries.push_back (query);

        vector<bool> results = Placement (queries);
        return results[0];
    }

    //! A batch version of the above Placement query. Takes an array of
    //! abilities, positions and optional unit tags and returns a matching array
    //! of bools indicating if placement is possible.
    //! \param queries Placement queries.
    //! \return Array of bools indicating if placement is possible.
    virtual vector<bool> Placement (const vector<PlacementQuery>& queries);

}; // class QueryInterface

} // namespace sc2
