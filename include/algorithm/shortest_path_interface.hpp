#ifndef PROJECT_X_ALGORITHM_SHORTEST_PATH_INTERFACE_HPP_
#define PROJECT_X_ALGORITHM_SHORTEST_PATH_INTERFACE_HPP_

#include "graph/id.hpp"
#include "route/route.hpp"
#include <vector>

namespace project_x {
namespace algorithm {

// A start/target location for a search
template <typename weight_type> struct Location {
  NodeID node;
  weight_type offset;
};

// general interface of how shortest path algorithms work
template <typename graph_type> class ShortestPathInterface {
public:
  using weight_type = typename graph_type::cost_type;
  using location_type = Location<weight_type>;

  // a direct path between two locations
  virtual route::Route<weight_type> operator()(location_type const &from,
                                               location_type const &to) = 0;
  // in case of multiple possible source/target candidates
  virtual route::Route<weight_type>
  operator()(std::vector<location_type> const &from,
             std::vector<location_type> const &to) = 0;
};

} // namespace algorithm
} // namespace project_x

#endif // PROJECT_X_ALGORITHM_SHORTEST_PATH_INTERFACE_HPP_
