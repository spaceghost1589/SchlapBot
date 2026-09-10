module;
#include <s2clientprotocol/sc2api.pb.h>
export module observer_action_interface;
import protocol_interface;
import point;

export namespace sc2 {

/*! The ObserverActionInterface corresponds to the actions available in the
 * observer UI. */
class ObserverActionInterface final {
public:
    GameRequestPtr request_ { nullptr };

    explicit ObserverActionInterface ( ) = default;

    SC2APIProtocol::RequestObserverAction *GetRequest ( ) {
        if ( request_ == nullptr ) {
            request_ = ProtoFace::MakeRequest( );
        }
        return request_->mutable_obs_action( );
    }

    /*! @brief Moves the observer camera to a target location. Will cause the
     * camera to stop following the observed player's perspective.
     * @param point The 2D world position to target.
     * @param distance Distance between camera and terrain. Larger value zooms
     * out camera. Defaults to standard camera distance if set to 0. */
    void CameraMove ( const Point2D &point, const float distance = 0.0F ) {
        SC2APIProtocol::RequestObserverAction *request = GetRequest( );
        SC2APIProtocol::ObserverAction        *action = request->add_actions( );
        SC2APIProtocol::ActionObserverCameraMove *camera_move =
            action->mutable_camera_move( );
        camera_move->set_distance ( distance );
        camera_move->mutable_world_pos( )->set_x ( point.x );
        camera_move->mutable_world_pos( )->set_y ( point.y );
    }

    /*! @brief Makes the observer camera follow the observed player's
     * perspective. */
    void CameraFollowPlayer ( ) {
        SC2APIProtocol::RequestObserverAction *request = GetRequest( );
        SC2APIProtocol::ObserverAction        *action = request->add_actions( );
        action->mutable_camera_follow_player( );
    }

    /*! @brief This function sends out all batched commands. You DO NOT need to
     * call this function. It's automatically called when stepping the
     * simulation forward. */
    void SendActions ( ) {
        if ( request_ == nullptr ) {
            return;
        }

        if ( !ProtoFace::SendRequest ( request_ ) ) {
            return;
        }

        request_ = nullptr;
        ProtoFace::WaitForResponse( );
    }

}; // ObserverActionInterface

} // namespace sc2
