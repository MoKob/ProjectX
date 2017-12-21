#ifndef PROJECT_X_ALGORITHM_SHORTEST_PATH_INTERFACE_HPP_
#define PROJECT_X_ALGORITHM_SHORTEST_PATH_INTERFACE_HPP_

#include "graph/id.hpp"
#include <vector>

namespace project_x {
namespace algorithm {

// A start/target location for a search
struct Location {
  EdgeID segment;
  std::int32_t offset;
};

// general interface of how shortest path algorithms work
class ShortestPathInterface {
public:
  // a direct path between two locations
  virtual std::vector<EdgeID> operator()(Location const &from,
                                         Location const &to) = 0;
  // in case of multiple possible source/target candidates
  virtual std::vector<EdgeID> operator()(std::vector<Location> const &from,
                                         std::vector<Location> const &to) = 0;
};

} // namespace algorithm
} // namespace project_x

#endif // PROJECT_X_ALGORITHM_SHORTEST_PATH_INTERFACE_HPP_
