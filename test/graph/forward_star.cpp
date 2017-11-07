#include "graph/forward_star.hpp"
#include "graph/forward_star_factory.hpp"

// make sure we get a new main function here
#define BOOST_TEST_MODULE ForwardStarGraph
#define BOOST_TEST_MAIN
#include <boost/test/unit_test.hpp>

struct Edge {
  std::uint64_t source, target;
};

// test a construction of an undirected graph from a set of edges
BOOST_AUTO_TEST_CASE(construct_undirected) {
  //
  // 0 -> 1 <-> 2
  //
  // 3 - > 4
  // |
  // v
  // 5
  //
  // 6
  //
  // define a basic directed graph
  std::vector<Edge> edges{{0, 1}, {2, 1}, {1, 2}, {1, 0}, {3, 4}, {3, 5}};
  auto graph =
      project_x::graph::ForwardStarGraphFactory::produce_directed_from_edges(
          7, edges);

  BOOST_CHECK_EQUAL(graph.number_of_nodes(), 7);
}
