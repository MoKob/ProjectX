#include "builder/graph.hpp"
#include "graph/decorator_factory.hpp"
#include "graph/forward_star_factory.hpp"

namespace project_x {
namespace builder {

NodeID Graph::to_node_id(std::uint64_t external_id) {
  auto const itr = id_map.find(external_id);
  if (itr == id_map.end()) {
    NodeID new_id = id_map.size();
    id_map.insert(itr, std::make_pair(external_id, new_id));
    return new_id;
  } else {
    return itr->second;
  }
}

void Graph::add_edge(std::uint64_t source, std::uint64_t target,
                     std::string payload) {
  edges.push_back({to_node_id(source), to_node_id(target), std::move(payload)});
}

void Graph::add_weighted_edge(std::uint64_t source, std::uint64_t target,
                              graph::WeightTimeDistance::weight_type weight,
                              graph::WeightTimeDistance::time_type time,
                              graph::WeightTimeDistance::distance_type distance,
                              std::string payload) {

  graph::WeightTimeDistance edge_weight{weight, time, distance};
  weighted_edges.push_back({to_node_id(source), to_node_id(target), edge_weight,
                            std::move(payload)});
}

void Graph::build_graph_and_store(std::string path) {
  io::File out(path,
               io::mode::mWRITE | io::mode::mBINARY | io::mode::mVERSIONED);

  if (!edges.empty()) {
    auto const graph = graph::ForwardStarFactory::produce_directed_from_edges(
        id_map.size(), edges);
    graph.serialise(out);
  } else if (!weighted_edges.empty()) {
    // construct a weight-decorated graph to allow navigation
    graph::RoutingGraph graph =
        graph::ForwardStarFactory::produce_directed_from_edges(id_map.size(),
                                                               weighted_edges);
    graph::DecoratorFactory decorator;

    auto const to_weight = [](WeightedEdge const &edge) { return edge.weight; };

    decorator.decorate(graph, weighted_edges, to_weight);
    graph.serialise(out);
  }
}

} // namespace builder
} // namespace project_x
