#ifndef PROJECT_X_GRAPH_ROUTING_HPP_
#define PROJECT_X_GRAPH_ROUTING_HPP_

#include "decorator.hpp"
#include "forward_star.hpp"

#include <cstdint>

namespace project_x {
namespace graph {

struct WeightTimeDistance {
  using weight_type = std::uint32_t;
  using time_type = std::uint32_t;
  using distance_type = std::uint32_t;

  weight_type weight;
  time_type time;
  distance_type distance;

  bool operator<(WeightTimeDistance const &other) const;
  bool operator<=(WeightTimeDistance const &other) const;
  bool operator>(WeightTimeDistance const &other) const;
  bool operator>=(WeightTimeDistance const &other) const;
  bool operator==(WeightTimeDistance const &other) const;
  bool operator!=(WeightTimeDistance const &other) const;

  WeightTimeDistance operator+(WeightTimeDistance const &other) const;
  WeightTimeDistance operator+=(WeightTimeDistance const &other);
  WeightTimeDistance operator-(WeightTimeDistance const &other) const;
  WeightTimeDistance operator-=(WeightTimeDistance const &other);
};

// The routing graph
using RoutingGraph = edge::CostDecorator<WeightTimeDistance, ForwardStar>;

} // namespace graph
} // namespace project_x

#endif // PROJECT_X_GRAPH_ROUTING_HPP_
