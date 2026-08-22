module;
#include <cassert>
#include <cstdint>
#include <fstream>
#include <string>
#include <type_traits>
#include <utility>
#include <vector>

#include "lib/gametypes.h"
#include "s2clientprotocol/common.pb.h"
export module map_info;
import errors;
import points;

using std::is_same_v, std::move, std::ofstream, std::string, std::vector;

export namespace sc2 {

struct PlayerInfo
{
    uint32_t   player_id { };
    PlayerType player_type { };
    Race       race_requested { };
    Race       race_actual { };
    Difficulty difficulty { };
    AIBuild    ai_build { };
    string     player_name;

    PlayerInfo ( ) {}

    PlayerInfo (
            uint32_t   player_id,
            PlayerType player_type,
            Race       race_requested,
            Race       race_actual,
            Difficulty difficulty,
            AIBuild    ai_build,
            string     player_name
    ):
            player_id (player_id),
            player_type (player_type),
            race_requested (race_requested),
            race_actual (race_actual),
            difficulty (difficulty),
            ai_build (ai_build),
            player_name (move (player_name))
    {}

    ~PlayerInfo ( ) = default;
};

struct ImageDataLocal
{
    ImageDataLocal ( ) {}

    explicit ImageDataLocal (const SC2APIProtocol::ImageData& image):
            bits_per_pixel_ {image.bits_per_pixel( )},
            map_ {Point2DI (image.size( ))},
            data_ {image.data( )}
    {}

    explicit ImageDataLocal (
            string i_data, const Point2D& i_area, const int32_t BBP
    ):
            bits_per_pixel_ {BBP}, map_ {i_area}, data_ {move (i_data)}
    {}

    explicit ImageDataLocal (
            string i_data, const Rect2DI& i_area, const int32_t BBP
    ):
            bits_per_pixel_ {BBP}, map_ {i_area}, data_ {move (i_data)}
    {}

    ~ImageDataLocal ( ) = default;

    // Update data string every frame
    bool UpdateImageDataLocal (
            const SC2APIProtocol::ImageData& image, bool need_return = false
    )
    {
        if ( need_return ) {
            const int expectedSizeBits =
                    bits_per_pixel_ * map_.Height( ) * map_.Width( );
            need_return =
                    (image.data( ).size( ) * 8 == expectedSizeBits &&
                     expectedSizeBits > 0);
        }
        // TODO Verify if data_ should be updated on check failure.
        //      proto_to_pods.cc::430
        data_ = image.data( );
        return need_return;
    }


    // bool GetBit (const Point2DI& point, bool* dst) const
    // {
    //     assert (bits_per_pixel_ == 1);
    //
    //     if ( !map_.Contain (point) ) {
    //         return false;
    //     }
    //
    //
    //     // NOLINTNEXTLINE(hicpp-signed-bitwise)
    //     *dst = static_cast<unsigned char> (data_.at (quot)) >> (7 - rem) & 1u;
    //     return true;
    // }

    // bool GetBit (const Point2DI& point, unsigned char* dst) const
    // {
    //     assert (bits_per_pixel_ > 1);
    //
    //     if ( !map_.Contain (point) ) {
    //         return false;
    //     }
    //
    //     // Image data is stored with an upper left origin.
    //     assert (data_.size( ) == area_.Area( ));
    //     *dst = data_.at (point.x + (point.y * map_.Width( )));
    //     return true;
    // }

    // data size = width * height * bits_per_pixel / 8
    template<typename T>
    requires is_same_v<T, bool> || is_same_v<T, unsigned char*>
    bool GetBit (const Point2DI& point, T dst) const
    { // Image data is stored with an upper left origin.
    // TODO: is upper-left correct? common.proto says bottom left.
        if ( !map_.Contain (point) ) {
            return false;
        }

        if ( is_same_v<T, bool> )
        {
            Assert (bits_per_pixel_ == 1, "");
            auto [quot, rem] = div (point.x + (point.y * map_.Width( )), 8);
            *dst = static_cast<unsigned char> (data_.at (quot)) >> (7 - rem) & 1U;
            return true;
        }
        else if ( is_same_v<T, unsigned char*> )
        {
            assert (bits_per_pixel_ == 8);
            assert (data_.size( ) == area_.Area( ));
            *dst = data_.at (point.x + (point.y * map_.Width( )));
            return true;
        }
        // else error logging
            return false;
    }

