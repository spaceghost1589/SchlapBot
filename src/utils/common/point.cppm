module;
#include <algorithm>
#include <cmath>
#include <concepts>
#include <format>
#include <functional>
#include <iosfwd>
#include <type_traits>
#include <variant>

#include <s2clientprotocol/common.pb.h>
export module common:point;


export namespace sc2 {
using namespace std;


//! Basic premise for a Point2D: Having X and Y coordinates
template<typename PL2D>
concept HasXY = requires ( PL2D p ) {
    { p.x } -> is_arithmetic;
    { p.y } -> is_arithmetic;
};

//! A type where there are at least 2 values: pairs, tuples, arrays, etc.
template<typename PL2D>
concept Pair2D = requires ( PL2D p ) {
    { get<0> ( p ) } -> is_arithmetic;
    { get<1> ( p ) } -> is_arithmetic;
};

//! Something is PointLike2D if it satisfies either concept: HasXY or Tuple2D
template<typename PL2D>
concept PointLike2D = HasXY<PL2D> || Pair2D<PL2D>;

//! Establishes X coordinate base on type concept.
template<PointLike2D PL2D> constexpr auto get_x ( const PL2D& p ) {
    if constexpr ( HasXY<PL2D> ) // Raw X coord
        return ( p.x );
    else // pairs, tuples, arrays, etc.
        return get<0> ( p );
}

//! Establishes Y coordinate base on type concept.
template<PointLike2D PL2D> constexpr float get_y ( const PL2D& p ) {
    if constexpr ( HasXY<PL2D> ) // Raw Y coord
        return p.y;
    else // pairs, tuples, arrays, etc.
        return get<1> ( p );
}

//------------------------------------------------------------------------------

//     Point2D - Point2D - Point2D - Point2D - Point2D - Point2D - Point2D

//------------------------------------------------------------------------------

/*! 2D point.
 * When referring to Point2D, (0, 0) is bottom left of map. \n
 * @see Distance2D, DistanceSquared2D, Normalize2D, Dot2D */
template<typename T>
    requires is_same_v<T, int> || is_same_v<T, float>
struct Point_2D
{
    T x { 0 };
    T y { 0 };

    // Constructors
    Point_2D ( ) = default;

    Point_2D ( T x_in, T y_in )
          : x ( x_in ),
            y ( y_in ) {}

    Point_2D ( const SC2APIProtocol::PointI& pt )
          : x ( pt.x( ) ),
            y ( pt.y( ) ) {}

    template<typename T_x, typename T_y>
        requires ( !is_same_v<T_x, T> || !is_same_v<T_y, T> )
    Point_2D ( T_x x_in, T_y y_in )
          : x ( convert_coord ( x_in ) ),
            y ( convert_coord ( y_in ) ) {}

    template<typename U>
    constexpr Point_2D ( const Point_2D<U>& pt )
          : x ( convert_coord ( pt.x ) ),
            y ( convert_coord ( pt.y ) ) {}

    // Point2D ( const SC2APIProtocol::PointI& point_i ):
    //     x ( convert_coord ( point_i.x( ) ) ),
    //     y ( convert_coord ( point_i.y( ) ) ) {}

    // Point2D (const SC2APIProtocol::Size2DI );

    // Universal Converting Constructor
    template<PointLike2D PL2D>
    constexpr Point_2D ( const PL2D& pt )
          : x ( convert_coord ( get_x ( pt ) ) ),
            y ( convert_coord ( get_y ( pt ) ) ) {}

    // Arithmetic Operators
    Point_2D& operator += ( const Point_2D& rhs ) {
        x += rhs.x;
        y += rhs.y;
        return *this;
    }

    [[nodiscard]]
    friend constexpr Point_2D operator + (
        Point_2D lhs, const Point_2D& rhs
    ) noexcept {
        return lhs += rhs;
    }

    Point_2D& operator -= ( const Point_2D& rhs ) {
        x -= rhs.x;
        y -= rhs.y;
        return *this;
    }

    [[nodiscard]]
    friend constexpr Point_2D operator - (
        Point_2D& lhs, const Point_2D& rhs
    ) noexcept {
        return lhs -= rhs;
    }

    Point_2D& operator *= ( float rhs ) {
        x *= rhs;
        y *= rhs;
        return *this;
    }

