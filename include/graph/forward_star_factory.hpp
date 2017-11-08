#ifndef PROJECT_X_GRAPH_FORWARD_STAR_FACTORY_HPP_
#define PROJECT_X_GRAPH_FORWARD_STAR_FACTORY_HPP_

#include "graph/forward_star.hpp"

#include <algorithm>
#include <cstdint>
#include <exception>

namespace project_x {
namespace graph {

namespace details {
template <typename edge> struct SourceTargetExtractor {
  std::uint64_t source(edge const &e) { return e.source; }
  std::uint64_t target(edge const &e) { return e.target; }
};
} // namespace details

class ForwardStarGraphFactory {
public:
  // create a forward star graph representation with directed edges. The edges
  // provided are sorted to represent be in the order of edges within the graph
  // Edges need to connect nodes identified by numbers from 0 to |N|-1.
  // The extractor has to provide a function source/target that returns this ID
  // Runs in O(|E| log |E|) and requires O(|V| + |E|) additional space
  template <typename container, typename extractor_type>
  static ForwardStarGraph
  produce_directed_from_edges(std::uint64_t const number_of_nodes,
                              container &edges, extractor_type extractor);

  // helper to allow construction with default extractor
  template <typename container>
  static ForwardStarGraph
  produce_directed_from_edges(std::uint64_t const number_of_nodes,
                              container &edges);
};

template <typename container, typename extractor_type>
ForwardStarGraph ForwardStarGraphFactory::produce_directed_from_edges(
    std::uint64_t const number_of_nodes, container &edges,
    extractor_type extractor) {
  auto const by_source = [&extractor](auto const &lhs, auto const &rhs) {
    return extractor.source(lhs) < extractor.source(rhs);
  };

  // sort edges, so that they are grouped by source
  std::stable_sort(edges.begin(), edges.end(), by_source);

  ForwardStarGraph graph;
  graph.node_offsets.reserve(number_of_nodes + 1);
  graph.node_offsets.push_back(0);
  graph.edge_storage.reserve(edges.size());

  auto edge = edges.begin();
  for (std::uint64_t node = 0; node < number_of_nodes; ++node) {
    // add all edges to the graph
    while (extractor.source(*edge) == node) {
      auto target = extractor.target(*edge);
      if (target >= number_of_nodes)
        throw std::out_of_range{
            "Node: " + std::to_string(target) +
            " is out of range. Number of nodes was specified as " +
            std::to_string(number_of_nodes)};
      graph.edge_storage.push_back(target);
      ++edge;
    }
    // mark the end of the current edges
    graph.node_offsets.push_back(graph.edge_storage.size());
  }
  if (edge != edges.end())
    throw std::out_of_range(
        "Some source vertices (" + std::to_string(extractor.target(*edge)) +
        " and up) are larger than the specified number of nodes.");

  return graph;
}
// helper to allow construction with default extractor
template <typename container>
ForwardStarGraph ForwardStarGraphFactory::produce_directed_from_edges(
    std::uint64_t const number_of_nodes, container &edges) {
  return produce_directed_from_edges(
      number_of_nodes, edges,
      details::SourceTargetExtractor<typename container::value_type>());
}

} // namespace graph
} // namespace project_x

#endif // PROJECT_X_GRAPH_FORWARD_STAR_FACTORY_HPP_
