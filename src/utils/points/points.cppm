module;
#include <algorithm>
#include <cmath>
#include <concepts>
#include <format>
#include <functional>
#include <iosfwd>
#include <type_traits>
#include <variant>

#include "s2clientprotocol/common.pb.h"
export module points;

using std::is_arithmetic, std::is_arithmetic_v, std::is_integral_v,
        std::is_same_v, std::convertible_to, std::format, std::function,
        std::ostream, std::ranges::max, std::ranges::min, std::roundf,
        std::string, std::to_string, std::variant;

namespace {

struct Point3D;

} // namespace

export namespace sc2 {
namespace points {

//! Basic premise for a Point2D: Having X and Y coordinates
template<typename PL2D>
concept HasXY = requires (PL2D p) {
    { p.x } -> is_arithmetic;
    { p.y } -> is_arithmetic;
};

//! A type where there are at least 2 values: pairs, tuples, arrays, etc.
template<typename PL2D>
concept Pair2D = requires (PL2D p) {
    { get<0> (p) } -> is_arithmetic;
    { get<1> (p) } -> is_arithmetic;
};

//! Something is PointLike2D if it satisfies either concept: HasXY or Tuple2D
template<typename PL2D>
concept PointLike2D = HasXY<PL2D> || Pair2D<PL2D>;

//! Establishes X coordinate base on type concept.
template<PointLike2D PL2D> constexpr auto get_x (const PL2D& p) {
    if constexpr ( HasXY<PL2D> ) // Raw X coord
        return (p.x);
    else // pairs, tuples, arrays, etc.
        return get<0> (p);
}

//! Establishes Y coordinate base on type concept.
template<PointLike2D PL2D> constexpr float get_y (const PL2D& p) {
    if constexpr ( HasXY<PL2D> ) // Raw Y coord
        return p.y;
    else // pairs, tuples, arrays, etc.
        return get<1> (p);
}

//------------------------------------------------------------------------------

//     Point2D - Point2D - Point2D - Point2D - Point2D - Point2D - Point2D

//------------------------------------------------------------------------------

//! 2D point.
//! When referring to Point2D, (0, 0) is bottom left of map. \n
//! @function Distance2D(const Point2D& a, const Point2D& b) \n
//! @function DistanceSquared2D(const Point2D& a, const Point2D& b)\n
//! @function Normalize2D(Point2D& a) \n
//! @function Dot2D(const Point2D& a, const Point2D& b) \n
template<typename T>
requires is_same_v<T, unsigned int> || is_same_v<T, float>
struct Point2D {
    T x;
    T y;

    // Constructors
    Point2D ( ):
            x (0), y (0) {}

    template<typename T_x, typename T_y>
    Point2D (T_x x_in, T_y y_in):
            x (convert_coord (x_in)), y (convert_coord (y_in)) {}

    Point2D (const SC2APIProtocol::PointI& point_i):
            x (convert_coord (point_i.x( ))),
            y (convert_coord (point_i.y( ))) {}

    // Point2D (const SC2APIProtocol::Size2DI );

    // Universal Converting Constructor
    template<PointLike2D PL2D>
    constexpr Point2D (const PL2D& pt):
            x (convert_coord (get_x (pt))), y (convert_coord (get_y (pt))) {}

    // Arithmetic Operators
    Point2D& operator += (const Point2D& rhs) {
        x += rhs.x;
        y += rhs.y;
        return *this;
    }

    [[nodiscard]]
    friend constexpr Point2D operator + (
            Point2D lhs, const Point2D& rhs
    ) noexcept {
        return lhs += rhs;
    }

    Point2D& operator -= (const Point2D& rhs) {
        x -= rhs.x;
        y -= rhs.y;
        return *this;
    }

    [[nodiscard]]
    friend constexpr Point2D operator - (
            const Point2D& lhs, const Point2D& rhs
    ) noexcept {
        return lhs -= rhs;
    }

    Point2D& operator *= (float rhs) {
        x *= rhs;
        y *= rhs;
        return *this;
    }

    [[nodiscard]]
    friend constexpr Point2D operator * (Point2D lhs, float rhs) noexcept {
        lhs *= rhs;
        return lhs;
    }

    Point2D& operator /= (float rhs) {
        x /= rhs;
        y /= rhs;
        return *this;
    }

    [[nodiscard]]
    friend constexpr Point2D operator / (
            Point2D lhs, const float rhs
    ) noexcept {
        return (lhs /= rhs);
    }

    [[nodiscard]]
    friend constexpr Point2D operator / (
            const float lhs, Point2D rhs
    ) noexcept {
        return Point2D {lhs / rhs.x, lhs / rhs.y};
    }

    // Boolean Operators
    bool operator == (const Point2D& rhs) const {
        return x == rhs.x && y == rhs.y;
    }

    bool operator != (const Point2D& rhs) const {
        return !(*this == rhs);
    }

    float DistanceTo (const Point2D& target) const {
        return hypotf (x - target.x, y - target.y);
    }

    [[nodiscard]]
    friend constexpr float Distance (Point2D lhs, const Point2D rhs) noexcept {
        return hypotf (lhs.x - rhs.x, lhs.y - rhs.y);
    }

    [[nodiscard]]
    string to_string (int flt_round = 2) const {
        if constexpr ( is_integral_v<T> ) {
            return format ("({}, {})", x, y);
        } else {
            return format ("({0:.{2}f}, {1:.{2}f})", x, y, flt_round);
        }
    }