    [[nodiscard]]
    friend constexpr Point_2D operator * ( Point_2D lhs, float rhs ) noexcept {
        lhs *= rhs;
        return lhs;
    }

    Point_2D& operator /= ( float rhs ) {
        x /= rhs;
        y /= rhs;
        return *this;
    }

    [[nodiscard]]
    friend constexpr Point_2D operator / (
        Point_2D lhs, const float rhs
    ) noexcept {
        return ( lhs /= rhs );
    }

    [[nodiscard]]
    friend constexpr Point_2D operator / (
        const float lhs, Point_2D rhs
    ) noexcept {
        return Point_2D { lhs / rhs.x, lhs / rhs.y };
    }

    // Boolean Operators

    bool operator == ( const Point_2D& rhs ) const {
        return x == rhs.x && y == rhs.y;
    }

    bool operator != ( const Point_2D& rhs ) const {
        return !( *this == rhs );
    }

    float DistanceTo ( const Point_2D& target ) const {
        return hypotf ( x - target.x, y - target.y );
    }

    [[nodiscard]]
    friend constexpr float Distance (
        const Point_2D& lhs, const Point_2D& rhs
    ) {
        return hypotf ( lhs.x - rhs.x, lhs.y - rhs.y );
    }

    [[nodiscard]]
    string to_string ( int flt_round = 2 ) const {
        if constexpr ( is_integral_v<T> ) {
            return format ( "({}, {})", x, y );
        } else {
            return format ( "({0:.{2}f}, {1:.{2}f})", x, y, flt_round );
        }
    }

    // Overload operator
    friend ostream& operator << ( std::ostream& stream, const Point_2D& pt ) {
        return stream << pt.to_string( );
    }

    static auto Dot2D ( const Point_2D& a, const Point_2D& b ) {
        return ( a.x * b.x ) + ( a.y * b.y );
    }

    auto DistanceSquared ( const Point_2D& a, const auto& b ) {
        return Dot2D ( a - b, a - b );
    }

    auto Distance2D ( const Point_2D& a, const Point_2D& b ) {
        return sqrt ( DistanceSquared ( a, b ) );
    }

    void Normalize ( Point_2D& a ) {
        a /= sqrt ( Dot2D ( a, a ) );
    }

private:
    //! @brief Type conversion and conditional int grid-rounding
    //! @param value one coordinate component (i.e. x or y).
    template<typename U> static T convert_coord ( U value ) {
        // Exact match, no cast needed
        if constexpr ( is_same_v<T, U> ) {
            return value;
        } // Float world-space to Int grid-space
        else if constexpr ( is_same_v<T, int> )
        {
            return static_cast<int> ( roundf ( value ) );
        } else { // Standard safe cast
            return static_cast<T> ( value );
        }
    }

}; // Point2D

//------------------------------------------------------------------------------

//    Rect2D - Rect2D - Rect2D - Rect2D - Rect2D - Rect2D - Rect2D - Rect2D

//------------------------------------------------------------------------------

//! @brief 2D rectangle based on two points.\n\n The points are
//! automatically converted into into min/max relative to the map origin.
//! @param {Point2D<T>} pt_min Bottom-Left corner of the rectangle.
//! @param pt_max Top-Right corner of the rectangle.
// TODO Check against map size
template<typename T>
    requires is_same_v<T, int> || is_same_v<T, float>
struct Rect_2D
{
    Point_2D<T> pt_min; // Bottom-Left corner
    Point_2D<T> pt_max; // Top-Right

    // Constructors
    Rect_2D ( ) = default;

    //! Builds a Rect2D using a single point and (0, 0).
    Rect_2D ( const Point_2D<T>& pt )
          : pt_min { 0, 0 },
            pt_max { pt } {}

    Rect_2D ( const SC2APIProtocol::PointI& pt )
          : pt_min { 0, 0 },
            pt_max { pt } {}

    //! Converts the input Point2D into min/max relative to (0, 0).
    Rect_2D ( const Point_2D<T>& pt_1, const Point_2D<T>& pt_2 )
          : pt_min { ranges::min ( pt_1.x, pt_2.x ), min ( pt_1.y, pt_2.y ) },
            pt_max { max ( pt_1.x, pt_2.x ), max ( pt_1.y, pt_2.y ) } {}

