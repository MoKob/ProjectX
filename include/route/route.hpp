#ifndef PROJECT_X_ROUTE_ROUTE_HPP_
#define PROJECT_X_ROUTE_ROUTE_HPP_

#include "graph/id.hpp"
#include <vector>

namespace project_x {
namespace route {

// A segment of a route is described all information necessary to reconstruct
// the API result of a shortest path query for a single road segment
template <typename weight_type> struct Segment {
  weight_type weight_at_end;
  EdgeID edge_id;
};

// A route consists of multiple edge-segments traversed one by one
template <typename weight_type> struct Route {
  std::vector<Segment<weight_type>> segments;
};

} // namespace route
} // namespace project_x

#endif // PROJECT_X_ROUTE_ROUTE_HPP_
