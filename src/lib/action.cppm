module;
#include <cstdint>
#include <vector>
export module action;
import point;
import game_types;
import type_enums;

namespace {

using std::uint8_t;
using std::vector;

} // namespace

export namespace sc2 {
// using namespace std;

//! An action (command or ability) applied to a unit or set of units.
struct ActionRaw
{
    //! Type of target. Target types are mutually exclusive.
    enum class TargetType : uint8_t {
        //! No target generally means 'self', e.g., a order to make a unit.
        TargetNone,
        /*! The target is a unit tag, could also be a snapshot in the
           fog-of-war. */
        TargetUnitTag,
        //! The target is a point.
        TargetPosition,
    };
    using enum TargetType;

    /*! Units this action applies to. In normal use, this would be the currently
     * selected units. */
    vector<Tag> unit_tags;
    //! The target of this action. Valid only when target_type == TargetUnitTag.
    Tag         target_tag { NullTag };
    /*! The target point for this action.\n\n
     * Valid only when target_type == TargetPosition. */
    Point2D     target_point { };
    //! The ID of the ability to invoke.
    AbilityID   ability_id { 0 };
    //! Which target fields are valid.
    TargetType  target_type { TargetNone };

    //! Comparison overload.

    bool operator == ( const ActionRaw &action_raw ) const {
        if ( ability_id != action_raw.ability_id ) {
            return false;
        }
        if ( target_type != action_raw.target_type ) {
            return false;
        }
        if ( target_tag != action_raw.target_tag ) {
            return false;
        }
        if ( target_point.x != action_raw.target_point.x ) {
            return false;
        }
        if ( target_point.y != action_raw.target_point.y ) {
            return false;
        }
        return true;
    }
};

using RawActions = vector<ActionRaw>;

//! An action (command or ability) applied to selected units when using feature
//! layers or the rendered interface.
struct SpatialUnitCommand
{
    //! If this action should apply to the screen or minimap.
    enum class SpatialTargetType : uint8_t {
        //! Apply this action to the main game screen.
        TargetScreen,
        //! Apply this action to the minimap.
        TargetMinimap,
    };
    using enum SpatialTargetType;

    //! The ID of the ability to invoke.
    AbilityID         ability_id { };
    //! If this action should be applied to the main game screen or the minimap.
    SpatialTargetType target_type { TargetScreen };
    //! Target point on the screen or minimap, if required.
    Point2DI          target { };
    //! Indicates if this action should replace or queue behind other actions.
    bool              queued { };
};

//! Where to move the camera to on the minimap.
struct SpatialCameraMove
{
    Point2DI center_minimap { };
};

//! Types of selection.
enum class PointSelectionType : uint8_t {
    //! Equivalent to normal click. Changes selection to unit.
    PtSelect     = 1,
    //! Equivalent to shift+click. Toggle selection of unit.
    PtToggle     = 2,
    //! Equivalent to control+click. Selects all units of a given type.
    PtAllType    = 3,
    //! Equivalent to shift+control+click. Selects all units of a given type.
    PtAddAllType = 4,
};
using enum PointSelectionType;

//! Point selection.
struct SpatialSelectPoint
{
    Point2DI           select_screen { };
    PointSelectionType type { PtSelect };
};

//! Rectangle selection. Equivalent to click-drag with the mouse. Multiple
//! rectangles are allowed as the feature layer projection is orthogonal, and
//! may not exactly work for the regular in-game perspective view.
struct SpatialSelectRect
{
    vector<Rect2DI> select_screen { };
    bool            select_add { };
};

//! Possible actions for feature layers.
struct SpatialActions
{
    //! Commands to selected units.
    vector<SpatialUnitCommand> unit_commands { };
    //! Camera movement.
    vector<SpatialCameraMove>  camera_moves { };
    //! Selecting by point.
    vector<SpatialSelectPoint> select_points { };
    //! Selecting by rectangles.
    vector<SpatialSelectRect>  select_rects { };
};

} // namespace sc2
