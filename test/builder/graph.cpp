#include "builder/graph.hpp"
#include "graph/forward_star.hpp"
#include "graph/forward_star_factory.hpp"
#include "graph/id.hpp"
#include "io/file.hpp"
#include "log/logger.hpp"

// make sure we get a new main function here
#define BOOST_TEST_MODULE Builder
#define BOOST_TEST_MAIN
#include <boost/test/unit_test.hpp>

using namespace project_x;

// construct a graph using a graph builder. This is the way we will see graphs
// created from python libs/profiles
BOOST_AUTO_TEST_CASE(construct_builder) {
  // 1 -> 2 <-> 3    4 <-> 5
  // 0 -> 1 <-> 2    3 <-> 4 mapped
  builder::Graph<builder::Edge<std::string>> builder;
  builder.add_edge(1, 2, "");
  builder.add_edge(2, 3, "");
  builder.add_edge(3, 2, "");
  builder.add_edge(4, 5, "");
  builder.add_edge(5, 4, "");

  builder.build_graph_and_store("construct.gr");

  auto graph = graph::ForwardStarFactory::produce_from_file("construct.gr");
  BOOST_CHECK_EQUAL(graph.number_of_nodes(), 5);
  BOOST_CHECK_EQUAL(*graph.edges_begin((NodeID)0), 1);
  BOOST_CHECK_EQUAL(*graph.edges_begin((NodeID)2), 1);
}
