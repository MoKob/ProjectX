#ifndef PROJECT_X_BUILDER_GRAPH_HPP_
#define PROJECT_X_BUILDER_GRAPH_HPP_

#include <cstdint>
#include <string>
#include <tuple>
#include <unordered_map>
#include <utility>
#include <vector>

#include "builder/conversion.hpp"
#include "graph/decorator.hpp"
#include "graph/decorator_factory.hpp"
#include "graph/forward_star_factory.hpp"
#include "graph/id.hpp"
#include "io/file.hpp"

namespace project_x {
namespace builder {

template <typename... Types> struct Edge {
  Edge(NodeID source, NodeID target, Types &&... data)
      : source(source), target(target), data(std::forward<Types>(data)...) {}

  NodeID source;
  NodeID target;

  // the data will contain the cost (one to n elements) and a possible string
  // payload, to encode json objects, pbf buffers or similar
  std::tuple<Types...> data;
};

template <typename Edge> class Graph {
public:
  template <typename... Types>
  void add_edge(std::uint64_t source, std::uint64_t target, Types &&... data);
  void build_graph_and_store(std::string const path);

  template <typename weight_type>
  void build_weighted_graph_and_store(std::string const path);

private:
  std::unordered_map<std::uint64_t, std::uint64_t> id_map;
  std::vector<Edge> edges;
};

template <typename Edge>
template <typename... Types>
void Graph<Edge>::add_edge(std::uint64_t source, std::uint64_t target,
                           Types &&... data) {
  auto const to_node_id = [this](auto const external_id) {
    auto const itr = id_map.find(external_id);
    if (itr == id_map.end()) {
      std::uint64_t new_id = id_map.size();
      id_map.insert(itr, std::make_pair(external_id, new_id));
      return new_id;
    } else {
      return itr->second;
    }
  };

  auto mapped_source = to_node_id(source);
  auto mapped_target = to_node_id(target);
  edges.push_back(
      Edge(mapped_source, mapped_target, std::forward<Types>(data)...));
}

template <typename Edge>
void Graph<Edge>::build_graph_and_store(std::string path) {
  auto const graph = graph::ForwardStarFactory::produce_directed_from_edges(
      id_map.size(), edges);

  io::File out(path,
               io::mode::mWRITE | io::mode::mBINARY | io::mode::mVERSIONED);
  graph.serialise(out);
}

template <typename Edge>
template <typename WeightType>
void Graph<Edge>::build_weighted_graph_and_store(std::string const path) {
  using WeightedGraph =
      graph::edge::CostDecorator<WeightType, graph::ForwardStar>;

  WeightedGraph graph(graph::ForwardStarFactory::produce_directed_from_edges(
      id_map.size(), edges));

  graph::DecoratorFactory decorator_factory;
  decorator_factory.decorate(graph, edges,
                             builder::decoration::convert<Edge, WeightType>);

  io::File out(path,
               io::mode::mWRITE | io::mode::mBINARY | io::mode::mVERSIONED);
  graph.serialise(out);
}

} // namespace builder
} // namespace project_x

#endif // PROJECT_X_BUILDER_GRAPH_HPP_
