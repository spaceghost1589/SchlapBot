module;
#include <s2clientprotocol/debug.pb.h>
#include <s2clientprotocol/raw.pb.h>

#include "api/interfaces.h"
#include "api/unit.h"
export module Client:debug_interface;
import points;
import enum_db;

namespace {

class ProtocolInterface;
class ObservationInterface;
class ControlInterface;

} // namespace

namespace sc2 {


//! DebugInterface draws debug text, lines and shapes. Available at any time
//! after the game starts. Guaranteed to be valid when the OnStep event is
//! called. All debug actions are queued and dispatched when SendDebug is
//! called. All drawn primitives continue to draw without resending until
//! another SendDebug is called.
class DebugInterface {
public:
    ProtocolInterface&    proto_;
    ObservationInterface& observation_;
    ControlInterface&     control_;

    // Debug display.

    struct DebugText {
        string   text;
        bool     has_coords;
        bool     is_3d;
        Point3D  pt;
        Color    color;
        uint32_t size = 0;
    };

    vector<DebugText> debug_text_;

    struct DebugLine {
        Point3D p0;
        Point3D p1;
        Color   color;
    };

    vector<DebugLine> debug_line_;

    struct DebugBox {
        Point3D p_min;
        Point3D p_max;
        Color   color;
    };

    vector<DebugBox> debug_box_;

    struct DebugSphere {
        Point3D p_;
        float   r_;
        Color   color_;
    };

    vector<DebugSphere> debug_sphere_;

    vector<SC2APIProtocol::DebugGameState> debug_state_;

    struct DebugSetUnitValue {
        enum class UnitValue { Energy, Life, Shields };
        UnitValue unit_value;
        float     value;
        Tag       tag;
    };

    vector<DebugSetUnitValue> debug_unit_values_;

    struct DebugUnit {
        UnitTypeID unit_type;
        Point2D    pos;
        uint32_t   player_id;
        uint32_t   count;
    };

    vector<DebugUnit> debug_unit_;


    Tags debug_kill_tag_;

    bool    has_move_camera;
    Point2D debug_move_camera_;

    bool    app_test_set_ {true};
    AppTest app_test_ {0};
    int     app_test_delay_ms_ { };
    bool    endgame_surrender_;
    bool    endgame_victory_;
    bool    set_score_;
    float   score_;

    DebugInterface ( );

    virtual ~DebugInterface ( );