    [[nodiscard]]
    int BPP ( ) const
    {
        return bits_per_pixel_;
    }

    [[nodiscard]]
    unsigned int Area ( ) const
    {
        return map_.Area( );
    }

protected:
    // NOTE (alkurbatov): Possible bits per pixel values specified in
    // protocol/s2clientprotocol/raw.proto
    int32_t bits_per_pixel_ { };
    Rect2DI map_ { };
    string  data_ { };
}; // ImageDataLocal

// 1 bit creep layer. (per raw.proto)
struct CreepMap : ImageDataLocal
{
    // using ImageDataLocal::ImageDataLocal;

    [[nodiscard]]
    //! Checks whether a point on the map has creep or not.
    bool HasCreep (const Point2DI& point) const
    {
        if ( bits_per_pixel_ == 1 ) {
            bool value { };
            if ( !GetBit (point, &value) ) {
                return false;
            }
            return value;
        }

        unsigned char value { };
        if ( !GetBit (point, &value) ) {
            return false;
        }
        return value > 0;
    }
};

//! @brief Map Visibility Enum:\n
//! 1 - Hidden\n 2 - Fogged\n 3 - Visible\n 4 - FullHidden
enum class Visibility {
    Hidden     = 0, /// Unexplored Shroud
    Fogged     = 1, /// Explored, No Active Vision
    Visible    = 2, /// Active Sight Line
    FullHidden = 3  /// Out of Bounds / Permanent Shroud
};

// 1 byte visibility layer. (per raw.proto)
class VisibilityMap : public ImageDataLocal
{
    using ImageDataLocal::ImageDataLocal;

    [[nodiscard]]
    Visibility GetVisibility (const Point2DI& point) const
    {
        unsigned char value { };
        if ( !GetBit (point, &value) ) {
            return Visibility::FullHidden;
        }
        else if ( value == 0 ) {
            return Visibility::Hidden;
        }
        else if ( value == 1 ) {
            return Visibility::Fogged;
        }
        else if ( value == 2 ) {
            return Visibility::Visible;
        }
        else {
            return Visibility::FullHidden;
        }
    }
};

//! Setup structure for feature layers or rendered images.
struct SpatialSetup
{
    float camera_width;
    // For feature layers only, determines the world space size of the camera.
    int   map_resolution_x;     // Number of pixels in X of the main game view.
    int   map_resolution_y;     // Number of pixels in Y of the main game view.
    int   minimap_resolution_x; //! Number of pixels in X of the minimap.
    int   minimap_resolution_y; //! Number of pixels in Y of the minimap.

    SpatialSetup ( ) = default;

    ~SpatialSetup ( ) = default;
};

//! Determines what type of data will be returned in observations.
struct InterfaceOptions
{
    bool         raw;           // Raw data; essentially a list of units.
    SpatialSetup feature_layer; //! Feature layer data.
    SpatialSetup render;        //! Rendered image data.

    InterfaceOptions ( )  = default;
    ~InterfaceOptions ( ) = default;
};

struct GameInfo
{
    string map_name;       //! Plain text name of a map; not the filename.
    string local_map_path; //! Filepath of map. Includes the ".SC2Map".

    int width {0};  //! World width of a map.
    int height {0}; //! World height of a map.
    ImageDataLocal
            pathing_grid; //! Grid showing which cells are pathable by units.
    ImageDataLocal terrain_height; //! Height map of terrain.
    ImageDataLocal placement_grid;
    //! Grid showing which cells can accept placement of structures.
    Point2D        playable_min;
    //! The minimum coords of playable space. Points less than this are not
    //! playable.
    Point2D        playable_max;
    //! The maximum coords of playable space. Points greater than this are not
    //! playable.

