#ifndef PROJECT_X_BUILDER_GRAPH_HPP_
#define PROJECT_X_BUILDER_GRAPH_HPP_

#include <cstdint>
#include <string>
#include <unordered_map>
#include <vector>

#include "graph/id.hpp"

namespace project_x {
namespace builder {

struct Edge {
  NodeID source;
  NodeID target;
  // payload to return
  std::string payload;
};

class Graph {
public:
  void add_edge(std::uint64_t source, std::uint64_t target,
                std::string payload);
  void build_graph_and_store(std::string const path);

private:
  std::unordered_map<std::uint64_t, std::uint64_t> id_map;
  std::vector<Edge> edges;
};

} // namespace builder
} // namespace project_x

#endif // PROJECT_X_BUILDER_GRAPH_HPP_