    DebugInterface (
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

    //! Outputs text at the top, left of the screen.
    //! \param out The string of text to display.
    //! \param color (Optional) Color of the text.
    virtual void DebugTextOut (const string& out, Color color = White) {
        DebugText debug_text;
        debug_text.text       = out;
        debug_text.has_coords = false;
        debug_text.color      = color;
        debug_text_.push_back (debug_text);
    }

    // Debug drawing primitives.

    //! Outputs text at any 2D point on the screen. Coordinate ranges are 0..1
    //! in X and Y.
    //! \param out The string of text to display.
    //! \param pt_virtual_2D The screen position to draw text at.
    //! \param color (Optional) Color of the text.
    //! \param size (Optional) Pixel height of the text.
    virtual void DebugTextOut (
            const string&  out,
            const Point2D& pt_virtual_2D,
            Color          color = White,
            uint32_t       size  = 8
    ) {
        DebugText debug_text;
        debug_text.text       = out;
        debug_text.has_coords = true;
        debug_text.is_3d      = false;
        debug_text.pt.x       = pt_virtual_2D.x;
        debug_text.pt.y       = pt_virtual_2D.y;
        debug_text.color      = color;
        debug_text.size       = size;
        debug_text_.push_back (debug_text);
    }

    //! Outputs text at any 3D point in the game world. Map coordinates are
    //! used.
    //! \param out The string of text to display.
    //! \param pt3D The world position to draw text at.
    //! \param color (Optional) Color of the text.
    //! \param size (Optional) Pixel height of the text.
    virtual void DebugTextOut (
            const string&  out,
            const Point3D& pt3D,
            Color          color = White,
            uint32_t       size  = 8
    ) {
        DebugText debug_text;
        debug_text.text       = out;
        debug_text.has_coords = true;
        debug_text.is_3d      = true;
        debug_text.pt.x       = pt3D.x;
        debug_text.pt.y       = pt3D.y;
        debug_text.pt.z       = pt3D.z;
        debug_text.color      = color;
        debug_text.size       = size;
        debug_text_.push_back (debug_text);
    }

    //! Outputs a line between two 3D points in the game world. Map coordinates
    //! are used.
    //! \param p0 The starting position of the line.
    //! \param p1 The ending position of the line.
    //! \param color (Optional) Color of the line.
    virtual void DebugLineOut (
            const Point3D& p0, const Point3D& p1, Color color = White
    ) {
        DebugLine line;
        line.p0    = p0;
        line.p1    = p1;
        line.color = color;
        debug_line_.push_back (line);
    }

    // TODO these two (above & below) may be the same
    //! Outputs a box specified as two 3D points in the game world. Map
    //! coordinates are used.
    //! \param p_min One corner of the box.
    //! \param p_max The far corner of the box.
    //! \param color (Optional) Color of the lines.
    virtual void DebugBoxOut (
            const Point3D& p_min, const Point3D& p_max, Color color = White
    ) {
        DebugBox box;
        box.p_min = p_min;
        box.p_max = p_max;
        box.color = color;
        debug_box_.push_back (box);
    }

    //! Outputs a sphere specified as a 3D point in the game world and a radius.
    //! Map coordinates are used.
    //! \param p Center of the sphere.
    //! \param r Radius of the sphere.
    //! \param color (Optional) Color of the lines.
    virtual void DebugSphereOut (
            const Point3D& p, float r, Color color = White
    ) {
        DebugSphere sphere;
        sphere.p_     = p;
        sphere.r_     = r;
        sphere.color_ = color;
        debug_sphere_.push_back (sphere);
    }

    // Cheats.

    //! Creates a unit at the given position.
    //! \param unit_type Type of unit to create.
    //! \param p Position to create the unit at.
    //! \param player_id Player the unit should belong to.
    //! \param count Number of units to create.
    virtual void DebugCreateUnit (
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
        debug_unit_.push_back (create_unit);
    }

    //! Destroy a unit.
    //! \param unit Unit to destroy.
    virtual void DebugKillUnit (const Unit* unit) {
        if ( !unit ) {
            return;
        }
        debug_kill_tag_.push_back (unit->tag);
    }

    //! Makes the entire map visible, i.e., removes the fog-of-war.
    virtual void DebugShowMap ( ) {
        debug_state_.push_back (SC2APIProtocol::DebugGameState::show_map);
    }

    //! Enables commands to be issued to enemy units.
    virtual void DebugEnemyControl ( ) {
        debug_state_.push_back (SC2APIProtocol::DebugGameState::control_enemy);
    }

    //! Disables the supply check.
    virtual void DebugIgnoreSupply ( ) {
        debug_state_.push_back (SC2APIProtocol::DebugGameState::food);
    }

    //! Disables resource checks.
    virtual void DebugIgnoreResourceCost ( ) {
        debug_state_.push_back (SC2APIProtocol::DebugGameState::free);
    }

    //! Gives a bunch of minerals and gas.
    virtual void DebugGiveAllResources ( ) {
        debug_state_.push_back (SC2APIProtocol::DebugGameState::all_resources);
    }

    //! Makes the units of a player indestructible.
    virtual void DebugGodMode ( ) {
        debug_state_.push_back (SC2APIProtocol::DebugGameState::god);
    }

    //! Ignores mineral costs.
    virtual void DebugIgnoreMineral ( ) {
        debug_state_.push_back (SC2APIProtocol::DebugGameState::minerals);
    }

    //! Ignores gas costs.
    virtual void DebugIgnoreGas ( ) {
        debug_state_.push_back (SC2APIProtocol::DebugGameState::gas);
    }

    //! Cooldowns become instant.
    virtual void DebugNoCooldowns ( ) {
        debug_state_.push_back (SC2APIProtocol::DebugGameState::cooldown);
    }

    //! All tech becomes available.
    virtual void DebugGiveAllTech ( ) {
        debug_state_.push_back (SC2APIProtocol::DebugGameState::tech_tree);
    }

    //! All upgrades are available.
    virtual void DebugGiveAllUpgrades ( ) {
        debug_state_.push_back (SC2APIProtocol::DebugGameState::upgrade);
    }

    //! Structures and units are built much faster.
    virtual void DebugFastBuild ( ) {
        debug_state_.push_back (SC2APIProtocol::DebugGameState::fast_build);
    }

    //! Sets the scripted "curriculum" score.
    virtual void DebugSetScore (float score) {
        set_score_ = true;
        score_     = score;
    }

    //! Ends a game.
    //! \param victory If true, this player is victorious. If false, this player
    //! surrenders.
    virtual void DebugEndGame (bool victory = false) {
        if ( victory ) {
            endgame_surrender_ = false;
            endgame_victory_   = true;
        } else {
            endgame_surrender_ = true;
            endgame_victory_   = false;
        }
    }

    //! Sets the energy level on a unit.
    //! \param value The new energy level.
    //! \param unit
    virtual void DebugSetEnergy (float value, const Unit* unit) {
        if ( !unit ) {
            return;
        }
        DebugSetUnitValue unit_value;
        unit_value.unit_value = DebugSetUnitValue::UnitValue::Energy;
        unit_value.value      = value;
        unit_value.tag        = unit->tag;
        debug_unit_values_.push_back (unit_value);
    }

    //! Sets the life on a unit.
    //! \param value The new life.
    //! \param unit
    virtual void DebugSetLife (float value, const Unit* unit) {
        if ( !unit ) {
            return;
        }
        DebugSetUnitValue unit_value;
        unit_value.unit_value = DebugSetUnitValue::UnitValue::Life;
        unit_value.value      = value;
        unit_value.tag        = unit->tag;
        debug_unit_values_.push_back (unit_value);
    }

    //! Sets shields on a unit.
    //! \param value The new shields.
    //! \param unit
    virtual void DebugSetShields (float value, const Unit* unit) {
        if ( !unit ) {
            return;
        }
        DebugSetUnitValue unit_value;
        unit_value.unit_value = DebugSetUnitValue::UnitValue::Shields;
        unit_value.value      = value;
        unit_value.tag        = unit->tag;
        debug_unit_values_.push_back (unit_value);
    }

    //! Sets the position of the camera.
    //! \param pos The camera position in world space.
    virtual void DebugMoveCamera (const Point2D& pos) {
        has_move_camera    = true;
        debug_move_camera_ = pos;
    }

    //! Cause the game to fail; useful to test library behavior.
    //! \param app_test State to put the game into.
    //! \param delay_ms Time to elapse before invoking the game state.
    void DebugTestApp (AppTest app_test, int delay_ms = 0) {
        app_test_set_      = true;
        app_test_          = app_test;
        app_test_delay_ms_ = delay_ms;
    }

    //! Dispatch all queued debug commands. No debug commands will be sent until
    //! this is called. This will also clear or set new debug primitives like
    //! text and lines.
    void SendDebug ( );
};

} // namespace sc2
