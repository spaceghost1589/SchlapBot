module;
#include <cassert>
#include <cstdint>
#include <cstdlib> // IWYU pragma: keep
#include <fstream>
#include <string>
#include <type_traits>
#include <utility>
#include <vector>

#include <s2clientprotocol/common.pb.h>
export module map_info;
import error_handler;
import point;
import game_types;

namespace {
using std::move;
using std::string;
using std::uint32_t;
} // namespace

/* TODO create a struct for each type of map_data:
 *  Creep, Visibility, Pathing, Placement, Height */

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

    PlayerInfo ( ) = default;

    PlayerInfo (
        const uint32_t   playerID,
        const PlayerType playerType,
        const Race       raceRequested,
        const Race       raceActual,
        const Difficulty diff,
        const AIBuild    aiBuild,
        const string    &playerName
    ) {
        player_id      = playerID;
        player_type    = playerType;
        race_requested = raceRequested;
        race_actual    = raceActual;
        difficulty     = diff;
        ai_build       = aiBuild;
        player_name    = playerName;
    }
};

struct ImageData
{
    //! Number of bits per pixel; 8 bits for a byte etc.
    int32_t bits_per_pixel { 0 };

    // int width { 0 };
    // int height { 0 };
    //! Map Dimension in pixels.
    Rect2DI map_area_ { }; // formerly `area_`

    /*! Binary data; the size of this buffer in bytes is width * height *
     * bits_per_pixel / 8.*/
    string data_ { };

    explicit ImageData ( const SC2APIProtocol::ImageData &image )
        : bits_per_pixel { image.bits_per_pixel( ) },
          map_area_ { Point2DI ( image.size( ).x( ), image.size( ).y( ) ) },
          data_ { image.data( ) } { }

    explicit ImageData (
        const int32_t   BBP,
        const Point2DI &i_area,
        const string   &i_data
    )
        : bits_per_pixel { BBP },
          map_area_ ( i_area ),
          data_ { move ( i_data ) } { }

    // Update data string every frame
    bool UpdateImageDataLocal (
        const SC2APIProtocol::ImageData &image,
        bool                             need_return = false
    ) {
        if ( need_return ) {
            const int expectedSizeBits { bits_per_pixel * map_area_.Area( ) };
            need_return = static_cast<int> ( image.data( ).size( ) ) * 8 ==
                              expectedSizeBits &&
                          expectedSizeBits > 0;
        }

        // TODO Verify if data_ should be updated on check failure.
        //      proto_to_pods.cc::430
        data_ = image.data( );
        return need_return;
    }

    /*! @brief Checks a point on the map
     * @param point Point on the make to be checked.
     * @param distance */
    bool GetBit ( const Point2DI &point, bool *distance ) const {
        Assert ( bits_per_pixel == 1 );

        if ( !map_area_.Contain ( point ) )
            return false;

        const auto [byte, bit] =
            div ( map_area_.Width( ) * point.y + point.x, 8 );
        *distance = ( data_[byte] >> ( 7 - bit ) ) & 1;
        return true;
    }

    bool GetBit ( const Point2DI &point, unsigned char *distance ) const {
        Assert ( bits_per_pixel > 1 );

        if ( !map_area_.Contain ( point ) ) {
            return false;
        }

        // Image data is stored with an upper left origin.
        assert ( data_.size( ) == map_area_.Area( ) );
        *distance = data_.at ( map_area_.Width( ) * point.y + point.x );
        return true;
    }

    // data size = width * height * bits_per_pixel / 8
    template<typename T>
        requires is_same_v<T, bool> || is_same_v<T, unsigned char *>
    bool GetBit (
        const Point2DI &point,
        T               dst
    ) const { // Image data is stored with an upper left origin.
              // TODO: is upper-left correct? common.proto says bottom left.
        if ( !map_area_.Contain ( point ) ) {
            return false;
        }

        if ( is_same_v<T, bool> ) {
            Assert ( bits_per_pixel == 1, "" );
            auto [quot, rem] =
                div ( map_area_.Width( ) * point.y + point.x, 8 );
            *dst = static_cast<unsigned char> ( data_.at ( quot ) ) >>
                       ( 7 - rem ) &
                   1U;
            return true;
        }
        if ( is_same_v<T, unsigned char *> ) {
            assert ( bits_per_pixel == 8 );
            assert ( data_.size( ) == map_area_.Area( ) );
            *dst = data_.at ( map_area_.Width( ) * point.y + point.x );
            return true;
        } // TODO: else error logging
        return false;
    }

