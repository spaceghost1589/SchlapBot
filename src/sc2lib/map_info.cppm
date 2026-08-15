/*! \file map_info.cppm
    \brief Information about a game map.
*/
module;
#include <cassert>
#include <cstdint>
#include <cstdlib>
#include <fstream>
#include <string>
#include <utility>
#include <vector>

#include "../sc2api/sc2_common.h"
#include "sc2_gametypes.h"
export module map_info;

using std::div_t, std::ofstream, std::string, std::uint32_t, std::vector;

export namespace sc2 {

struct PlayerInfo {
    uint32_t player_id;
    PlayerType player_type;
    Race race_requested;
    Race race_actual;
    Difficulty difficulty;
    AIBuild ai_build;
    string player_name;

    PlayerInfo() = default;

    PlayerInfo(uint32_t player_id, PlayerType player_type, Race race_requested, Race race_actual, Difficulty difficulty,
               AIBuild ai_build, string player_name)
        : player_id(player_id),
          player_type(player_type),
          race_requested(race_requested),
          race_actual(race_actual),
          difficulty(difficulty),
          ai_build(ai_build),
          player_name(std::move(player_name)) {
    }

    ~PlayerInfo() = default;
};

//! Data for a feature layer or rendered image.
struct ImageData {
    int width{0};
    int height{0};
    int32_t bits_per_pixel{};
    string data;

    ImageData() = default;

    ~ImageData() = default;
};

//! Setup structure for feature layers or rendered images.
struct SpatialSetup {
    float camera_width;        // For feature layers only, determines the world space size of the camera.
    int map_resolution_x;      // Number of pixels in X of the main game view.
    int map_resolution_y;      // Number of pixels in Y of the main game view.
    int minimap_resolution_x;  //! Number of pixels in X of the minimap.
    int minimap_resolution_y;  //! Number of pixels in Y of the minimap.

    SpatialSetup() = default;

    ~SpatialSetup() = default;
};

//! Determines what type of data will be returned in observations.
struct InterfaceOptions {
    bool raw;                    // Raw data; essentially a list of units.
    SpatialSetup feature_layer;  //! Feature layer data.
    SpatialSetup render;         //! Rendered image data.

    InterfaceOptions() = default;
    ~InterfaceOptions() = default;
};

struct GameInfo {
    string map_name;           //! Plain text name of a map; not the filename.
    string local_map_path;     //! Filename of map. Includes the ".SC2Map" file extension.
    int width{0};              //! World width of a map.
    int height{0};             //! World height of a map.
    ImageData pathing_grid;    //! Grid showing which cells are pathable by units.
    ImageData terrain_height;  //! Height map of terrain.
    ImageData placement_grid;  //! Grid showing which cells can accept placement of structures.
    Point2D playable_min;      //! The minimum coords of playable space. Points less than this are not playable.
    Point2D playable_max;      //! The maximum coords of playable space. Points greater than this are not playable.

    vector<Point2D> enemy_start_locations;  //! Positions of possible enemy starting locations.
    vector<Point2D> start_locations;

    //! Types of data that will be in observations.
    //!< \sa InterfaceOptions
    InterfaceOptions options;

    vector<PlayerInfo> player_info;

    GameInfo() = default;
    ~GameInfo() = default;
};

//! Rendered data for a game frame.
struct RenderedFrame {
    ImageData map;
    ImageData minimap;

    RenderedFrame() = default;

    ~RenderedFrame() = default;
};

struct SampleImage {
    SampleImage() = default;

    explicit SampleImage(const ImageData& data)
        : data_(data.data), area_({0, 0}, {data.width, data.height}), bits_per_pixel_(data.bits_per_pixel) {
    }

    explicit SampleImage(string i_data, const Rect2DI& i_area, const int32_t BBP)
        : data_{std::move(i_data)}, area_{i_area}, bits_per_pixel_{BBP} {
    }

    ~SampleImage() = default;

