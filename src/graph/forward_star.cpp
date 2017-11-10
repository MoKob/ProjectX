#include "graph/forward_star.hpp"
#include "log/logger.hpp"

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

// ranges / begin / end
ForwardStarGraph::node_iterator ForwardStarGraph::node_begin() {
  return &node_offsets.front();
}
ForwardStarGraph::const_node_iterator ForwardStarGraph::node_begin() const {
  return &node_offsets.front();
}

ForwardStarGraph::node_iterator ForwardStarGraph::node_end() {
  return &node_offsets.back();
}
ForwardStarGraph::const_node_iterator ForwardStarGraph::node_end() const {
  return &node_offsets.back();
}

ForwardStarGraph::node_range ForwardStarGraph::nodes() {
  return {node_begin(), node_end()};
}

ForwardStarGraph::const_node_range ForwardStarGraph::nodes() const {
  return {node_begin(), node_end()};
}

// Translating into IDs
std::uint64_t ForwardStarGraph::node_id(node_iterator const node_itr) const {
  return *node_itr - &node_offsets.front();
}
std::uint64_t
ForwardStarGraph::node_id(const_node_iterator const node_itr) const {
  return std::distance(&node_offsets.front(), *node_itr);
}
std::uint64_t ForwardStarGraph::node_id(offset_ptr const node_itr) const {
  return node_itr - &node_offsets.front();
}

std::uint64_t
ForwardStarGraph::edge_id(const_edge_iterator const edge_itr) const {
  return std::distance(edge_storage.cbegin(), edge_itr);
}
std::uint64_t ForwardStarGraph::edge_id(edge_iterator const edge_itr) const {
  return std::distance(edge_storage.begin(),
                       static_cast<const_edge_iterator>(edge_itr));
}

ForwardStarGraph::edge_iterator ForwardStarGraph::edges_begin() {
  return edge_storage.begin();
}
ForwardStarGraph::const_edge_iterator ForwardStarGraph::edges_begin() const {
  return edge_storage.cbegin();
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
ForwardStarGraph::edges_begin(node_iterator const itr) {
  return edge_storage.begin() + **itr;
}
ForwardStarGraph::const_edge_iterator
ForwardStarGraph::edges_begin(const_node_iterator const itr) const {
  return edge_storage.cbegin() + **itr;
}
ForwardStarGraph::edge_iterator ForwardStarGraph::edges_begin(offset_ptr itr) {
  return edge_storage.begin() + *itr;
}

ForwardStarGraph::edge_iterator
ForwardStarGraph::edges_end(std::uint64_t const id) {
  return edge_storage.begin() + node_offsets[id + 1];
}
ForwardStarGraph::const_edge_iterator
ForwardStarGraph::edges_end(std::uint64_t const id) const {
  return edge_storage.cbegin() + node_offsets[id + 1];
}
ForwardStarGraph::edge_iterator
ForwardStarGraph::edges_end(node_iterator const itr) {
  return edge_storage.begin() + **(itr + 1);
}
ForwardStarGraph::edge_iterator
ForwardStarGraph::edges_end(offset_ptr const itr) {
  return edge_storage.begin() + *(itr + 1);
}
ForwardStarGraph::const_edge_iterator
ForwardStarGraph::edges_end(const_node_iterator const itr) const {
  return edge_storage.cbegin() + **(itr + 1);
}

ForwardStarGraph::edge_iterator ForwardStarGraph::edges_end() {
  return edge_storage.end();
}
ForwardStarGraph::const_edge_iterator ForwardStarGraph::edges_end() const {
  return edge_storage.cend();
}
ForwardStarGraph::edge_iterator ForwardStarGraph::edge(std::uint64_t const id) {
  return edge_storage.begin() + id;
}
ForwardStarGraph::const_edge_iterator
ForwardStarGraph::edge(std::uint64_t const id) const {
  return edge_storage.cbegin() + id;
}

ForwardStarGraph::edge_range ForwardStarGraph::edges() {
  return {edge_storage.begin(), edge_storage.end()};
}
ForwardStarGraph::const_edge_range ForwardStarGraph::edges() const {
  return {edge_storage.cbegin(), edge_storage.cend()};
}
ForwardStarGraph::edge_range
ForwardStarGraph::edges(std::uint64_t const node_id) {
  return {edges_begin(node_id), edges_end(node_id)};
}
ForwardStarGraph::const_edge_range
ForwardStarGraph::edges(std::uint64_t const node_id) const {
  return {edges_begin(node_id), edges_end(node_id)};
}
ForwardStarGraph::edge_range ForwardStarGraph::edges(node_iterator const itr) {
  return {edges_begin(itr), edges_end(itr)};
}
ForwardStarGraph::edge_range ForwardStarGraph::edges(offset_ptr const itr) {
  return {edges_begin(itr), edges_end(itr)};
}
ForwardStarGraph::const_edge_range
ForwardStarGraph::edges(const_node_iterator const itr) const {
  return {edges_begin(itr), edges_end(itr)};
}

void ForwardStarGraph::serialise(io::File &file) const {
  log::Logger logger;
  std::uint64_t count_offsets = node_offsets.size(),
                count_targets = edge_storage.size();
  logger.message(log::Level::DEBUG,
                 "Serialise: writing " + std::to_string(count_offsets - 1) +
                     " nodes and " + std::to_string(count_targets) + " edges.");
  file.write_pod(count_offsets);
  file.write_pod(count_targets);
  file.write_pod(node_offsets);
  file.write_pod(edge_storage);
}

void ForwardStarGraph::deserialise(io::File &file) {
  log::Logger logger;
  std::uint64_t count_offsets = 0, count_targets = 0;
  file.read_pod(count_offsets);
  file.read_pod(count_targets);
  logger.message(log::Level::DEBUG,
                 "Deserialise: got " + std::to_string(count_offsets - 1) +
                     " nodes and " + std::to_string(count_targets) + " edges.");
  node_offsets.resize(count_offsets);
  edge_storage.resize(count_targets);
  file.read_pod(node_offsets);
  file.read_pod(edge_storage);
}

} // namespace graph
} // namespace project_x
