#ifndef PROJECT_X_CONTAINER_HEAP_ELEMENT_HPP_
#define PROJECT_X_CONTAINER_HEAP_ELEMENT_HPP_

#include <tuple>

namespace project_x {
namespace container {
template <typename key_type, typename weight_type> struct HeapElement {
  key_type key;
  weight_type weight;

  bool operator<(HeapElement<key_type, weight_type> const &other) {
    return std::tie(weight, key) < std::tie(other.weight, other.key);
  }
  bool operator>(HeapElement<key_type, weight_type> const &other) {
    return std::tie(weight, key) > std::tie(other.weight, other.key);
  }
};
} // namespace container
} // namespace project_x

#endif // PROJECT_X_CONTAINER_HEAP_ELEMENT_HPP_