    [[nodiscard]]
    int BPP ( ) const {
        return bits_per_pixel;
    }

    [[nodiscard]]
    unsigned int Area ( ) const {
        return map_area_.Area( );
    }
}; // ImageData

// 1 bit creep layer. (per raw.proto)
struct CreepMap : ImageData
{
    [[nodiscard]]
    //! Checks whether a point on the map has creep or not.
    bool HasCreep ( const Point2DI &point ) const {
        if ( bits_per_pixel == 1 ) {
            bool value { };
            if ( !GetBit ( point, &value ) ) {
                return false;
            }
            return value;
        }

        unsigned char value { };
        if ( !GetBit ( point, &value ) ) {
            return false;
        }
        return value > 0;
    }
};

//! @brief Map Visibility Enum:\n
//! 0 - Hidden\n 1 - Fogged\n 2 - Visible\n 3 - FullHidden
enum class Visibility : uint8_t {
    Hidden     = 0, /// Unexplored Shroud
    Fogged     = 1, /// Explored, No Active Vision
    Visible    = 2, /// Active Sight Line
    FullHidden = 3, /// Out of Bounds / Permanent Shroud
};

using enum Visibility;

// 1 byte visibility layer. (per raw.proto)
class VisibilityMap : public ImageData {
    [[nodiscard]]
    Visibility GetVisibility ( const Point2DI &point ) const {
        unsigned char value { };
        if ( !GetBit ( point, &value ) ) {
            return FullHidden;
        }
        if ( value == 0 ) {
            return Hidden;
        }
        if ( value == 1 ) {
            return Fogged;
        }
        if ( value == 2 ) {
            return Visible;
        }
        return FullHidden;
    }
};

//! Setup structure for feature layers or rendered images.
struct SpatialSetup
{
    //! For feature layers only, determines the world space size of the camera.
    float    camera_width { 0.0F };
    //! Number of pixels in X of the main game view.
    uint16_t map_resolution_x { 0 };
    //! Number of pixels in Y of the main game view.
    uint16_t map_resolution_y { 0 };
    //! Number of pixels in X of the minimap.
    uint16_t minimap_resolution_x { 0 };
    //! Number of pixels in Y of the minimap.
    uint16_t minimap_resolution_y { 0 };

    SpatialSetup ( ) = default;
};

//! Determines what type of data will be returned in observations.
struct InterfaceOptions
{
    bool         raw { false };     // Raw data; essentially a list of units.
    SpatialSetup feature_layer { }; //! Feature layer data.
    SpatialSetup render { };        //! Rendered image data.

    InterfaceOptions ( ) = default;
};

struct GameInfo
{
    //! Plain text name of a map; not the filename.
    string map_name { };
    //! Filepath of map. Includes the ".SC2Map".
    string local_map_path { };

    //! World width of a map.
    int       width { 0 };
    //! World height of a map.
    int       height { 0 };
    //! Grid showing which cells are pathable by units.
    ImageData pathing_grid;
    //! Height map of terrain.
    ImageData terrain_height;
    //! Grid showing which cells can accept placement of structures.
    ImageData placement_grid;

    /*! The minimum coords of playable space. Points less than this are not
     * playable. */
    Point2D playable_min { };
    /*! The maximum coords of playable space. Points greater than this are not
     * playable. */
    Point2D playable_max { };

    //! Positions of possible enemy starting locations.
    vector<Point2D> enemy_start_locations { };
    vector<Point2D> start_locations { };

    //! Types of data that will be in observations.
    InterfaceOptions options;

    vector<PlayerInfo> player_info { };
};

//! Rendered data for a game frame.
struct RenderedFrame
{
    ImageData map;
    ImageData minimap;
};

struct ImageData_StepSample
{
private:
    const string data_ { };
    Rect2DI      map_area_ { };

    // NOTE (alkurbatov): Possible bits per pixel values specified in
    // protocol/s2clientprotocol/raw.proto
    int bits_per_pixel;

public:
    // explicit ImageData_StepSample ( const SC2APIProtocol::ImageData &data )
    //   : data_ ( data.data( ) ),
    //     map_area_ ( { 0, 0 }, { data.size( ).x( ), data.size( ).y( ) } ),
    //     bits_per_pixel ( data.bits_per_pixel( ) ) { }

    explicit ImageData_StepSample ( const ImageData &data )
        : data_ ( data.data_ ),
          map_area_ (
              { 0, 0 },
              { data.map_area_.Width( ), data.map_area_.Height( ) }
          ),
          bits_per_pixel ( data.bits_per_pixel ) { }

