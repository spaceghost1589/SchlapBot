module;
#include <s2clientprotocol/sc2api.pb.h>
export module debug_interface;
import observation_interface;
import protocol_interface;
import common;
import enum_db;
import game_types;
import type_enums;
import unit;


export namespace sc2 {
using namespace std;

enum class AppTest { hang = 1, crash = 2, exit = 3 };

/*! @brief DebugInterface draws debug text, lines and shapes. Available at any
 * time after the game starts. Guaranteed to be valid when the OnStep event is
 * called. All debug actions are queued and dispatched when SendDebug is called.
 * All drawn primitives continue to draw without resending until another
 * SendDebug is called. */
class DebugInterface {
public:
    ObservationInterface& observation_;

    // Debug display.

    struct DebugText
    {
        string   text { "" };
        uint32_t size { 0 };
        Color    color { White };
        bool     has_coords { false };
        Point3D  point;
        bool     is_3d { false };
    };

    vector<DebugText> debug_text_;

    struct DebugLine
    {
        Point3D point_0;
        Point3D point_1;
        Color   color { White };
    };

    vector<DebugLine> debug_lines_;

    struct DebugBox
    {
        Point3D pt_min;
        Point3D pt_max;
        Color   color { White };
    };

    vector<DebugBox> debug_boxes_;

    struct DebugSphere
    {
        Point3D center_pt;
        float   radius;
        Color   color { White };
    };

    vector<DebugSphere> debug_spheres_;

    vector<SC2APIProtocol::DebugGameState> debug_state_;

    struct DebugSetUnitValue
    {
        enum class UnitValue { Energy, Life, Shields };
        UnitValue unit_value;
        float     value;
        Tag       tag;
    };

    vector<DebugSetUnitValue> debug_unit_values_;

    struct DebugUnit
    {
        Point2D    pos;
        uint32_t   player_id;
        UnitTypeID unit_type;
        uint8_t    count;
    };

    vector<DebugUnit> debug_unit_;

    Tags debug_kill_tag_;

    bool    has_move_camera { false };
    Point2D debug_move_camera_;

    bool    app_test_set_ { false };
    AppTest app_test_ { };
    int     app_test_delay_ms_ { 0 };
    bool    endgame_surrender_ { false };
    bool    endgame_victory_ { false };
    bool    set_score_ { false };
    float   score_ { 0.0F };

    DebugInterface ( ObservationInterface& observation )
          : observation_ ( observation ) {}

    virtual ~DebugInterface ( ) = default;

    // Debug drawing primitives.

    /*! @brief Outputs text at the top, left of the screen.
     * @param out The string of text to display.
     * @param text_color Text color (defaults to White) */
    void DebugTextOut ( const string& out, Color text_color = White ) {
        DebugText debug_text;
        debug_text.text       = out;
        debug_text.has_coords = false;
        debug_text.color      = text_color;
        debug_text_.push_back ( debug_text );
    }

