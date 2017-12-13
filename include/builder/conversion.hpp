#ifndef PROJECT_X_BUILDER_CONVERSION_HPP_
#define PROJECT_X_BUILDER_CONVERSION_HPP_

#include "graph/routing.hpp"
#include <tuple>

namespace project_x {
namespace builder {
namespace decoration {

template <typename edge_type, typename decoration_type>
typename std::enable_if<
    std::is_same<decoration_type, graph::WeightTimeDistance>::value,
    graph::WeightTimeDistance>::type
convert(edge_type const &edge) {
  static_assert(std::tuple_size<decltype(edge.data)>::value >= 3,
                "Conversion requires at least three data members.");
  return {std::get<0>(edge.data), std::get<1>(edge.data),
          std::get<2>(edge.data)};
}

} // namespace decoration
} // namespace builder
} // namespace project_x

#endif // PROJECT_X_BUILDER_CONVERSION_HPP_
