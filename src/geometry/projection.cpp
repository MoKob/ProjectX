#include "geometry/projection.hpp"
#include "geometry/constants.hpp"

#include <cmath>
#include <utility>

namespace {
// conversion factors between different angle formats
const constexpr long double degree_to_rad = 0.017453292519943295769236907684886;
const constexpr long double rad_to_degree = 1.0 / degree_to_rad;
} // namespace

namespace project_x {
namespace geometry {

// projection functions allow converting between coordinate formats
WebMercatorFixedCoorinate projectWgsWebMerc(WGS84FixedCoorinate const wgs) {
  auto const longitude_radians =
      coordinate::to_floating(wgs.longitude) * degree_to_rad;

  auto projected_longitude = 128.0 / M_PI * (longitude_radians + M_PI);

  auto web_longitude =
      FixedWebMercLongitude{coordinate::to_fixed(projected_longitude)};

  auto const latitude_radians =
      coordinate::to_floating(wgs.latitude) * degree_to_rad;

  auto const sin_lat = std::sin(latitude_radians);

  auto projected_latitude =
      -((rad_to_degree * std::log((1 + sin_lat) / (1 - sin_lat))) * 64. / 180. -
        128);

  auto web_latitude =
      FixedWebMercLatitude{coordinate::to_fixed(projected_latitude)};

  return {std::move(web_latitude), std::move(web_longitude)};
}

} // namespace geometry
} // namespace project_x
