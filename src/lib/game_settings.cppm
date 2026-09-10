module;
#include <cstdint>
#include <string>
#include <vector>
export module game_settings;
import game_types;

export namespace sc2 {
using namespace std;

//! Information about a running process.
struct ProcessInfo
{
    ProcessInfo ( ) = default;

    ProcessInfo ( const string &path, const uint64_t id, const int port )
        : process_path ( path ),
          process_id ( id ),
          port ( port ) { }

    string   process_path;
    uint64_t process_id;
    int      port;
};

//! Settings to run the game process.
struct ProcessSettings
{
    bool   realtime;
    int    step_size;
    string process_path;
    string data_version;
    string net_address;
    int    timeout_ms;
    int    port_start;
    bool   multi_threaded { false }; // Run all OnSteps in parallel.
    bool   full_screen { false };
    vector<string>
        extra_command_lines; // PID and port of all running sc2 processes.

    vector<ProcessInfo> process_info;

    ProcessSettings ( ) = default;

    ProcessSettings (
        const bool    in_real_time,
        const int     in_step_size,
        const string &in_process_path,
        const string &in_net_address,
        const int     in_timeout_ms,
        const int     in_port_start,
        const bool    in_multi_threaded = false,
        const bool    in_full_screen    = false
    )
        : realtime ( in_real_time ),
          step_size ( in_step_size ),
          process_path ( in_process_path ),
          net_address ( in_net_address ),
          timeout_ms ( in_timeout_ms ),
          port_start ( in_port_start ),
          multi_threaded ( in_multi_threaded ),
          full_screen ( in_full_screen ) { }
};

//! Settings for an RGB rendered output.
struct RenderSettings
{
    RenderSettings ( ) = default;

    RenderSettings (
        const int map_x,
        const int map_y,
        const int minimap_x,
        const int minimap_y
    )
        : map_x ( map_x ),
          map_y ( map_y ),
          minimap_x ( minimap_x ),
          minimap_y ( minimap_y ) { }

    //! X size of rendered bitmap for the world screen.
    int map_x     = 800;
    //! Y size of rendered bitmap for the world screen.
    int map_y     = 600;
    //! X size of rendered bitmap for the minimap.
    int minimap_x = 300;
    //! Y size of rendered bitmap for the minimap.
    int minimap_y = 300;
};

//! Settings for feature layer output.
struct FeatureLayerSettings
{
    FeatureLayerSettings ( ) = default;

    FeatureLayerSettings (
        const float in_camera_width,
        const int   in_map_x,
        const int   in_map_y,
        const int   in_minimap_x,
        const int   in_minimap_y
    )
        : camera_width ( in_camera_width ),
          map_x ( in_map_x ),
          map_y ( in_map_y ),
          minimap_x ( in_minimap_x ),
          minimap_y ( in_minimap_y ) { }

    //! The width of the camera view as it would appear in the world. The size
    //! is in game world units.
    float camera_width = 24.0F;
    //! X size of the feature layer bitmap for the world screen.
    int   map_x        = 64;
    //! Y size of the feature layer bitmap for the world screen.
    int   map_y        = 64;
    //! X size of the feature layer bitmap for the minimap.
    int   minimap_x    = 64;
    //! Y size of the feature layer bitmap for the minimap.
    int   minimap_y    = 64;
};

//! Settings for rendered feature layer output.
struct InterfaceSettings
{
    InterfaceSettings ( ) = default;


    FeatureLayerSettings feature_layer_settings;
    RenderSettings       render_settings;

    bool use_feature_layers { false };
    bool use_render { false };
};

//! Settings for starting a game.
struct GameSettings
{
    GameSettings ( ) = default;

    string              map_name;
    vector<PlayerSetup> player_setup;
    Ports               ports;

    /*! @retval true Will not generate a deselect command after sending a
     * command to a unit.
     * @note performance increase
     * @see SetRawAffectsSelection */
    bool raw_affects_selection { false };
};

//! Settings for starting a replay.
struct ReplaySettings
{
    ReplaySettings ( ) = default;

    string         replay_dir;
    //! Fill with replays to analyze.
    vector<string> replay_file;
    uint32_t       player_id { 1 };
};

//! Game status.
enum class AppState {
    //! The game application has behaved normally.
    Normal,
    //! A timeout has occurred, and the game application was terminated.
    Timeout,
    /*! A timeout has occurred, but the game application could not be
       terminated.*/
    Timeout_Zombie,
    //! A crash has been detected.
    Crashed,
};

inline AppState app_state = AppState::Normal;

} // namespace sc2
