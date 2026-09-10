module;
#include "s2clientprotocol/sc2api.pb.h"
export module action_feature_layer_interface;
import protocol_interface;
import action;
import point;
import type_enums;

export namespace sc2 {

/*! The ActionFeatureLayerInterface emulates UI actions in feature layer.\n\n
 * Guaranteed to be valid when the OnStep event is called.\n\n
 * Not available in replays. */
class ActionFeatureLayerInterface final
{
public:
    GameRequestPtr request_actions_;

    ActionFeatureLayerInterface ( ) {}

    SC2APIProtocol::RequestAction* GetRequestAction ( ) {
        if ( request_actions_ == nullptr ) {
            request_actions_ = ProtoFace::MakeRequest( );
        }
        return request_actions_->mutable_action( );
    } // GetRequestAction

    /*! @brief Issues a command to whatever is selected. Self targeting.
     * @param ability The ability id of the command. */
    void UnitCommand (const AbilityID ability ) {
        SC2APIProtocol::RequestAction* request_action = GetRequestAction( );
        SC2APIProtocol::Action*        action = request_action->add_actions( );
        SC2APIProtocol::ActionSpatial* action_feature_layer =
            action->mutable_action_feature_layer( );
        SC2APIProtocol::ActionSpatialUnitCommand* unit_command =
            action_feature_layer->mutable_unit_command( );
        unit_command->set_ability_id ( ability );
    } // UnitCommand

    /*! @brief Issues a command to whatever is selected. Uses a point as a
     * target for the command.
     * @param ability The ability id of the command.
     * @param point The 2D world position to target.
     * @param minimap Target in the minimap instead of the map. */
    void UnitCommand (
        const AbilityID ability, const Point2DI& point, const bool minimap = false
    ) {
        SC2APIProtocol::RequestAction* request_action = GetRequestAction( );
        SC2APIProtocol::Action*        action = request_action->add_actions( );
        SC2APIProtocol::ActionSpatial* action_feature_layer =
            action->mutable_action_feature_layer( );
        SC2APIProtocol::ActionSpatialUnitCommand* unit_command =
            action_feature_layer->mutable_unit_command( );

        SC2APIProtocol::PointI* pt;
        if ( minimap ) {
            pt = unit_command->mutable_target_minimap_coord( );
        } else {
            pt = unit_command->mutable_target_screen_coord( );
        }
        pt->set_x ( point.x );
        pt->set_y ( point.y );
        unit_command->set_ability_id ( ability );
    } // UnitCommand

    /*! @brief Moves the camera to be centered around a position. Coordinate is
     * position on minimap feature layer. */
    void CameraMove ( const Point2DI& center ) {
        SC2APIProtocol::RequestAction* request_action = GetRequestAction( );
        SC2APIProtocol::Action*        action = request_action->add_actions( );
        SC2APIProtocol::ActionSpatial* action_feature_layer =
            action->mutable_action_feature_layer( );
        SC2APIProtocol::ActionSpatialCameraMove* camera_move =
            action_feature_layer->mutable_camera_move( );

        SC2APIProtocol::PointI* center_proto =
            camera_move->mutable_center_minimap( );
        center_proto->set_x ( center.x );
        center_proto->set_y ( center.y );
    } // CameraMove

    /*! @brief Selection of a point, equivalent to clicking the mouse on a unit.
     * @param center The feature layer 'pixel' being clicked on.
     * @param selection_type Any modifier keys, for example if 'shift-click' is
     * desired. */
    void SelectPoint ( const Point2DI& center, PointSelectionType selection_type ) {
        SC2APIProtocol::RequestAction* request_action = GetRequestAction( );
        SC2APIProtocol::Action*        action = request_action->add_actions( );
        SC2APIProtocol::ActionSpatial* action_feature_layer =
            action->mutable_action_feature_layer( );
        SC2APIProtocol::ActionSpatialUnitSelectionPoint* select_pt =
            action_feature_layer->mutable_unit_selection_point( );

        SC2APIProtocol::PointI* center_proto =
            select_pt->mutable_selection_screen_coord( );
        center_proto->set_x ( center.x );
        center_proto->set_y ( center.y );
        select_pt->set_type (
            static_cast<SC2APIProtocol::ActionSpatialUnitSelectionPoint_Type> (
                selection_type
            )
        );
    } // SelectPoint

    /*! @brief Selection of an area, equivalent to click-dragging the mouse over
     * an area of the screen.
     * @param p0 The feature layer pixel where the first click occurs (mouse
     * button down).
     * @param p1 The feature layer pixel where the drag release occurs (mouse
     * button up).
     * @param add_to_selection Will add newly selected units to an existing
     * selection. */
    void SelectRect (
        const Point2DI& p0, const Point2DI& p1, bool add_to_selection = false
    ) {
        SC2APIProtocol::RequestAction* request_action = GetRequestAction( );
        SC2APIProtocol::Action*        action = request_action->add_actions( );
        SC2APIProtocol::ActionSpatial* action_feature_layer =
            action->mutable_action_feature_layer( );
        SC2APIProtocol::ActionSpatialUnitSelectionRect* select_rect =
            action_feature_layer->mutable_unit_selection_rect( );
        SC2APIProtocol::RectangleI* selection_screen_coord =
            select_rect->add_selection_screen_coord( );
        SC2APIProtocol::PointI* selection_p0 =
            selection_screen_coord->mutable_p0( );
        selection_p0->set_x ( p0.x );
        selection_p0->set_y ( p0.y );
        SC2APIProtocol::PointI* selection_p1 =
            selection_screen_coord->mutable_p1( );
        selection_p1->set_x ( p1.x );
        selection_p1->set_y ( p1.y );
    } // SelectRect

    /*! @brief This function sends out all batched selection and unit commands.
     * You DO NOT need to call this function in non real time simulations since
     * it is automatically called when stepping the simulation forward. You only
     * need to call this function in a real time simulation. */
    void SendActions ( ) {
        if ( request_actions_ == nullptr ) {
            return;
        }

        if ( !ProtoFace::SendRequest ( request_actions_ ) ) {
            return;
        }

        request_actions_ = nullptr;
        ProtoFace::WaitForResponse( );
    } // SendActions
}; // ActionFeatureLayerInterface

} // namespace sc2
