#ifndef PROJECT_X_GEOMETRY_PROJECTION_HPP_
#define PROJECT_X_GEOMETRY_PROJECTION_HPP_

#include "geometry/coordinate.hpp"

namespace project_x {
namespace geometry {

// projection functions allow converting between coordinate formats
WebMercatorFixedCoorinate projectWgsWebMerc(WGS84FixedCoorinate const);

// TODO possibly implement back projection
// WGS84FixedCoorinate projectWebMercWgs(WebMercatorFixedCoorinate const);

} // namespace geometry
} // namespace project_x

#endif // PROJECT_X_GEOMETRY_PROJECTION_HPP_
