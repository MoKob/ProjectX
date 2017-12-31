#ifndef PROJECT_X_GEOMETRY_COORDINATE_HPP_
#define PROJECT_X_GEOMETRY_COORDINATE_HPP_

#include "traits/strong_typedef.hpp"
#include "traits/typemap.hpp"

#include <cmath>

namespace project_x {
namespace geometry {

// standard google polyline precision for internal coordinate precision
const constexpr std::int32_t fixed_coordinate_precision = 1e05;

// lat/lon coordinates in fixed precision integer representation
using FixedWGSLatitude =
    traits::strong_typedef<std::int32_t, traits::typemap::tagWGSLatitude>;
using FixedWGSLongitude =
    traits::strong_typedef<std::int32_t, traits::typemap::tagWGSLongitude>;

// a fixed precision WGS84 coordinate
struct WGS84FixedCoorinate {
  FixedWGSLatitude latitude;
  FixedWGSLongitude longitude;
};

using FixedWebMercLatitude =
    traits::strong_typedef<std::int32_t, traits::typemap::tagWebMercLatitude>;
using FixedWebMercLongitude =
    traits::strong_typedef<std::int32_t, traits::typemap::tagWebMercLongitude>;

// a fixed precision WGS84 coordinate
struct WebMercatorFixedCoorinate {
  FixedWebMercLatitude latitude;
  FixedWebMercLongitude longitude;
};

// conversion functions to ensure easy adjustment of precision, if needed at
// some point
namespace coordinate {
template <typename lat_or_lon> double to_floating(lat_or_lon value) {
  return static_cast<double>(value.base()) / fixed_coordinate_precision;
}

inline std::int32_t to_fixed(double value) {
  return static_cast<std::int32_t>(
      std::round(value * fixed_coordinate_precision));
}
} // namespace coordinate

} // namespace geometry
} // namespace project_x

#endif // PROJECT_X_GEOMETRY_COORDINATE_HPP_