    Rect_2D ( const SC2APIProtocol::RectangleI& rectangle_i )
          : Rect_2D (
                Point_2D<T> ( rectangle_i.p0( ) ),
                Point_2D<T> ( rectangle_i.p1( ) )
            ) {}

    [[nodiscard]]
    T Width ( ) const {
        return pt_max.x - pt_min.x;
    }

    [[nodiscard]]
    T Height ( ) const {
        return pt_max.y - pt_min.y;
    }

    [[nodiscard]]
    T Area ( ) const {
        return Width( ) * Height( );
    }

    //! @brief Checks to see if a Point2D is contained within the Rectangle.
    [[nodiscard]]
    bool Contain ( const Point_2D<T>& point ) const {
        return (
            point.x >= pt_min.x &&
            point.y >= pt_min.y &&
            point.x <= pt_max.x &&
            point.y <= pt_max.y
        );
    }
};

//------------------------------------------------------------------------------

// Point3D - Point3D - Point3D - Point3D - Point3D - Point3D - Point3D - Point3D

//------------------------------------------------------------------------------

/*! 3D point.
 * @see Distance3D, DistanceSquared3D, Normalize3D, Dot3D */
template<typename T>
    requires is_same_v<T, unsigned int> || is_same_v<T, float>
struct Point_3D : Point_2D<T>
{
    T z { 0 };

    constexpr Point_3D ( ) = default;

    constexpr Point_3D ( T in_x, T in_y, T in_z )
          : Point_2D<T> ( in_x, in_y ),
            z ( in_z ) {}

    constexpr Point_3D ( const Point_2D<T>& p2d, const float in_z = 0.0F )
          : Point_2D<T> ( p2d ),
            z ( in_z ) {}

    // TODO: Implement map height check auto-z

    // Arithmetic Operators
    Point_3D& operator += ( const Point_3D& rhs ) {
        this->x += rhs.x;
        this->y += rhs.y;
        z       += rhs.z;
        return *this;
    }

    [[nodiscard]]
    friend constexpr Point_3D operator + (
        Point_3D& lhs, const Point_3D& rhs
    ) {
        return lhs += rhs;
    }

    Point_3D& operator -= ( const Point_3D& rhs ) {
        this->x -= rhs.x;
        this->y -= rhs.y;
        z       -= rhs.z;
        return *this;
    }

    [[nodiscard]]
    friend constexpr Point_3D operator - (
        Point_3D& lhs, const Point_3D& rhs
    ) {
        return lhs -= rhs;
    }

    Point_3D& operator *= ( float rhs ) {
        this->x *= rhs;
        this->y *= rhs;
        z       *= rhs;
        return *this;
    }

    [[nodiscard]]
    friend constexpr Point_3D operator * ( Point_3D& lhs, const float rhs ) {
        return lhs *= rhs;
    }

    Point_3D& operator /= ( float rhs ) {
        this->x /= rhs;
        this->y /= rhs;
        z       /= rhs;
        return *this;
    }

    [[nodiscard]]
    friend constexpr Point_3D operator / ( const Point_3D& lhs, float rhs ) {
        return lhs /= rhs;
    }

    [[nodiscard]]
    friend constexpr Point_3D operator / ( float lhs, const Point_3D& rhs ) {
        return { lhs / rhs.x, lhs / rhs.y, lhs / rhs.z };
    }

    // Boolean Operators

    [[nodiscard]]
    bool operator == ( const Point_3D& rhs ) const {
        return this->x == rhs.x && this->y == rhs.y && z == rhs.z;
    }

    [[nodiscard]]
    bool operator != ( const Point_3D& rhs ) const {
        return !( *this == rhs );
    }
}; // struct Point3D


using Point2D  = Point_2D<float>;
using Point2DI = Point_2D<int>;

using Rect2D  = Rect_2D<float>;
using Rect2DI = Rect_2D<int>;

using Point3D = Point_3D<float>;


float Dot3D ( const Point3D& a, const Point3D& b ) {
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

float DistanceSquared3D ( Point3D& a, const Point3D& b ) {
    return Dot3D ( a - b, a - b );
}

float Distance3D ( Point3D& a, const Point3D& b ) {
    return sqrt ( DistanceSquared3D( a, b ) );
}

void Normalize3D ( Point3D& a ) {
    a /= sqrt ( Dot3D ( a, a ) );
}

} // namespace sc2
