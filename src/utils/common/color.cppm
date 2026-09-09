module;
#include <cstdint>
#include <iostream>
#include <string>
export module color;

namespace {
using std::stoul;
using std::string;
using std::string_view;
using std::cout;
} // using declarations


export namespace sc2 {

//! RGB Color.
struct Color
{
    uint8_t R { 255 };
    uint8_t G { 255 };
    uint8_t B { 255 };

    constexpr Color ( ) = default;

    constexpr Color ( uint8_t in_R, uint8_t in_G, uint8_t in_B )
      : R ( in_R ),
        G ( in_G ),
        B ( in_B ) {}

    /*! @brief Converts a hex color to RGB values.
     * @param {string_view} hex_color
     */
    explicit Color ( string_view hex_color ) {
        if ( hex_color.size( ) == 7 && hex_color.starts_with ( '#' ) ) {
            hex_color.remove_prefix ( 1 );
        }
        if ( hex_color.size( ) == 6 ) {
            R = static_cast<uint8_t> (
              stoul ( string ( hex_color.substr ( 0, 2 ) ), nullptr, 16 )
            );
            G = static_cast<uint8_t> (
              stoul ( string ( hex_color.substr ( 2, 2 ) ), nullptr, 16 )
            );
            B = static_cast<uint8_t> (
              stoul ( string ( hex_color.substr ( 4, 2 ) ), nullptr, 16 )
            );
        } else {
            cout << "Invalid hex_color; set to White instead." << '\n';
        }
    }


}; // struct Color

constexpr Color White = { 255, 255, 255 };
constexpr Color Gray  = { 128, 128, 128 };
constexpr Color Black = { 0, 0, 0 };

constexpr Color Red     = { 255, 0, 0 };
constexpr Color Orange  = { 255, 128, 0 };
constexpr Color Yellow  = { 255, 255, 0 };
constexpr Color Lime    = { 0, 255, 0 };
constexpr Color Green   = { 0, 128, 0 }; // Lime is better for `good`
constexpr Color Blue    = { 0, 0, 255 };
constexpr Color Cyan    = { 0, 255, 255 };
constexpr Color Magenta = { 255, 0, 255 };
constexpr Color Purple  = { 128, 0, 128 };


} // namespace sc2
