#include "builder/graph.hpp"
#include "graph/forward_star_factory.hpp"

namespace project_x {
namespace builder {

void Graph::add_edge(std::uint64_t source, std::uint64_t target,
                     std::string payload) {
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

  edges.push_back({to_node_id(source), to_node_id(target), std::move(payload)});
}

void Graph::build_graph_and_store(std::string path) {
  auto const graph = graph::ForwardStarFactory::produce_directed_from_edges(
      id_map.size(), edges);

  io::File out(path,
               io::mode::mWRITE | io::mode::mBINARY | io::mode::mVERSIONED);
  graph.serialise(out);
}

} // namespace builder
} // namespace project_x
