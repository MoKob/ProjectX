#ifndef PROJECT_X_GEOMETRY_CONSTANTS_HPP_
#define PROJECT_X_GEOMETRY_CONSTANTS_HPP_

#include <cmath>

namespace project_x {
namespace geometry {
namespace constants {
// radius of planet earth in meters
const constexpr long double earth_radius_meters = 6372797.560856;
// mercator projection limits the values based on a tubular projection of the
// earth surface
const constexpr long double merc_max_extent = earth_radius_meters * M_PI;
// the epsg ellipsoid does not support latitudes close to the poles
const constexpr double epsg3857_max_latitude = 85.051128779806592377;
} // namespace constants
} // namespace geometry
} // namespace project_x

#endif // PROJECT_X_GEOMETRY_CONSTANTS_HPP_