    vector<Point2D> enemy_start_locations;
    //! Positions of possible enemy starting locations.
    vector<Point2D> start_locations;

    //! Types of data that will be in observations.
    //!< \sa InterfaceOptions
    InterfaceOptions options;

    vector<PlayerInfo> player_info;

    GameInfo ( )  = default;
    ~GameInfo ( ) = default;
};

//! Rendered data for a game frame.
struct RenderedFrame
{
    ImageDataLocal map;
    ImageDataLocal minimap;

    RenderedFrame ( ) = default;

    ~RenderedFrame ( ) = default;
};

struct PathingGrid
{
    PathingGrid ( ) = default;

    explicit PathingGrid (const GameInfo& info):
            pathing_grid_ (info.pathing_grid)
    {}

    ~PathingGrid ( ) = default;

    [[nodiscard]]
    bool IsPathable (const Point2DI& point) const
    {
        if ( pathing_grid_.BPP( ) == 1 ) {
            bool value { };
            if ( !pathing_grid_.GetBit (point, &value) ) {
                return false;
            }

            return value;
        }

        unsigned char value { };
        if ( !pathing_grid_.GetBit (point, &value) ) {
            return false;
        }

        return value != 255;
    }

    void Dump (const string& file_path) const
    {
        ofstream dst (file_path);

        for ( int y = pathing_grid_.Area( ).Height( ) - 1; y >= 0; --y ) {
            for ( int x = 0; x < pathing_grid_.Area( ).Width( ); ++x ) {
                dst << (IsPathable ({x, y}) ? ' ' : '#');
            }

            dst << '\n';
        }
    }

private:
    ImageDataLocal pathing_grid_;
}; // PathingGrid

struct PlacementGrid
{
    PlacementGrid ( ) = default;

    explicit PlacementGrid (const GameInfo& info):
            placement_grid_ (info.placement_grid)
    {}

    ~PlacementGrid ( ) = default;

    [[nodiscard]]
    bool IsPlacable (const Point2DI& point) const
    {
        if ( placement_grid_.BPP( ) == 1 ) {
            bool value { };
            if ( !placement_grid_.GetBit (point, &value) ) {
                return false;
            }

            return value;
        }

        unsigned char value { };
        if ( !placement_grid_.GetBit (point, &value) ) {
            return false;
        }

        return value == 255;
    }

    void Dump (const string& file_path) const
    {
        ofstream dst (file_path);

        for ( int y = placement_grid_.Area( ).Height( ) - 1; y >= 0; --y ) {
            for ( int x = 0; x < placement_grid_.Area( ).Width( ); ++x ) {
                dst << (IsPlacable ({x, y}) ? ' ' : '#');
            }

            dst << '\n';
        }
    }

private:
    ImageDataLocal placement_grid_;
}; // PlacementGrid

struct HeightMap
{
    HeightMap ( ) = default;

    explicit HeightMap (const GameInfo& info):
            height_map_ (info.terrain_height)
    {}

    ~HeightMap ( ) = default;

    [[nodiscard]]
    float TerrainHeight (const Point2DI& point) const
    {
        unsigned char value { };
        if ( !height_map_.GetBit (point, &value) ) {
            return 0.0f;
        }

        return (static_cast<float> (value) - 127) / 8.f;
    }

    void Dump (const string& file_path) const
    {
        ofstream dst (file_path);

        for ( int x = 0; x < height_map_.Area( ).Width( ); ++x ) {
            for ( int y = 0; y < height_map_.Area( ).Height( ); ++y ) {
                dst << TerrainHeight ({x, y}) << "|";
            }
            dst << '\n';
        }
    }

private:
    ImageDataLocal height_map_;
}; // HeightMap

} // namespace sc2
