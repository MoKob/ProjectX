#include "graph/routing.hpp"

#include <exception>

// make sure we get a new main function here
#define BOOST_TEST_MODULE RoutingGraph
#define BOOST_TEST_MAIN
#include <boost/test/unit_test.hpp>

using namespace project_x;

inline graph::WeightTimeDistance
makeWeight(std::uint32_t weight, std::uint32_t time, std::uint32_t distance) {
  return {weight, time, distance};
}

// test a construction of an undirected graph from a set of edges
BOOST_AUTO_TEST_CASE(edge_weight_comparisons) {
  auto unit = makeWeight(1, 1, 1);
  auto weight = makeWeight(1, 0, 0);
  auto time = makeWeight(0, 1, 0);
  auto distance = makeWeight(0, 0, 1);

  BOOST_CHECK(unit < unit + weight);
  BOOST_CHECK(unit < unit + time);
  BOOST_CHECK(unit < unit + distance);
  BOOST_CHECK(!(unit < unit));

  BOOST_CHECK(unit <= unit + weight);
  BOOST_CHECK(unit <= unit + time);
  BOOST_CHECK(unit <= unit + distance);
  BOOST_CHECK(unit <= unit);

  BOOST_CHECK(unit + weight > unit);
  BOOST_CHECK(unit + time > unit);
  BOOST_CHECK(unit + distance > unit);
  BOOST_CHECK(!(unit > unit));

  BOOST_CHECK(unit + weight >= unit);
  BOOST_CHECK(unit + time >= unit);
  BOOST_CHECK(unit + distance >= unit);
  BOOST_CHECK(unit >= unit);

  BOOST_CHECK(unit == unit);
  BOOST_CHECK(unit != unit + unit);

  auto twice = unit;
  twice += unit;
  BOOST_CHECK(unit < twice);
  BOOST_CHECK(unit == twice - unit);
  auto once = twice;
  once -= unit;
  BOOST_CHECK(unit == once);
}
