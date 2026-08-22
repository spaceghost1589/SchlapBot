/*! \file interfaces.h
    \brief A set of public facing interfaces used to query game state.

Each function in this class is pure virtual but is not intended for a user of the API to overwrite.
An implementation file that utilizes this interface will be responsible for its definition and should
be of little concern to the consumer.
*/

#pragma once

#include "api/data.h"
#include "api/unit.h"
#include "lib/action.h"

import map_info;
import points;
import renderer;

enum class UNIT_TYPEID;
enum class ABILITY_ID;


namespace sc2 {

//! The ActionFeatureLayerInterface emulates UI actions in feature layer. Not available in replays.
//! Guaranteed to be valid when the OnStep event is called.
class ActionFeatureLayerInterface {
public:
    virtual ~ActionFeatureLayerInterface() = default;

    //! Issues a command to whatever is selected. Self targeting.
    //! \param ability The ability id of the command.
    virtual void UnitCommand(AbilityID ability) = 0;

    //! Issues a command to whatever is selected. Uses a point as a target for the command.
    //! \param ability The ability id of the command.
    //! \param point The 2D world position to target.
    //! \param minimap Target in the minimap instead of the map.
    virtual void UnitCommand(AbilityID ability, const Point2DI& point,
                             bool minimap = false) = 0;

    //! Moves the camera to be centered around a position. Coordinate is position on minimap feature layer.
    virtual void CameraMove(const Point2DI& center) = 0;

    //! Selection of a point, equivalent to clicking the mouse on a unit.
    //! \param center The feature layer 'pixel' being clicked on.
    //! \param selection_type Any modifier keys, for example if 'shift-click' is desired.
    virtual void Select(const Point2DI& center,
                        PointSelectionType selection_type) = 0;

    //! Selection of an area, equivalent to click-dragging the mouse over an area of the screen.
    //! \param p0 The feature layer pixel where the first click occurs (mouse button down).
    //! \param p1 The feature layer pixel where the drag release occurs (mouse button up).
    //! \param add_to_selection Will add newly selected units to an existing selection.
    virtual void Select(const Point2DI& p0, const Point2DI& p1,
                        bool add_to_selection = false) = 0;

    //! This function sends out all batched selection and unit commands. You DO NOT need to call this function in non
    //! real time simulations since it is automatically called when stepping the simulation forward. You only need to
    //! call this function in a real time simulation.
    virtual void SendActions() = 0;
};

//! The ObserverActionInterface corresponds to the actions available in the observer UI.
class ObserverActionInterface {
public:
    virtual ~ObserverActionInterface() = default;

    //! Moves the observer camera to a target location. Will cause the camera to stop following
    //! the observed player's perspective.
    //! \param point The 2D world position to target.
    //! \param distance Distance between camera and terrain. Larger value zooms out camera. Defaults to standard camera
    //! distance if set to 0.
    virtual void CameraMove(const Point2D& point, float distance = 0.0f) = 0;

    //! Makes the observer camera follow the observed player's perspective.
    virtual void CameraFollowPlayer() = 0;

    //! This function sends out all batched commands. You DO NOT need to call this function.
    //! it is automatically called when stepping the simulation forward.
    virtual void SendActions() = 0;
};

};
} // namespace sc2
