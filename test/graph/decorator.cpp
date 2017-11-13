#include "graph/decorator.hpp"
#include "graph/decorator_factory.hpp"
#include "graph/forward_star.hpp"
#include "graph/forward_star_factory.hpp"
#include "graph/id.hpp"
#include "io/file.hpp"
#include "io/wrappers.hpp"
#include "log/logger.hpp"

#include <algorithm>
#include <exception>
#include <string>
#include <vector>

// make sure we get a new main function here
#define BOOST_TEST_MODULE Decorator
#define BOOST_TEST_MAIN
#include <boost/test/unit_test.hpp>

using namespace project_x;

struct Data {
  int data;
};

struct Cost {
  int weight;
};

struct Edge {
  NodeID source, target;
  Data data;
  Cost cost;
};

// Fully Annotated Graph
using CostGraph = graph::edge::CostDecorator<Cost, graph::ForwardStar>;
using DataCostGraph = graph::edge::DataDecorator<Data, CostGraph>;
using AnnotatedGraph = graph::edge::ByteDecorator<DataCostGraph>;

AnnotatedGraph make_graph() {
  std::vector<Edge> edges{{0, 1, {1}, {2}},  {2, 1, {3}, {4}},
                          {1, 2, {5}, {6}},  {1, 0, {7}, {8}},
                          {3, 4, {9}, {10}}, {3, 5, {11}, {12}}};
  AnnotatedGraph graph(
      graph::ForwardStarFactory::produce_directed_from_edges(7, edges));

  graph::DecoratorFactory decorator_factory;
  decorator_factory.decorate<CostGraph>(
      graph, edges, [](auto const &edge) { return edge.cost; });
  decorator_factory.decorate<DataCostGraph>(
      graph, edges, [](auto const &edge) { return edge.data; });
  decorator_factory.decorate<AnnotatedGraph>(graph, edges, [](auto const &) {
    return io::SerialisableContainer<std::string>("Hello World");
  });

  return graph;
}

// test a construction of an undirected graph from a set of edges
BOOST_AUTO_TEST_CASE(check_annotations) {
  // create the basic graph to check the annotations on
  auto const graph = make_graph();

  io::File out_file("decorated_graph.dgr",
                    io::mode::mWRITE | io::mode::mBINARY |
                        io::mode::mVERSIONED);
  graph.serialise(out_file);
  out_file.close();

  AnnotatedGraph read_graph;
  io::File in_file("decorated_graph.dgr",
                   io::mode::mREAD | io::mode::mBINARY | io::mode::mVERSIONED);
  read_graph.deserialise(in_file);

  for (EdgeID eid = 0; eid < graph.number_of_edges(); ++eid) {
    BOOST_CHECK_EQUAL(graph.cost(eid).weight, read_graph.cost(eid).weight);
    BOOST_CHECK_EQUAL(graph.data(eid).data, read_graph.data(eid).data);
    BOOST_CHECK_EQUAL(graph.bytes(eid), read_graph.bytes(eid));
  }

  // query and verify all annotations for the graph
}
