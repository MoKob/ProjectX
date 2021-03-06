#include "graph/forward_star.hpp"
#include "log/logger.hpp"

#include <cassert>
#include <iterator>

namespace project_x {
namespace graph {

// construction
std::size_t ForwardStar::number_of_nodes() const {
  // a graph should never be empty. The factory always needs to add at least a
  // sentinel
  assert(!node_offsets.empty());
  return node_offsets.size() - 1;
}

std::size_t ForwardStar::number_of_edges() const { return edge_storage.size(); }

// ranges / begin / end
ForwardStar::node_iterator ForwardStar::node_begin() {
  return &node_offsets.front();
}
ForwardStar::const_node_iterator ForwardStar::node_begin() const {
  return &node_offsets.front();
}

ForwardStar::node_iterator ForwardStar::node_end() {
  return &node_offsets.back();
}
ForwardStar::const_node_iterator ForwardStar::node_end() const {
  return &node_offsets.back();
}

ForwardStar::node_range ForwardStar::nodes() {
  return {node_begin(), node_end()};
}

ForwardStar::const_node_range ForwardStar::nodes() const {
  return {node_begin(), node_end()};
}

// Translating into IDs
NodeID ForwardStar::node_id(node_iterator const node_itr) const {
  return *node_itr - &node_offsets.front();
}
NodeID ForwardStar::node_id(const_node_iterator const node_itr) const {
  return std::distance(&node_offsets.front(), *node_itr);
}
NodeID ForwardStar::node_id(offset_ptr const node_itr) const {
  return node_itr - &node_offsets.front();
}

EdgeID ForwardStar::edge_id(const_edge_iterator const edge_itr) const {
  return std::distance(edge_storage.cbegin(), edge_itr);
}
EdgeID ForwardStar::edge_id(edge_iterator const edge_itr) const {
  return std::distance(edge_storage.begin(),
                       static_cast<const_edge_iterator>(edge_itr));
}

ForwardStar::edge_iterator ForwardStar::edges_begin() {
  return edge_storage.begin();
}
ForwardStar::const_edge_iterator ForwardStar::edges_begin() const {
  return edge_storage.cbegin();
}

ForwardStar::edge_iterator ForwardStar::edges_begin(NodeID const id) {
  return edge_storage.begin() + node_offsets[id];
}
ForwardStar::const_edge_iterator
ForwardStar::edges_begin(NodeID const id) const {
  return edge_storage.cbegin() + node_offsets[id];
}
ForwardStar::edge_iterator ForwardStar::edges_begin(node_iterator const itr) {
  return edge_storage.begin() + **itr;
}
ForwardStar::const_edge_iterator
ForwardStar::edges_begin(const_node_iterator const itr) const {
  return edge_storage.cbegin() + **itr;
}
ForwardStar::edge_iterator ForwardStar::edges_begin(offset_ptr itr) {
  return edge_storage.begin() + *itr;
}

ForwardStar::edge_iterator ForwardStar::edges_end(NodeID const id) {
  return edge_storage.begin() + node_offsets[id + 1];
}
ForwardStar::const_edge_iterator ForwardStar::edges_end(NodeID const id) const {
  return edge_storage.cbegin() + node_offsets[id + 1];
}
ForwardStar::edge_iterator ForwardStar::edges_end(node_iterator const itr) {
  return edge_storage.begin() + **(itr + 1);
}
ForwardStar::edge_iterator ForwardStar::edges_end(offset_ptr const itr) {
  return edge_storage.begin() + *(itr + 1);
}
ForwardStar::const_edge_iterator
ForwardStar::edges_end(const_node_iterator const itr) const {
  return edge_storage.cbegin() + **(itr + 1);
}

ForwardStar::edge_iterator ForwardStar::edges_end() {
  return edge_storage.end();
}
ForwardStar::const_edge_iterator ForwardStar::edges_end() const {
  return edge_storage.cend();
}
ForwardStar::edge_iterator ForwardStar::edge(EdgeID const id) {
  return edge_storage.begin() + id;
}
ForwardStar::const_edge_iterator ForwardStar::edge(EdgeID const id) const {
  return edge_storage.cbegin() + id;
}

ForwardStar::edge_range ForwardStar::edges() {
  return {edge_storage.begin(), edge_storage.end()};
}
ForwardStar::const_edge_range ForwardStar::edges() const {
  return {edge_storage.cbegin(), edge_storage.cend()};
}
ForwardStar::edge_range ForwardStar::edges(NodeID const node_id) {
  return {edges_begin(node_id), edges_end(node_id)};
}
ForwardStar::const_edge_range ForwardStar::edges(NodeID const node_id) const {
  return {edges_begin(node_id), edges_end(node_id)};
}
ForwardStar::edge_range ForwardStar::edges(node_iterator const itr) {
  return {edges_begin(itr), edges_end(itr)};
}
ForwardStar::edge_range ForwardStar::edges(offset_ptr const itr) {
  return {edges_begin(itr), edges_end(itr)};
}
ForwardStar::const_edge_range
ForwardStar::edges(const_node_iterator const itr) const {
  return {edges_begin(itr), edges_end(itr)};
}

void ForwardStar::serialise(io::File &file) const {
  log::Logger logger;
  std::uint64_t count_offsets = node_offsets.size(),
                count_targets = edge_storage.size();
  logger.message(log::Level::DEBUG,
                 "Serialise: writing " + std::to_string(count_offsets - 1) +
                     " nodes and " + std::to_string(count_targets) + " edges.");
  file.write_container(node_offsets);
  file.write_container(edge_storage);
}

void ForwardStar::deserialise(io::File &file) {
  file.read_container(node_offsets);
  file.read_container(edge_storage);
  log::Logger logger;
  logger.message(log::Level::DEBUG,
                 "Deserialise: got " + std::to_string(node_offsets.size() - 1) +
                     " nodes and " + std::to_string(edge_storage.size()) +
                     " edges.");
}

} // namespace graph
} // namespace project_x
