#include "geometry/coordinate.hpp"

// make sure we get a new main function here
#define BOOST_TEST_MODULE Geometry
#define BOOST_TEST_MAIN
#include <boost/test/unit_test.hpp>

using namespace project_x;

namespace {
geometry::WGS84FixedCoorinate make_coordinate(double lat, double lon) {
  return {geometry::FixedWGSLatitude{geometry::coordinate::to_fixed(lat)},
          geometry::FixedWGSLongitude{geometry::coordinate::to_fixed(lon)}};
}
}

// test a construction of an undirected graph from a set of edges
BOOST_AUTO_TEST_CASE(fixed_floating) {
  auto coordinate = make_coordinate(90, 180);
  BOOST_CHECK_EQUAL(geometry::coordinate::to_floating(coordinate.latitude),
                    90.0);
  BOOST_CHECK_EQUAL(geometry::coordinate::to_floating(coordinate.longitude),
                    180.0);
}
