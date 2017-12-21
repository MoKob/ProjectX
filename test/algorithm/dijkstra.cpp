#include "algorithm/dijkstra.hpp"
#include "graph/decorator.hpp"
#include "graph/decorator_factory.hpp"
#include "graph/forward_star.hpp"
#include "graph/forward_star_factory.hpp"
#include "graph/id.hpp"

#include <vector>

// make sure we get a new main function here
#define BOOST_TEST_MODULE Dijkstra
#define BOOST_TEST_MAIN
#include <boost/test/unit_test.hpp>

using namespace project_x;

struct Edge {
  NodeID source, target;
  int weight;
};

using DecoratedGraph = graph::edge::CostDecorator<int, graph::ForwardStar>;

// test a construction of an undirected graph from a set of edges
BOOST_AUTO_TEST_CASE(reach_first_with_high_weight) {
  //   (2)- - - 2
  //  /         |
  //  |        (5)
  //  |         |
  //  0- (10) - 1 <- (4) - 3
  std::vector<Edge> edges{{0, 1, 10}, {0, 2, 2}, {2, 1, 5}, {3, 1, 4}};
  DecoratedGraph graph =
      graph::ForwardStarFactory::produce_directed_from_edges(4, edges);
  graph::DecoratorFactory decorator_factory;
  decorator_factory.decorate<DecoratedGraph>(
      graph, edges, [](auto const &edge) { return edge.weight; });

  algorithm::Dijkstra<DecoratedGraph> dijkstra(graph);
  auto route = dijkstra({0, 0}, {1, 0});
  BOOST_CHECK_EQUAL(route.segments.size(), 2);

  auto no_route = dijkstra({0, 0}, {3, 0});
  BOOST_CHECK(no_route.segments.empty());
}

BOOST_AUTO_TEST_CASE(reach_first_with_high_weight_multi_source) {
  //   (2)- - - 2
  //  /         |
  //  |        (5)
  //  |         |
  //  0- (10) - 1 <- (4) - 3
  std::vector<Edge> edges{{0, 1, 10}, {0, 2, 2}, {2, 1, 5}, {3, 1, 4}};
  DecoratedGraph graph =
      graph::ForwardStarFactory::produce_directed_from_edges(4, edges);
  graph::DecoratorFactory decorator_factory;
  decorator_factory.decorate<DecoratedGraph>(
      graph, edges, [](auto const &edge) { return edge.weight; });

  algorithm::Dijkstra<DecoratedGraph> dijkstra(graph);

  std::vector<typename algorithm::Dijkstra<DecoratedGraph>::location_type>
      sources, targets;
  sources.push_back({0, 0});
  sources.push_back({3, 5});
  targets.push_back({1, 0});
  targets.push_back({2, 10});
  targets.push_back({2, 20});
  auto route = dijkstra(sources, targets);
  BOOST_CHECK_EQUAL(route.segments.size(), 2);

  targets.clear();
  sources.pop_back();
  targets.push_back({3, 0});
  auto no_route = dijkstra(sources, targets);
  BOOST_CHECK(no_route.segments.empty());
}