    // Overload operator
    friend std::ostream& operator << (std::ostream& stream, const Point2D& pt) {
        return stream << pt.to_string( );
    }

private:
    //! @brief Type conversion and conditional int grid-rounding
    //! @param value one coordinate component (i.e. x or y).
    template<typename U> static T convert_coord (U value) {
        // Exact match, no cast needed
        if constexpr ( is_same_v<T, U> ) {
            return value;
        } // Float world-space to Int grid-space
        else if constexpr ( is_same_v<T, int> ) {
            return static_cast<int> (roundf (value));
        } else { // Standard safe cast
            return static_cast<T> (value);
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
requires is_same_v<T, unsigned int> || is_same_v<T, float>
struct Rect2D {
    Point2D<T> pt_min; // Bottom-Left corner
    Point2D<T> pt_max; // Top-Right

    // Constructors
    Rect2D ( ) = default;

    //! Builds a Rect2D using a single point and (0, 0).
    Rect2D (const Point2D<T>& pt):
            pt_min {0, 0}, pt_max {pt} {}

    //! Converts the input Point2D into min/max relative to (0, 0).
    Rect2D (const Point2D<T>& pt_1, const Point2D<T>& pt_2):
            pt_min {min (pt_1.x, pt_2.x), min (pt_1.y, pt_2.y)},
            pt_max {max (pt_1.x, pt_2.x), max (pt_1.y, pt_2.y)} {}

    Rect2D (const SC2APIProtocol::RectangleI& rectangle_i):
            Rect2D (Point2D<T> (rectangle_i.p0( )),
                    Point2D<T> (rectangle_i.p1( ))) {}

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
    bool Contain (const Point2D<T>& point) const {
        return (point.x >= pt_min.x &&
                point.y >= pt_min.y &&
                point.x <= pt_max.x &&
                point.y <= pt_max.y);
    }
};

auto Dot2D (const Point2D<auto>& a, const Point2D<auto>& b) {
    return (a.x * b.x) + (a.y * b.y);
}

auto DistanceSquared (const Point2D<auto>& a, const auto& b) {
    return Dot2D (a - b, a - b);
}

auto Distance2D (const Point2D<auto>& a, const Point2D<auto>& b) {
    return sqrt (DistanceSquared (a, b));
}

void Normalize (Point2D<auto>& a) {
    a /= sqrt (Dot2D (a, a));
}

//------------------------------------------------------------------------------

// Point3D - Point3D - Point3D - Point3D - Point3D - Point3D - Point3D - Point3D

//------------------------------------------------------------------------------

//! 3D point.
//!< \sa Distance3D(const Point3D& a, const Point3D& b) DistanceSquared3D(const
//!< Point3D& a, const Point3D& b) Normalize3D(Point3D& a) Dot3D(const Point3D&
//!< a, const Point3D& b)
struct Point3D : Point2D<float> {
    float z {0.0f};

    constexpr Point3D ( ) {}

    constexpr Point3D (float in_x, float in_y, float in_z):
            Point2D {in_x, in_y}, z (in_z) {}

    constexpr explicit Point3D (const Point2D& p2d, float in_z = 0.0f):
            Point2D (p2d), z (in_z) {}

    // TODO: Implement map height check auto-z

    Point3D& operator += (const Point3D& rhs) {
        x += rhs.x;
        y += rhs.y;
        z += rhs.z;
        return *this;
    }

    Point3D& operator -= (const Point3D& rhs) {
        x -= rhs.x;
        y -= rhs.y;
        z -= rhs.z;
        return *this;
    }

    Point3D& operator *= (float rhs) {
        x *= rhs;
        y *= rhs;
        z *= rhs;
        return *this;
    }

    Point3D& operator /= (float rhs) {
        x /= rhs;
        y /= rhs;
        z /= rhs;
        return *this;
    }

    bool operator == (const Point3D& rhs) const {
        return x == rhs.x && y == rhs.y && z == rhs.z;
    }

    bool operator != (const Point3D& rhs) const {
        return !(*this == rhs);
    }

}; // struct Point3D

Point3D operator + (const Point3D& lhs, const Point3D& rhs) {
    return {lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z};
}

Point3D operator - (const Point3D& lhs, const Point3D& rhs) {
    return {lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z};
}

Point3D operator * (const Point3D& lhs, float rhs) {
    return {lhs.x * rhs, lhs.y * rhs, lhs.z * rhs};
}

Point3D operator * (float lhs, const Point3D& rhs) {
    return rhs * lhs;
}

Point3D operator / (const Point3D& lhs, float rhs) {
    return {lhs.x / rhs, lhs.y / rhs, lhs.z / rhs};
}

Point3D operator / (float lhs, const Point3D& rhs) {
    return rhs / lhs;
}

float Dot3D (const Point3D& a, const Point3D& b) {
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

float Distance3D (const Point3D& a, const Point3D& b) {
    const Point3D diff = a - b;
    return sqrt (Dot3D (diff, diff));
}

float DistanceSquared3D (const Point3D& a, const Point3D& b) {
    const Point3D diff = a - b;
    return Dot3D (diff, diff);
}

void Normalize3D (Point3D& a) {
    a /= sqrt (Dot3D (a, a));
}



} // namespace points

using Point2D  = points::Point2D<float>;
using Point2DI = points::Point2D<unsigned int>;

using Rect2D  = points::Rect2D<float>;
using Rect2DI = points::Rect2D<unsigned int>;

using Point3D = points::Point3D;

} // namespace sc2
