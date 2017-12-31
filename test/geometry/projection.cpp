#include "geometry/projection.hpp"
#include "geometry/coordinate.hpp"

#include <iostream>

// make sure we get a new main function here
#define BOOST_TEST_MODULE Geometry
#define BOOST_TEST_MAIN
#include <boost/test/unit_test.hpp>

using namespace project_x;

geometry::WGS84FixedCoorinate make_coordinate(double const lat,
                                              double const lon) {
  return {geometry::FixedWGSLatitude{geometry::coordinate::to_fixed(lat)},
          geometry::FixedWGSLongitude{geometry::coordinate::to_fixed(lon)}};
}

// test a construction of an undirected graph from a set of edges
BOOST_AUTO_TEST_CASE(mercator_projection) {
  auto c1 = make_coordinate(0, 0);
  auto c1m = geometry::projectWgsWebMerc(c1);
  BOOST_CHECK_CLOSE(128.0, geometry::coordinate::to_floating(c1m.latitude),
                    0.001);
  BOOST_CHECK_CLOSE(128.0, geometry::coordinate::to_floating(c1m.longitude),
                    0.001);

  auto c2 = make_coordinate(45, 135);
  auto c2m = geometry::projectWgsWebMerc(c2);
  BOOST_CHECK_CLOSE(92.0896, geometry::coordinate::to_floating(c2m.latitude),
                    0.001);
  BOOST_CHECK_CLOSE(224.0, geometry::coordinate::to_floating(c2m.longitude),
                    0.001);
}
