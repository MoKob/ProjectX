#include "graph/forward_star.hpp"
#include "graph/forward_star_factory.hpp"
#include "io/file.hpp"
#include "log/logger.hpp"

#include <algorithm>
#include <exception>
#include <vector>

// make sure we get a new main function here
#define BOOST_TEST_MODULE ForwardStarGraph
#define BOOST_TEST_MAIN
#include <boost/test/unit_test.hpp>

using namespace project_x;

struct Edge {
  std::uint64_t source, target;
};

namespace details {
template <typename graph_type>
void run_test(graph_type &graph, std::vector<Edge> const &edges) {
  BOOST_CHECK_EQUAL(graph.number_of_nodes(), 7);
  {
    auto edge_itr = graph.edges_begin();
    auto edge_end = graph.edges_end();

    // iterating through the edges by range / id / itr should all yield the same
    std::uint64_t id = 0;
    for (auto target : graph.edges()) {
      BOOST_CHECK(edge_itr != edge_end);
      BOOST_CHECK_EQUAL(target, *edge_itr);
      BOOST_CHECK_EQUAL(edges[id].target, *graph.edge(id));
      BOOST_CHECK_EQUAL(edges[id].target, target);
      BOOST_CHECK_EQUAL(graph.edge_id(edge_itr), id);
      ++edge_itr;
      ++id;
    }
  }

  {
    std::size_t eid = 0;
    auto node_itr = graph.node_begin();
    std::uint64_t node_id = 0;
    for (auto node : graph.nodes()) {
      BOOST_CHECK(*node_itr == node);
      BOOST_CHECK_EQUAL(graph.node_id(node), node_id);
      BOOST_CHECK_EQUAL(graph.node_id(node_itr), node_id);
      BOOST_CHECK_EQUAL(**node_itr, *node);

      while (eid < edges.size() && edges[eid].source < graph.node_id(node))
        ++eid;

      auto edge_itr = graph.edges_begin(node);
      auto edge_itr_itr = graph.edges_begin(node_itr);
      auto const node_itr_const = node_itr;
      auto edge_itr_itr_const = graph.edges_begin(node_itr_const);
      BOOST_CHECK(edge_itr_itr_const == edge_itr_itr);
      auto const node_id_const = node_id;
      auto edge_itr_id = graph.edges_begin(node_id);
      auto edge_itr_id_const = graph.edges_begin(node_id_const);
      BOOST_CHECK(edge_itr_id == edge_itr_id_const);
      auto edge_end = graph.edges_end(node);
      auto edge_end_itr = graph.edges_end(node_itr);
      auto edge_end_itr_const = graph.edges_end(node_itr_const);
      BOOST_CHECK(edge_end_itr == edge_end_itr_const);
      auto edge_end_id = graph.edges_end(node_id);
      auto edge_end_id_const = graph.edges_end(node_id_const);
      BOOST_CHECK(edge_end_id == edge_end_id_const);

      auto range_itr = graph.edges(node_itr);
      auto range_id = graph.edges(node_id);
      auto range = graph.edges(node);
      BOOST_CHECK(edge_itr == range.begin());
      BOOST_CHECK(edge_end == range.end());
      BOOST_CHECK(edge_itr == range_itr.begin());
      BOOST_CHECK(edge_end == range_itr.end());
      BOOST_CHECK(edge_itr == range_id.begin());
      BOOST_CHECK(edge_end == range_id.end());
      for (auto target : graph.edges(node)) {
        BOOST_CHECK(edge_itr != edge_end);
        BOOST_CHECK(edge_itr_itr != edge_end_itr);
        BOOST_CHECK(edge_itr_id != edge_end_id);
        BOOST_CHECK_EQUAL(target, edges[eid++].target);
        BOOST_CHECK_EQUAL(target, *edge_itr++);
        BOOST_CHECK_EQUAL(target, *edge_itr_itr++);
        BOOST_CHECK_EQUAL(target, *edge_itr_id++);
      }
      // have we seen all edges
      BOOST_CHECK(edge_itr == edge_end);
      BOOST_CHECK(edge_itr_itr == edge_end_itr);
      BOOST_CHECK(edge_itr_id == edge_end_id);
      BOOST_CHECK(eid == edges.size() ||
                  edges[eid].source > graph.node_id(node));
      node_id++;
      ++node_itr;
    }
    BOOST_CHECK(node_itr == graph.node_end());
  }
}
} // namespace details

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
      graph::ForwardStarGraphFactory::produce_directed_from_edges(7, edges);
  std::stable_sort(
      edges.begin(), edges.end(),
      [](auto const &lhs, auto const &rhs) { return lhs.source < rhs.source; });

  details::run_test(graph, edges);
}

BOOST_AUTO_TEST_CASE(const_construct_undirected) {
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
  auto const graph =
      graph::ForwardStarGraphFactory::produce_directed_from_edges(7, edges);
  std::stable_sort(
      edges.begin(), edges.end(),
      [](auto const &lhs, auto const &rhs) { return lhs.source < rhs.source; });

  details::run_test(graph, edges);
}

BOOST_AUTO_TEST_CASE(throw_on_bound) {
  std::vector<Edge> edges{{0, 0}, {1, 0}};
  // throw on more sources than nodes
  BOOST_CHECK_THROW(
      graph::ForwardStarGraphFactory::produce_directed_from_edges(1, edges),
      std::out_of_range);

  edges.push_back({1, 2});
  // throw on larger target
  BOOST_CHECK_THROW(
      graph::ForwardStarGraphFactory::produce_directed_from_edges(2, edges),
      std::out_of_range);
}

BOOST_AUTO_TEST_CASE(graph_io) {
  log::Logger logger;
  logger.set_stream(&std::cout);
  std::vector<Edge> edges{{0, 1}, {2, 1}, {1, 2}};
  auto const graph =
      graph::ForwardStarGraphFactory::produce_directed_from_edges(3, edges);

  io::File out("tmp.gr",
               io::mode::mWRITE | io::mode::mBINARY | io::mode::mVERSIONED);
  graph.serialise(out);
  out.close();

  auto const deserialised_graph =
      graph::ForwardStarGraphFactory::produce_from_file("tmp.gr");

  auto itr = graph.edges_begin();
  auto des_itr = deserialised_graph.edges_begin();
  for (; itr != graph.edges_end() && des_itr != deserialised_graph.edges_end();
       ++itr, ++des_itr) {
    BOOST_CHECK_EQUAL(*itr, *des_itr);
  }
  BOOST_CHECK(itr == graph.edges_end());
  BOOST_CHECK(des_itr == deserialised_graph.edges_end());
}
