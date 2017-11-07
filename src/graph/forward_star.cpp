#include "graph/forward_star.hpp"

#include <cassert>
#include <iterator>

namespace project_x {
namespace graph {

// construction
ForwardStarGraph::ForwardStarGraph() {}

std::size_t ForwardStarGraph::number_of_nodes() const {
  // a graph should never be empty. The factory always needs to add at least a
  // sentinel
  assert(!node_offsets.empty());
  return node_offsets.size() - 1;
}

// Access to nodes in the graph
ForwardStarGraph::node_iterator ForwardStarGraph::node(std::uint64_t const id) {
  return node_offsets.begin() + id;
}

ForwardStarGraph::const_node_iterator
ForwardStarGraph::node(std::uint64_t const id) const {
  return node_offsets.cbegin() + id;
}

// ranges / begin / end
ForwardStarGraph::node_iterator ForwardStarGraph::node_begin() {
  return node_offsets.begin();
}
ForwardStarGraph::const_node_iterator ForwardStarGraph::node_begin() const {
  return node_offsets.cbegin();
}

ForwardStarGraph::node_iterator ForwardStarGraph::node_end() {
  return node_offsets.end() - 1;
}
ForwardStarGraph::const_node_iterator ForwardStarGraph::node_end() const {
  return node_offsets.cend() - 1;
}

ForwardStarGraph::node_range ForwardStarGraph::nodes() {
  return {node_offsets.begin(), node_offsets.begin() + number_of_nodes()};
}

ForwardStarGraph::const_node_range ForwardStarGraph::nodes() const {
  return {node_offsets.cbegin(), node_offsets.cbegin() + number_of_nodes()};
}

// Translating into IDs
std::uint64_t
ForwardStarGraph::node_id(const_node_iterator const node_itr) const {
  return std::distance(node_offsets.cbegin(), node_itr);
}

std::uint64_t
ForwardStarGraph::edge_id(const_edge_iterator const edge_itr) const {
  return std::distance(edge_storage.cbegin(), edge_itr);
}

ForwardStarGraph::edge_iterator ForwardStarGraph::edges_begin() {
  return edge_storage.begin();
}
ForwardStarGraph::const_edge_iterator ForwardStarGraph::edges_begin() const {
  return edge_storage.cbegin();
}
ForwardStarGraph::edge_iterator
ForwardStarGraph::edges_begin(const_node_iterator const node_itr) {
  return edge_storage.begin() + *node_itr;
}
ForwardStarGraph::const_edge_iterator
ForwardStarGraph::edges_begin(const_node_iterator const node_itr) const {
  return edge_storage.cbegin() + *node_itr;
}
ForwardStarGraph::edge_iterator
ForwardStarGraph::edges_begin(std::uint64_t const id) {
  return edge_storage.begin() + node_offsets[id];
}
ForwardStarGraph::const_edge_iterator
ForwardStarGraph::edges_begin(std::uint64_t const id) const {
  return edge_storage.cbegin() + node_offsets[id];
}

ForwardStarGraph::edge_iterator
ForwardStarGraph::edges_end(const_node_iterator const node_itr) {
  return edge_storage.begin() + *(node_itr + 1);
}
ForwardStarGraph::const_edge_iterator
ForwardStarGraph::edges_end(const_node_iterator const node_itr) const {
  return edge_storage.cbegin() + *(node_itr + 1);
}
ForwardStarGraph::edge_iterator
ForwardStarGraph::edges_end(std::uint64_t const id) {
  return edge_storage.begin() + node_offsets[id + 1];
}
ForwardStarGraph::const_edge_iterator
ForwardStarGraph::edges_end(std::uint64_t const id) const {
  return edge_storage.cbegin() + node_offsets[id + 1];
}
ForwardStarGraph::edge_iterator ForwardStarGraph::edges_end() {
  return edge_storage.end();
}
ForwardStarGraph::const_edge_iterator ForwardStarGraph::edges_end() const {
  return edge_storage.cend();
}

ForwardStarGraph::edge_range ForwardStarGraph::edges() {
  return {edge_storage.begin(), edge_storage.end()};
}
ForwardStarGraph::const_edge_range ForwardStarGraph::edges() const {
  return {edge_storage.cbegin(), edge_storage.cend()};
}
ForwardStarGraph::edge_range
ForwardStarGraph::edges(const_node_iterator const node_itr) {
  return {edges_begin(node_itr), edges_end(node_itr)};
}
ForwardStarGraph::edge_range
ForwardStarGraph::edges(std::uint64_t const node_id) {
  return {edges_begin(node_id), edges_end(node_id)};
}
ForwardStarGraph::const_edge_range
ForwardStarGraph::edges(const_node_iterator const node_itr) const {
  return {edges_begin(node_itr), edges_end(node_itr)};
}
ForwardStarGraph::const_edge_range
ForwardStarGraph::edges(std::uint64_t const node_id) const {
  return {edges_begin(node_id), edges_end(node_id)};
}

} // namespace graph
} // namespace project_x
