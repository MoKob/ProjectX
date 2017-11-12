#include "algorithm/scc.hpp"
#include "graph/forward_star.hpp"
#include "graph/forward_star_factory.hpp"
#include "graph/id.hpp"
#include "log/logger.hpp"

#include <algorithm>
#include <exception>
#include <vector>

// make sure we get a new main function here
#define BOOST_TEST_MODULE AlgorithmSCC
#define BOOST_TEST_MAIN
#include <boost/test/unit_test.hpp>

using namespace project_x;

struct Edge {
  NodeID source, target;
};

// test a construction of an undirected graph from a set of edges
BOOST_AUTO_TEST_CASE(multiple_components) {
  // 0  2  4
  // |  |  ^
  // |  |  |
  // |  v  |
  // 1  3  5
  // define a basic directed graph
  std::vector<Edge> edges{{0, 1}, {1, 0}, {2, 3}, {5, 4}};
  auto graph = graph::ForwardStarFactory::produce_directed_from_edges(6, edges);
  auto components = algorithm::SCC::compute(graph);

  BOOST_CHECK_EQUAL(components[0], components[1]);
  for (int i = 2; i < 6; ++i)
    BOOST_CHECK(components[0] != components[2]);
  BOOST_CHECK(components[2] != components[3]);
  BOOST_CHECK(components[4] != components[5]);
}