    bool GetBit ( const Point2DI &point, bool *distance ) const {
        assert ( bits_per_pixel == 1 );

        if ( !map_area_.Contain ( point ) )
            return false;

        const auto [byte, bit] =
            div ( map_area_.Width( ) * point.y + point.x, 8 );
        *distance = ( data_.at ( byte ) >> ( 7 - bit ) ) & 1;
        return true;
    }

    bool GetBit ( const Point2DI &point, unsigned char *distance ) const {
        assert ( bits_per_pixel > 1 );

        if ( !map_area_.Contain ( point ) ) {
            return false;
        }

        // Image data is stored with an upper left origin.
        assert ( data_.size( ) == map_area_.Width( ) * map_area_.Height( ) );
        *distance = data_[point.x + point.y * map_area_.Width( )];
        return true;
    }

    [[nodiscard]] int BPP ( ) const {
        return bits_per_pixel;
    }

    [[nodiscard]] Rect2DI Area ( ) const {
        return map_area_;
    }
};

struct PathingGrid
{
    PathingGrid ( ) = delete;

    explicit PathingGrid ( const GameInfo &info )
        : pathing_grid_ ( info.pathing_grid ) { }

    [[nodiscard]]
    bool IsPathable ( const Point2DI &point ) const {
        if ( pathing_grid_.BPP( ) == 1 ) {
            bool value { }; // NOLINT(*-const-correctness)
            if ( !pathing_grid_.GetBit ( point, &value ) ) {
                return false;
            }
            return value;
        }

        unsigned char value { };
        if ( !pathing_grid_.GetBit ( point, &value ) ) {
            return false;
        }

        return value != 255;
    }

    void DumpPathing ( const string &file_path ) const {
        ofstream dst ( file_path );

        for ( int y_coord = 0; y_coord < pathing_grid_.Area( ).Height( );
              y_coord++ )
        {
            for ( int x_coord = 0; x_coord < pathing_grid_.Area( ).Width( );
                  x_coord++ )
            {
                dst << ( IsPathable ( { x_coord, y_coord } ) ? ' ' : '#' );
            }
            dst << '\n';
        }
    }

private:
    ImageData_StepSample pathing_grid_;
}; // PathingGrid

struct PlacementGrid
{
    PlacementGrid ( ) = delete;

    explicit PlacementGrid ( const GameInfo &info )
        : placement_grid_ ( info.placement_grid ) { }

    [[nodiscard]]
    bool IsPlacable ( const Point2DI &point ) const {
        if ( placement_grid_.BPP( ) == 1 ) {
            bool value { };
            if ( !placement_grid_.GetBit ( point, &value ) ) {
                return false;
            }

            return value;
        }

        unsigned char value { };
        if ( !placement_grid_.GetBit ( point, &value ) ) {
            return false;
        }

        return value == 255;
    }

    void DumpPlacement ( const string &file_path ) const {
        ofstream dst ( file_path );

        for ( int y_coord = 0; y_coord < placement_grid_.Area( ).Height( );
              y_coord++ )
        {
            for ( int x_coord = 0; x_coord < placement_grid_.Area( ).Width( );
                  x_coord++ )
            {
                dst << ( IsPlacable ( { x_coord, y_coord } ) ? ' ' : '#' );
            }

            dst << '\n';
        }
    }

private:
    ImageData_StepSample placement_grid_;
}; // PlacementGrid

struct HeightMap
{
private:
    ImageData_StepSample height_map_;

public:
    HeightMap ( ) = delete;

    explicit HeightMap ( const GameInfo &info )
        : height_map_ ( info.terrain_height ) { }

    [[nodiscard]]
    float TerrainHeight ( const Point2DI &point ) const {
        unsigned char value { };
        if ( !height_map_.GetBit ( point, &value ) ) {
            return 0.0F;
        }

        return ( static_cast<float> ( value ) - 127 ) / 8.0F;
    }

    void DumpHeight ( const string &file_path ) const {
        ofstream dst ( file_path );

        for ( int x_coord = 0; x_coord < height_map_.Area( ).Width( );
              ++x_coord )
        {
            for ( int y_coord = 0; y_coord < height_map_.Area( ).Height( );
                  ++y_coord )
            {
                dst << TerrainHeight ( { x_coord, y_coord } ) << "|";
            }
            dst << '\n';
        }
    }
}; // HeightMap

} // namespace sc2
