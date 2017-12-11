#ifndef PROJECT_X_BUILDER_GRAPH_HPP_
#define PROJECT_X_BUILDER_GRAPH_HPP_

#include <cstdint>
#include <string>
#include <unordered_map>
#include <vector>

#include "graph/id.hpp"
#include "graph/routing.hpp"

namespace project_x {
namespace builder {

struct Edge {
  NodeID source;
  NodeID target;
  // payload to return
  std::string payload;
};

struct WeightedEdge {
  NodeID source;
  NodeID target;
  graph::WeightTimeDistance weight;
  // payload to return
  std::string payload;
};

class Graph {
public:
  void add_edge(std::uint64_t source, std::uint64_t target,
                std::string payload);

  void add_weighted_edge(std::uint64_t source, std::uint64_t target,
                         graph::WeightTimeDistance::weight_type weight,
                         graph::WeightTimeDistance::time_type time,
                         graph::WeightTimeDistance::distance_type distance,
                         std::string payload);

  void build_graph_and_store(std::string const path);

private:
  // convert a input id into a local graph ID
  NodeID to_node_id(std::uint64_t external_id);

  std::unordered_map<std::uint64_t, NodeID> id_map;
  std::vector<Edge> edges;
  std::vector<WeightedEdge> weighted_edges;
};

} // namespace builder
} // namespace project_x

#endif // PROJECT_X_BUILDER_GRAPH_HPP_
