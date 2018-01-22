#include "algorithm/partition.hpp"
#include "algorithm/union_find.hpp"
#include "graph/id.hpp"

#include <queue>

namespace project_x {
namespace algorithm {

namespace {
std::vector<NodeID> close_nodes(graph::ForwardStar const &graph,
                                NodeID const to_node,
                                std::uint32_t node_count) {
  std::vector<NodeID> nodes;
  nodes.push_back(to_node);

  return nodes;
}
} // namespace

Partition::Partition(graph::ForwardStar const &graph,
                     std::uint32_t const max_cell_size)
    : graph(graph) {
  auto cells = compute_cells(max_cell_size);
}

std::vector<std::uint32_t>
Partition::compute_cells(std::uint32_t max_cell_size) {
  algorithm::UnionFind uf(graph.number_of_nodes());
}

} // namespace algorithm
} // namespace project_x
