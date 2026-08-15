module;
#include <string>
#include <string_view>
#include <vector>

#include "../sc2api/sc2_common.h"
export module map_data;


// #ifndef SCHLAPBOT_MAP_DATA_H
// #define SCHLAPBOT_MAP_DATA_H
//
// #endif //SCHLAPBOT_MAP_DATA_H
using std::string,
    std::string_view,
    std::vector;

export namespace sc2 {

struct MapData {
    MapData() = default;

    MapData(string map_path_new,
            Point2D starting_point_1,
            Point2D starting_point_2,
            vector<Point2D> expansion_locations);

    ~MapData() = default;

    string map_path_new;
    vector<Point2D> expansion_locations;

    [[nodiscard]] const Point2D& starting_point_1() const { return expansion_locations.front(); }
    [[nodiscard]] const Point2D& starting_point_2() const { return expansion_locations.back(); }

    explicit MapData(const string& path) {
        if (path == "IncorporealAIE_v4") {
            map_path_new = "Sc2-AI-Arena-2026-Season-1/IncorporealAIE_v4.SC2Map";
            expansion_locations = {
                Point2D(123.5F, 24.5F),   // starting_point_1,
                Point2D(96.5F , 25.5F),   // Natural Expansion 1-1 (West)
                Point2D(113.5F, 48.5F),   // Natural Expansion 1-2 (North-West)
                Point2D(67.5F , 25.5F),   // Back-row 3 (South-South-West)
                Point2D(124.5F, 77.5F),   // Right-Side (West-South-West)
                Point2D(33.5F , 25.5F),   // Bottom-Left Corner (South-West)
                Point2D(97.5F , 77.5F),   // Middle-Right (Center-West)
                Point2D(58.5F , 86.5F),   // Middle-Left (Center-East)
                Point2D(122.5F, 138.5F),  // Top-Right Corner (North-East)
                Point2D(31.5F , 86.5F),   // Left-Side (East-North-East)
                Point2D(88.5F , 138.5F),  // Back-row 3 (North-North-East)
                Point2D(42.5F , 115.5F),  // Natural Expansion 2-2 (North-West)
                Point2D(59.5F , 138.5F),  // Natural Expansion 2-1 (East)
                Point2D(32.5, 139.5),     // starting_point_2,
            };
        }
    }
}; // MapData

}  // namespace sc2





//! Known maps.
//! See documentation for how to download and install additional map packs.
// inline constexpr string_view IncorporealAIE_v4 = "Sc2-AI-Arena-2026-Season-1/IncorporealAIE_v4.SC2Map";
// inline constexpr string_view LeyLinesAIE_v3    = "Sc2-AI-Arena-2026-Season-1/LeyLinesAIE_v3.SC2Map";
// inline constexpr string_view MagannathaAIE_v2  = "Sc2-AI-Arena-2026-Season-1/MagannathaAIE_v2.SC2Map";
// inline constexpr string_view PersephoneAIE_v4  = "Sc2-AI-Arena-2026-Season-1/PersephoneAIE_v4.SC2Map";
// inline constexpr string_view PylonAIE_v4       = "Sc2-AI-Arena-2026-Season-1/PylonAIE_v4.SC2Map";
// inline constexpr string_view TorchesAIE_v4     = "Sc2-AI-Arena-2026-Season-1/TorchesAIE_v4.SC2Map";
// inline constexpr string_view UltraloveAIE_v2   = "Sc2-AI-Arena-2026-Season-1/UltraloveAIE_v2.SC2Map";