    bool GetBit(const Point2DI& point, bool* dst) const {
        assert(bits_per_pixel_ == 1);

        if (!area_.Contain(point)) {
            return false;
        }

        auto [quot, rem] = div(point.x + (point.y * area_.Width()), 8);
        // NOLINTNEXTLINE(hicpp-signed-bitwise)
        *dst = static_cast<unsigned char>(data_.at(quot)) >> (7 - rem) & 1U;
        return true;
    }

    bool GetBit(const Point2DI& point, unsigned char* dst) const {
        assert(bits_per_pixel_ > 1);

        if (!area_.Contain(point)) {
            return false;
        }

        // Image data is stored with an upper left origin.
        assert(data_.size() == area_.Width() * area_.Height());
        *dst = data_.at(point.x + (point.y * area_.Width()));
        return true;
    }

    [[nodiscard]] int BPP() const {
        return bits_per_pixel_;
    }

    [[nodiscard]] Rect2DI Area() const {
        return area_;
    }

private:
    string data_;
    Rect2DI area_;

    // NOTE (alkurbatov): Possible bits per pixel values specified in
    // protocol/s2clientprotocol/raw.proto
    int32_t bits_per_pixel_{};

};  // SampleImage

struct PathingGrid {
    PathingGrid() = default;

    explicit PathingGrid(const GameInfo& info) : pathing_grid_(info.pathing_grid) {
    }

    ~PathingGrid() = default;

    [[nodiscard]] bool IsPathable(const Point2DI& point) const {
        if (pathing_grid_.BPP() == 1) {
            bool value{};
            if (!pathing_grid_.GetBit(point, &value)) {
                return false;
            }

            return value;
        }

        unsigned char value{};
        if (!pathing_grid_.GetBit(point, &value)) {
            return false;
        }

        return value != 255;
    }

    void Dump(const string& file_path) const {
        ofstream dst(file_path);

        for (int y = pathing_grid_.Area().Height() - 1; y >= 0; --y) {
            for (int x = 0; x < pathing_grid_.Area().Width(); ++x) {
                dst << (IsPathable({x, y}) ? ' ' : '#');
            }

            dst << '\n';
        }
    }

private:
    SampleImage pathing_grid_;

};  // PathingGrid

struct PlacementGrid {
    PlacementGrid() = default;

    explicit PlacementGrid(const GameInfo& info) : placement_grid_(info.placement_grid) {
    }

    ~PlacementGrid() = default;

    [[nodiscard]] bool IsPlacable(const Point2DI& point) const {
        if (placement_grid_.BPP() == 1) {
            bool value{};
            if (!placement_grid_.GetBit(point, &value)) {
                return false;
            }

            return value;
        }

        unsigned char value{};
        if (!placement_grid_.GetBit(point, &value)) {
            return false;
        }

        return value == 255;
    }

    void Dump(const string& file_path) const {
        ofstream dst(file_path);

        for (int y = placement_grid_.Area().Height() - 1; y >= 0; --y) {
            for (int x = 0; x < placement_grid_.Area().Width(); ++x) {
                dst << (IsPlacable({x, y}) ? ' ' : '#');
            }

            dst << '\n';
        }
    }

private:
    SampleImage placement_grid_;

};  // PlacementGrid

struct HeightMap {
    HeightMap() = default;

    explicit HeightMap(const GameInfo& info) : height_map_(info.terrain_height) {
    }

    ~HeightMap() = default;

    [[nodiscard]] float TerrainHeight(const Point2DI& point) const {
        unsigned char value{};
        if (!height_map_.GetBit(point, &value)) {
            return 0.0F;
        }

        return (static_cast<float>(value) - 127) / 8.F;
    }

    void Dump(const string& file_path) const {
        std::ofstream dst(file_path);

        for (int x = 0; x < height_map_.Area().Width(); ++x) {
            for (int y = 0; y < height_map_.Area().Height(); ++y) {
                dst << TerrainHeight({x, y}) << "|";
            }
            dst << '\n';
        }
    }

private:
    SampleImage height_map_;

};  // HeightMap

}  // namespace sc2
