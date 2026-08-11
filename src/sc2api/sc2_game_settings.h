#pragma once

#include <cstdint>
#include <string>
#include <utility>
#include <vector>

#include "sc2_gametypes.h"

namespace sc2 {

using std::string,
    std::uint8_t,
    std::uint32_t,
    std::uint64_t,
    std::vector;

//! Information about a running process.
struct ProcessInfo {
    ProcessInfo() = default;
    ProcessInfo(string path,
                const uint64_t id,
                const int port)
            : process_path(std::move(path)),
            process_id(id),
            port(port) {}

    string process_path;
    uint64_t process_id{0};
    int port{0};
};

//! Settings to run the game process.
struct ProcessSettings {
    ProcessSettings() = default;
    ProcessSettings(bool in_realtime,
                    int in_step_size,
                    const string& in_process_path,
                    const string& in_net_address,
                    int in_timeout_ms,
                    int in_port_start,
                    bool in_multi_threaded = false,
                    bool in_full_screen = false);

    bool realtime{false};
    int step_size{0};
    string process_path;
    string data_version;
    string net_address;
    int timeout_ms{0};
    int port_start{0};
    // Run all OnSteps in parallel.
    bool multi_threaded{false};
    bool full_screen{false};
    vector<string> extra_command_lines;
    // PID and port of all running sc2 processes.
    vector<ProcessInfo> process_info;
};

//! Settings for an RGB rendered output.
struct RenderSettings {
    RenderSettings() = default;
    RenderSettings(const int map_x,
                const int map_y,
                const int minimap_x,
                const int minimap_y)
          : map_x(map_x),
            map_y(map_y),
            minimap_x(minimap_x),
            minimap_y(minimap_y) {}

    //! X size of rendered bitmap for the world screen.
    int map_x{800};
    //! Y size of rendered bitmap for the world screen.
    int map_y{600};
    //! X size of rendered bitmap for the minimap.
    int minimap_x{300};
    //! Y size of rendered bitmap for the minimap.
    int minimap_y{300};
};

//! Settings for feature layer output.
struct FeatureLayerSettings {
    FeatureLayerSettings() = default;
    FeatureLayerSettings(const float in_camera_width,
                        const int in_map_x,
                        const int in_map_y,
                        const int in_minimap_x,
                        const int in_minimap_y)
        : camera_width(in_camera_width),
          map_x(in_map_x),
          map_y(in_map_y),
          minimap_x(in_minimap_x),
          minimap_y(in_minimap_y) {}

    //! The width of the camera view as it would appear in the world. The size is in game world units.
    float camera_width = 24.0F;
    //! X size of the feature layer bitmap for the world screen.
    int map_x = 64;
    //! Y size of the feature layer bitmap for the world screen.
    int map_y = 64;
    //! X size of the feature layer bitmap for the minimap.
    int minimap_x = 64;
    //! Y size of the feature layer bitmap for the minimap.
    int minimap_y = 64;
};

//! Settings for rendered feature layer output.
struct InterfaceSettings {
    InterfaceSettings();

    bool use_feature_layers{false};
    bool use_render{false};
    FeatureLayerSettings feature_layer_settings;
    RenderSettings render_settings;
};

//! Settings for starting a game.
struct GameSettings {
    GameSettings() = default;

    string map_name;
    vector<PlayerSetup> player_setup;
    Ports ports;
    bool raw_affects_selection = false;
};

//! Settings for starting a replay.
struct ReplaySettings {
    ReplaySettings();

    // Fill with replays to analyze.
    vector<string> replay_file;
    string replay_dir;
    uint32_t player_id{1};
};

//! Game status.
enum class AppState : uint8_t{
    normal,          // The game application has behaved normally.
    timeout,         // A timeout has occurred, and the game application was terminated.
    timeout_zombie,  // A timeout has occurred, but the game application could not be terminated.
    crashed,         // A crash has been detected.
};

//! Known maps.
//! These are the maps that come with the repo.
//! See documentation for how to download and install additional map packs.
inline constexpr auto kMapBelShirVestigeLE = "Ladder/(2)Bel'ShirVestigeLE (Void).SC2Map";
inline constexpr auto kMapEmpty = "Test/Empty.SC2Map";
inline constexpr auto kMapEmptyLong = "Test/EmptyLong.SC2Map";
inline constexpr auto kMapEmptyTall = "Test/EmptyTall.SC2Map";
inline constexpr auto kMapMarineMicro = "Example/MarineMicro.SC2Map";

}  // namespace sc2
