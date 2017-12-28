#include "algorithm/union_find.hpp"

#include <algorithm>

namespace project_x {
namespace algorithm {

UnionFind::UnionFind(std::uint64_t const universe_size)
    : reps(universe_size, -1) {}

void UnionFind::unite(std::uint64_t const lhs, std::uint64_t const rhs) {
  // union by size
  auto const lhs_rep = find(lhs);
  auto const rhs_rep = find(rhs);

  if (lhs_rep == rhs_rep)
    return;

  auto const lhs_size = std::abs(reps[lhs_rep]);
  auto const rhs_size = std::abs(reps[rhs_rep]);

  if (lhs_size < rhs_size) {
    reps[lhs_rep] -= rhs_size;
    reps[rhs_rep] = lhs_rep;
  } else {
    reps[rhs_rep] -= lhs_size;
    reps[lhs_rep] = rhs_rep;
  }
}

// find the representative of a group
std::uint64_t UnionFind::find(std::uint64_t rep) {
  if (reps[rep] < 0)
    return rep;
  else {
    // path compression
    reps[rep] = find(reps[rep]);
    return reps[rep];
  }
}

} // namespace algorithm
} // namespace project_x
