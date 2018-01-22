#ifndef PROJECT_X_ALGORITHM_UNION_FIND_HPP_
#define PROJECT_X_ALGORITHM_UNION_FIND_HPP_

#include <cstdint>
#include <vector>

namespace project_x {
namespace algorithm {
// implementaiton of the classic union-find algorithm, allowing combination of
// entries into groups and finding representatives of these groups
class UnionFind {
public:
  UnionFind(std::uint64_t const universe_size);

  // combine two groups into a single one
  void unite(std::uint64_t const lhs, std::uint64_t const rhs);

  // find the representative of a group
  std::uint64_t find(std::uint64_t rep);

private:
  std::vector<std::int64_t> reps;
};
} // namespace algorithm
} // namespace project_x

#endif // PROJECT_X_ALGORITHM_UNION_FIND_HPP_
