#ifndef PROJECT_X_GRAPH_FORWARD_STAR_HPP_
#define PROJECT_X_GRAPH_FORWARD_STAR_HPP_

#include <boost/range/iterator_range.hpp>
#include <cstdint>
#include <vector>

namespace project_x {
namespace graph {

// A forward star graph offers simple connectivity based on IDs
class ForwardStarGraph {
public:
  // defines for nodes
  using offset_storage = std::vector<std::uint64_t>;
  using node_iterator = offset_storage::iterator;
  using const_node_iterator = offset_storage::const_iterator;
  using node_range = boost::iterator_range<node_iterator>;
  using const_node_range = boost::iterator_range<const_node_iterator>;

  // defines for edges
  using value_type = std::uint64_t;
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

  // access to nodes by id, begin/end or range
  node_iterator node_begin();
  const_node_iterator node_begin() const;
  node_iterator node_end();
  const_node_iterator node_end() const;

  node_iterator node(std::uint64_t const);
  const_node_iterator node(std::uint64_t const) const;

  node_range nodes();
  const_node_range nodes() const;

  // access into the edges
  edge_iterator edges_begin();
  const_edge_iterator edges_begin() const;
  edge_iterator edges_begin(const_node_iterator const);
  const_edge_iterator edges_begin(const_node_iterator const) const;
  edge_iterator edges_begin(std::uint64_t const);
  const_edge_iterator edges_begin(std::uint64_t const) const;

  edge_iterator edges_end(const_node_iterator const);
  const_edge_iterator edges_end(const_node_iterator const) const;
  edge_iterator edges_end(std::uint64_t const);
  const_edge_iterator edges_end(std::uint64_t const) const;
  edge_iterator edges_end();
  const_edge_iterator edges_end() const;

  edge_range edges();
  const_edge_range edges() const;
  edge_range edges(const_node_iterator const);
  edge_range edges(std::uint64_t const);
  const_edge_range edges(const_node_iterator const) const;
  const_edge_range edges(std::uint64_t const) const;

  // translating into IDs
  std::uint64_t node_id(const_node_iterator const) const;
  std::uint64_t edge_id(const_edge_iterator const) const;

private:
  // cannot construct without an appropriate factory
  ForwardStarGraph();

  std::vector<std::size_t> node_offsets;
  storage_type edge_storage;

  // ensure that the respective factory is allowed to acces the graph
  friend class ForwardStarGraphFactory;
};

} // namespace graph
} // namespace project_x

#endif // PROJECT_X_GRAPH_FORWARD_STAR_HPP_
