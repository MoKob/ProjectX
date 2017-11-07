#ifndef PROJECT_X_GRAPH_FORWARD_STAR_FACTORY_HPP_
#define PROJECT_X_GRAPH_FORWARD_STAR_FACTORY_HPP_

#include "graph/forward_star.hpp"

#include <algorithm>
#include <cstdint>

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
                              container &edges, extractor_type extractor) {
    auto const by_source = [&extractor](auto const &lhs, auto const &rhs) {
      return extractor.source(lhs) < extractor.source(rhs);
    };

    // sort edges, so that they are grouped by source
    std::sort(edges.begin(), edges.end(), by_source);

    ForwardStarGraph graph;
    graph.node_offsets.reserve(number_of_nodes + 1);
    graph.node_offsets.push_back(0);
    graph.edge_storage.reserve(edges.size());

    auto edge = edges.begin();
    for (std::uint64_t node = 0; node < number_of_nodes; ++node) {
      // add all edges to the graph
      while (extractor.source(*edge) == node) {
        graph.edge_storage.push_back(extractor.target(*edge));
        ++edge;
      }
      // mark the end of the current edges
      graph.node_offsets.push_back(graph.edge_storage.size());
    }

    return graph;
  }
  // helper to allow construction with default extractor
  template <typename container>
  static ForwardStarGraph
  produce_directed_from_edges(std::uint64_t const number_of_nodes,
                              container &edges) {
    return produce_directed_from_edges(
        number_of_nodes, edges,
        details::SourceTargetExtractor<typename container::value_type>());
  }
};
}
} // namespace project_x

#endif // PROJECT_X_GRAPH_FORWARD_STAR_FACTORY_HPP_
