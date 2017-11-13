#include "graph/routing.hpp"

#include <tuple>

namespace project_x {
namespace graph {

bool WeightTimeDistance::operator<(WeightTimeDistance const &other) const {
  return std::tie(weight, time, distance) <
         std::tie(other.weight, other.time, other.distance);
}

bool WeightTimeDistance::operator<=(WeightTimeDistance const &other) const {
  return std::tie(weight, time, distance) <=
         std::tie(other.weight, other.time, other.distance);
}

bool WeightTimeDistance::operator>(WeightTimeDistance const &other) const {
  return std::tie(weight, time, distance) >
         std::tie(other.weight, other.time, other.distance);
}

bool WeightTimeDistance::operator>=(WeightTimeDistance const &other) const {
  return std::tie(weight, time, distance) >=
         std::tie(other.weight, other.time, other.distance);
}

bool WeightTimeDistance::operator==(WeightTimeDistance const &other) const {
  return std::tie(weight, time, distance) ==
         std::tie(other.weight, other.time, other.distance);
}

bool WeightTimeDistance::operator!=(WeightTimeDistance const &other) const {
  return std::tie(weight, time, distance) !=
         std::tie(other.weight, other.time, other.distance);
}

WeightTimeDistance WeightTimeDistance::
operator+=(WeightTimeDistance const &other) {
  weight += other.weight;
  time += other.time;
  distance += other.distance;
  return *this;
}

WeightTimeDistance WeightTimeDistance::
operator+(WeightTimeDistance const &other) const {
  auto copy = *this;
  copy += other;
  return copy;
}

WeightTimeDistance WeightTimeDistance::
operator-=(WeightTimeDistance const &other) {
  weight -= other.weight;
  time -= other.time;
  distance -= other.distance;
  return *this;
}

WeightTimeDistance WeightTimeDistance::
operator-(WeightTimeDistance const &other) const {
  auto copy = *this;
  copy -= other;
  return copy;
}

} // namespace graph
} // namespace project_x