    /*! Outputs text at any 2D point on the screen. Coordinate ranges are 0..1
     * in X and Y.
     * @param out The string of text to display.
     * @param pt_virtual_2D The screen position to draw text at.
     * @param color (Optional) Color of the text.
     * @param size (Optional) Pixel height of the text. */
    void DebugTextOut (
        const string&  out,
        const Point2D& pt_virtual_2D,
        Color          color = White,
        uint32_t       size  = 8
    ) {
        DebugText debug_text;
        debug_text.text       = out;
        debug_text.has_coords = true;
        debug_text.is_3d      = false;
        debug_text.point.x    = pt_virtual_2D.x;
        debug_text.point.y    = pt_virtual_2D.y;
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
    void DebugTextOut (
        const string&  out,
        const Point3D& pt3D,
        Color          color = White,
        uint32_t       size  = 8
    ) {
        DebugText debug_text;
        debug_text.text       = out;
        debug_text.has_coords = true;
        debug_text.is_3d      = true;
        debug_text.point.x    = pt3D.x;
        debug_text.point.y    = pt3D.y;
        debug_text.point.z    = pt3D.z;
        debug_text.color      = color;
        debug_text.size       = size;
        debug_text_.push_back ( debug_text );
    }

    //! Outputs a line between two 3D points in the game world. Map coordinates
    //! are used.
    //! @param pt_0 The starting position of the line.
    //! @param pt_1 The ending position of the line.
    //! @param color (Optional) Color of the line.
    void DebugLineOut (
        const Point3D& pt_0, const Point3D& pt_1, Color color = White
    ) {
        DebugLine line;
        line.point_0 = pt_0;
        line.point_1 = pt_1;
        line.color   = color;
        debug_lines_.push_back ( line );
    }

    //! Outputs a box specified as two 3D points in the game world. Map
    //! coordinates are used.
    //! @param p_min One corner of the box.
    //! @param p_max The far corner of the box.
    //! @param color (Optional) Color of the lines.
    void DebugBoxOut (
        const Point3D& p_min, const Point3D& p_max, Color color
    ) {
        DebugBox box;
        box.pt_min = p_min;
        box.pt_max = p_max;
        box.color  = color;
        debug_boxes_.push_back ( box );
    }

    //! Outputs a sphere specified as a 3D point in the game world and a radius.
    //! Map coordinates are used.
    //! @param p Center of the sphere.
    //! @param r Radius of the sphere.
    //! @param color (Optional) Color of the lines.
    void DebugSphereOut ( const Point3D& p, float r, Color color = White ) {
        DebugSphere sphere;
        sphere.center_pt = p;
        sphere.radius    = r;
        sphere.color     = color;
        debug_spheres_.push_back ( sphere );
    }

    // Cheats.

    //! Creates a unit at the given position.
    //! @param unit_type Type of unit to create.
    //! @param p Position to create the unit at.
    //! @param player_id Player the unit should belong to.
    //! @param count Number of units to create.
    void DebugCreateUnit (
        UnitTypeID     unit_type,
        const Point2D& p,
        uint32_t       player_id = 1,
        uint32_t       count     = 1
    ) {
        DebugUnit create_unit;
        create_unit.unit_type = unit_type;
        create_unit.pos       = p;
        create_unit.player_id = player_id;
        create_unit.count     = count;
        debug_unit_.push_back ( create_unit );
    }

    //! Destroy a unit.
    //! @param unit Unit to destroy.
    void DebugKillUnit ( const Unit* unit ) {
        if ( !unit ) {
            return;
        }
        debug_kill_tag_.push_back ( unit->tag );
    }

    //! Makes the entire map visible, i.e., removes the fog-of-war.
    void DebugShowMap ( ) {
        debug_state_.push_back ( SC2APIProtocol::DebugGameState::show_map );
    }

    //! Enables commands to be issued to enemy units.
    void DebugEnemyControl ( ) {
        debug_state_.push_back (
            SC2APIProtocol::DebugGameState::control_enemy
        );
    }

    //! Disables the supply check.
    void DebugIgnoreSupply ( ) {
        debug_state_.push_back ( SC2APIProtocol::DebugGameState::food );
    }

    //! Disables resource checks.
    void DebugIgnoreResourceCost ( ) {
        debug_state_.push_back ( SC2APIProtocol::DebugGameState::free );
    }

    //! Gives a bunch of minerals and gas.
    void DebugGiveAllResources ( ) {
        debug_state_.push_back (
            SC2APIProtocol::DebugGameState::all_resources
        );
    }

    //! Makes the units of a player indestructible.
    void DebugGodMode ( ) {
        debug_state_.push_back ( SC2APIProtocol::DebugGameState::god );
    }

    //! Ignores mineral costs.
    void DebugIgnoreMineral ( ) {
        debug_state_.push_back ( SC2APIProtocol::DebugGameState::minerals );
    }

    //! Ignores gas costs.
    void DebugIgnoreGas ( ) {
        debug_state_.push_back ( SC2APIProtocol::DebugGameState::gas );
    }

    //! Cooldowns become instant.
    void DebugNoCooldowns ( ) {
        debug_state_.push_back ( SC2APIProtocol::DebugGameState::cooldown );
    }

    //! All tech becomes available.
    void DebugGiveAllTech ( ) {
        debug_state_.push_back ( SC2APIProtocol::DebugGameState::tech_tree );
    }

    //! All upgrades are available.
    void DebugGiveAllUpgrades ( ) {
        debug_state_.push_back ( SC2APIProtocol::DebugGameState::upgrade );
    }

    //! Structures and units are built much faster.
    void DebugFastBuild ( ) {
        debug_state_.push_back ( SC2APIProtocol::DebugGameState::fast_build );
    }

    //! Sets the scripted "curriculum" score.
    void DebugSetScore ( float score ) {
        set_score_ = true;
        score_     = score;
    }

    //! Ends a game.
    //! @param victory If true, this player is victorious. If false, this
    //! player surrenders.
    void DebugEndGame ( bool victory ) {
        if ( victory ) {
            endgame_surrender_ = false;
            endgame_victory_   = true;
        } else {
            endgame_surrender_ = true;
            endgame_victory_   = false;
        }
    }

    //! Sets the energy level on a unit.
    //! @param value The new energy level.
    //! @param unit The unit.
    // TODO allow percentage
    void DebugSetEnergy ( float value, const Unit* unit ) {
        if ( !unit ) {
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
    void DebugSetLife ( float value, const Unit* unit ) {
        if ( !unit ) {
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
    void DebugSetShields ( float value, const Unit* unit ) {
        if ( !unit ) {
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
    void DebugMoveCamera ( const Point2D& pos ) {
        has_move_camera    = true;
        debug_move_camera_ = pos;
    }

    //! @brief Cause the game to fail; useful to test library behavior.
    //! @param app_test State to put the game into.
    //! @param delay_ms Time to elapse before invoking the game state.
    void DebugTestApp ( AppTest app_test, int delay_ms = 0 ) {
        app_test_set_      = true;
        app_test_          = app_test;
        app_test_delay_ms_ = delay_ms;
    }

    void DebugClear ( ) {
        debug_text_.clear( );
        debug_lines_.clear( );
        debug_boxes_.clear( );
        debug_spheres_.clear( );

        debug_state_.clear( );
        debug_unit_.clear( );
        debug_kill_tag_.clear( );
        debug_unit_values_.clear( );
    }

    //! Dispatch all queued debug commands. No debug commands will be sent until
    //! this is called. This will also clear or set new debug primitives like
    //! text and lines.
    void SendDebug ( ) {
        const GameRequestPtr          request       = ProtoFace::MakeRequest( );
        SC2APIProtocol::RequestDebug* request_debug = request->mutable_debug( );

        for ( const DebugText& entry : debug_text_ ) {
            SC2APIProtocol::DebugCommand* command = request_debug->add_debug( );
            SC2APIProtocol::DebugText*    debug_text =
                command->mutable_draw( )->add_text( );
            debug_text->set_text ( entry.text );
            debug_text->set_size ( entry.size );
            if ( entry.has_coords ) {
                if ( entry.is_3d ) {
                    SC2APIProtocol::Point* pos =
                        debug_text->mutable_world_pos( );
                    pos->set_x ( entry.point.x );
                    pos->set_y ( entry.point.y );
                    pos->set_z ( entry.point.z );
                } else {
                    SC2APIProtocol::Point* pos =
                        debug_text->mutable_virtual_pos( );
                    pos->set_x ( entry.point.x );
                    pos->set_y ( entry.point.y );
                }
            }
            SC2APIProtocol::Color* color_text = debug_text->mutable_color( );
            color_text->set_r ( entry.color.R );
            color_text->set_g ( entry.color.G );
            color_text->set_b ( entry.color.B );
        }

        for ( const DebugLine& line : debug_lines_ ) {
            SC2APIProtocol::DebugCommand* command = request_debug->add_debug( );
            SC2APIProtocol::DebugLine*    debug_line =
                command->mutable_draw( )->add_lines( );
            SC2APIProtocol::Line* proto_line = debug_line->mutable_line( );

            SC2APIProtocol::Point* p0 = proto_line->mutable_p0( );
            p0->set_x ( line.point_0.x );
            p0->set_y ( line.point_0.y );
            p0->set_z ( line.point_0.z );

            SC2APIProtocol::Point* p1 = proto_line->mutable_p1( );
            p1->set_x ( line.point_1.x );
            p1->set_y ( line.point_1.y );
            p1->set_z ( line.point_1.z );

            SC2APIProtocol::Color* color_line = debug_line->mutable_color( );
            color_line->set_r ( line.color.R );
            color_line->set_g ( line.color.G );
            color_line->set_b ( line.color.B );
        }

        for ( const DebugBox& box : debug_boxes_ ) {
            SC2APIProtocol::DebugCommand* command = request_debug->add_debug( );
            SC2APIProtocol::DebugBox*     debug_box =
                command->mutable_draw( )->add_boxes( );

            SC2APIProtocol::Point* p_min = debug_box->mutable_min( );
            p_min->set_x ( box.pt_min.x );
            p_min->set_y ( box.pt_min.y );
            p_min->set_z ( box.pt_min.z );

            SC2APIProtocol::Point* p_max = debug_box->mutable_max( );
            p_max->set_x ( box.pt_max.x );
            p_max->set_y ( box.pt_max.y );
            p_max->set_z ( box.pt_max.z );

            SC2APIProtocol::Color* color_box = debug_box->mutable_color( );
            color_box->set_r ( box.color.R );
            color_box->set_g ( box.color.G );
            color_box->set_b ( box.color.B );
        }

        for ( const DebugSphere& sphere : debug_spheres_ ) {
            SC2APIProtocol::DebugCommand* command = request_debug->add_debug( );
            SC2APIProtocol::DebugSphere*  debug_sphere =
                command->mutable_draw( )->add_spheres( );

            SC2APIProtocol::Point* p = debug_sphere->mutable_p( );
            p->set_x ( sphere.center_pt.x );
            p->set_y ( sphere.center_pt.y );
            p->set_z ( sphere.center_pt.z );

            debug_sphere->set_r ( sphere.radius );

            SC2APIProtocol::Color* color_sphere =
                debug_sphere->mutable_color( );
            color_sphere->set_r ( sphere.color.R );
            color_sphere->set_g ( sphere.color.G );
            color_sphere->set_b ( sphere.color.B );
        }

        for ( const DebugSetUnitValue& set_unit_value : debug_unit_values_ ) {
            SC2APIProtocol::DebugCommand* command = request_debug->add_debug( );
            SC2APIProtocol::DebugSetUnitValue* unit_value =
                command->mutable_unit_value( );
            switch ( set_unit_value.unit_value ) {
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

        for ( const SC2APIProtocol::DebugGameState& state : debug_state_ ) {
            SC2APIProtocol::DebugCommand* command = request_debug->add_debug( );
            command->set_game_state ( state );
        }

        for ( const DebugUnit& unit : debug_unit_ ) {
            if ( unit.count < 1 ) {
                continue;
            }

            SC2APIProtocol::DebugCommand* command = request_debug->add_debug( );
            SC2APIProtocol::DebugCreateUnit* create_unit =
                command->mutable_create_unit( );
            create_unit->set_unit_type ( unit.unit_type );
            create_unit->set_owner ( unit.player_id );
            SC2APIProtocol::Point2D* point = create_unit->mutable_pos( );
            point->set_x ( unit.pos.x );
            point->set_y ( unit.pos.y );
            create_unit->set_quantity ( unit.count );
        }

        if ( !debug_kill_tag_.empty( ) ) {
            SC2APIProtocol::DebugCommand* command = request_debug->add_debug( );
            SC2APIProtocol::DebugKillUnit* debug_kill_unit =
                command->mutable_kill_unit( );
            for ( const Tag tag : debug_kill_tag_ ) {
                debug_kill_unit->add_tag ( tag );
            }
        }

        if ( app_test_set_ ) {
            SC2APIProtocol::DebugCommand* command = request_debug->add_debug( );
            SC2APIProtocol::DebugTestProcess* test_process =
                command->mutable_test_process( );
            test_process->set_test (
                static_cast<SC2APIProtocol::DebugTestProcess_Test> ( app_test_ )
            );
            test_process->set_delay_ms ( app_test_delay_ms_ );
        }

        if ( set_score_ ) {
            SC2APIProtocol::DebugCommand* command = request_debug->add_debug( );
            SC2APIProtocol::DebugSetScore* set_score =
                command->mutable_score( );
            set_score->set_score ( score_ );
        }
        set_score_ = false;
        score_     = 0.0F;

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

        ProtoFace::SendRequest ( request );
        DebugClear( );

        // Wait for the response.
        ProtoFace::WaitForResponse( );

        if ( has_move_camera ) {
            const GameRequestPtr camera_request = ProtoFace::MakeRequest( );
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
}; // class DebugInterface

} // namespace sc2
