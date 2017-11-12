#ifndef PROJECT_X_GRAPH_ID_HPP_
#define PROJECT_X_GRAPH_ID_HPP_

#include <cstdint>

// IDs are kept in the main namespace, since they are used all over the project
namespace project_x {

using NodeID = std::uint64_t;
using EdgeID = std::uint64_t;

} // namespace project_x

#endif // PROJECT_X_GRAPH_ID_HPP_
