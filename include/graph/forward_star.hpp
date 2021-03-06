#ifndef PROJECT_X_GRAPH_FORWARD_STAR_HPP_
#define PROJECT_X_GRAPH_FORWARD_STAR_HPP_

#include <boost/range/iterator_range.hpp>

#include <cstdint>
#include <utility>
#include <vector>

#include "graph/id.hpp"
#include "io/file.hpp"
#include "io/serialisable.hpp"
#include "iterator/pointer.hpp"

namespace project_x {
namespace graph {

// A forward star graph offers simple connectivity based on IDs
class ForwardStar : public io::Serialisable {
public:
  // defines for nodes
  using offset_storage = std::vector<std::uint64_t>;
  using node_iterator = iterator::Pointer<std::uint64_t>;
  using offset_ptr = std::uint64_t *;
  using const_node_iterator = iterator::Pointer<std::uint64_t const>;
  using node_range = boost::iterator_range<node_iterator>;
  using const_node_range = boost::iterator_range<const_node_iterator>;

  // defines for edges
  using value_type = NodeID;
  using storage_type = std::vector<value_type>;
  using edge_iterator = storage_type::iterator;
  using const_edge_iterator = storage_type::const_iterator;
  using edge_range = boost::iterator_range<edge_iterator>;
  using const_edge_range = boost::iterator_range<const_edge_iterator>;
  // For future implementation:
  // using reverse_edge_iterator = storage_type::reverse_iterator;
  // using const_reverse_edge_iterator = storage_type::const_reverse_iterator;
  // using reverse_edge_range = boost::iterator_range<reverse_edge_iterator>;
  // using const_reverse_edge_range =
  //    boost::iterator_range<const_reverse_edge_iterator>;

  // the number of nodes in the graph. All nodes are labeled from 0 to n-1
  std::size_t number_of_nodes() const;
  std::size_t number_of_edges() const;

  // access to nodes by id, begin/end or range
  node_iterator node_begin();
  const_node_iterator node_begin() const;
  node_iterator node_end();
  const_node_iterator node_end() const;

  node_range nodes();
  const_node_range nodes() const;

  // access into the edges
  edge_iterator edges_begin();
  const_edge_iterator edges_begin() const;

  edge_iterator edges_begin(NodeID const);
  const_edge_iterator edges_begin(NodeID const) const;
  const_edge_iterator edges_begin(const_node_iterator const) const;
  edge_iterator edges_begin(node_iterator const);
  edge_iterator edges_begin(offset_ptr const);

  edge_iterator edges_end(NodeID const);
  const_edge_iterator edges_end(NodeID const) const;
  const_edge_iterator edges_end(const_node_iterator const) const;
  edge_iterator edges_end(node_iterator const);
  edge_iterator edges_end(offset_ptr const);
  edge_iterator edges_end();
  const_edge_iterator edges_end() const;
  edge_iterator edge(EdgeID const);
  const_edge_iterator edge(NodeID const) const;

  edge_iterator edge(node_iterator const);
  edge_iterator edge(offset_ptr const);
  const_edge_iterator edge(offset_ptr const) const;

  edge_range edges();
  const_edge_range edges() const;
  edge_range edges(NodeID const);
  const_edge_range edges(NodeID const) const;
  const_edge_range edges(const_node_iterator const) const;
  edge_range edges(node_iterator const);
  edge_range edges(offset_ptr const);

  // translating into IDs
  NodeID node_id(const_node_iterator const) const;
  NodeID node_id(node_iterator const) const;
  NodeID node_id(offset_ptr const) const;
  EdgeID edge_id(const_edge_iterator const) const;
  EdgeID edge_id(edge_iterator const) const;

  // storing / restoring
  void serialise(io::File &file) const;
  void deserialise(io::File &file);

private:
  offset_storage node_offsets;
  storage_type edge_storage;

  // ensure that the respective factory is allowed to acces the graph
  friend class ForwardStarFactory;
};

} // namespace graph
} // namespace project_x

#endif // PROJECT_X_GRAPH_FORWARD_STAR_HPP_
