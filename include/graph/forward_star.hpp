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
  using reverse_node_iterator = offset_storage::reverse_iterator;
  using const_reverse_node_iterator = offset_storage::const_reverse_iterator;
  using reverse_node_range = boost::iterator_range<reverse_node_iterator>;
  using const_reverse_node_range =
      boost::iterator_range<const_reverse_node_iterator>;

  // defines for edges
  using value_type = std::uint64_t;
  using storage_type = std::vector<value_type>;
  using edge_iterator = storage_type::iterator;
  using const_edge_iterator = storage_type::const_iterator;
  using edge_range = boost::iterator_range<edge_iterator>;
  using const_edge_range = boost::iterator_range<const_edge_iterator>;
  using reverse_edge_iterator = storage_type::reverse_iterator;
  using const_reverse_edge_iterator = storage_type::const_reverse_iterator;
  using reverse_edge_range = boost::iterator_range<reverse_edge_iterator>;
  using const_reverse_edge_range =
      boost::iterator_range<const_reverse_edge_iterator>;

private:
  // cannot construct without an appropriate factory
  ForwardStarGraph();

  std::vector<std::size_t> node_offsets;
  storage_type edges;

  // ensure that the respective factory is allowed to acces the graph
  friend class ForwardStarGraphFactory;
};

} // namespace graph
} // namespace project_x

#endif // PROJECT_X_GRAPH_FORWARD_STAR_HPP_
