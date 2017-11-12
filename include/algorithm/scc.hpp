#ifndef PROJECT_X_ALGORITHM_SCC_HPP_
#define PROJECT_X_ALGORITHM_SCC_HPP_

#include <cstdint>
#include <vector>

namespace project_x {

namespace graph {
class ForwardStar;
} // namespace graph

namespace algorithm {
// implementation of Tarjans algorithm for the computation of Strongly Connected
// Components (SCC). For every node of the graph, in order, the result will
// contain the ID of the component the node belongs to
class SCC {
public:
  // requires O(N+M) time on G=(V,E), N = |V|, M = |E|
  // Additional space in the order of O(N)
  // Components are numbered from 0 to N-1 (inclusive)
  static std::vector<std::uint64_t> compute(graph::ForwardStar const &graph);
};

} // namespace algorithm
} // namespace project_x

#endif // PROJECT_X_ALGORITHM_SCC_HPP_
