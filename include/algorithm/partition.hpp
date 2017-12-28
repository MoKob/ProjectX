#ifndef PROJECT_X_ALGORITHM_PARTITION_HPP_
#define PROJECT_X_ALGORITHM_PARTITION_HPP_

#include "graph/forward_star.hpp"

#include <cstdint>
#include <vector>

namespace project_x {
namespace algorithm {

// recursive bisection of a forward star graph, following a fixed balance
// constraint for cells
class Partition {
public:
  using PartitionID = std::uint64_t;

  Partition(ForwardStar const &graph, std::uint32_t const max_cell_size);

private:
  // compute a set of base-cells
  std::vector<PartitionID> compute_cells(std::uint32_t const max_cell_size);

  graph::ForwardStar const &graph;
};

} // namespace algorithm
} // namespace project_x

#endif // PROJECT_X_ALGORITHM_PARTITION_HPP_
