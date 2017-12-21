#ifndef PROJECT_X_ALGORITHM_DIJKSTRA_HPP_
#define PROJECT_X_ALGORITHM_DIJKSTRA_HPP_

#include "algorithm/shortest_path_interface.hpp"
#include "container/kary_heap.hpp"
#include "route/route.hpp"

#include <algorithm>
#include <unordered_map>
#include <vector>

namespace project_x {
namespace algorithm {
template <typename graph_type>
class Dijkstra : public ShortestPathInterface<graph_type> {
public:
  using weight_type = typename graph_type::cost_type;
  using location_type = Location<weight_type>;

  Dijkstra(graph_type const &graph);

  // a direct path between two locations
  route::Route<weight_type> operator()(location_type const &from,
                                       location_type const &to) override final;

  // in case of multiple possible source/target candidates
  route::Route<weight_type>
  operator()(std::vector<location_type> const &from,
             std::vector<location_type> const &to) override final;

private:
  // perform a step of dijkstras algorithm
  void relax();
  route::Route<weight_type> extract_path(NodeID) const;

  graph_type const &graph;
  // binary heap, storing cost
  container::KAryHeap<NodeID, typename graph_type::cost_type, 2> heap;

  struct ParentData {
    NodeID parent_node;
    EdgeID via_edge;
  };
  // parents of nodes
  std::unordered_map<NodeID, ParentData> parent_ptrs;
};

template <typename graph_type>
Dijkstra<graph_type>::Dijkstra(graph_type const &graph) : graph(graph) {}

template <typename graph_type>
route::Route<typename graph_type::cost_type> Dijkstra<graph_type>::
operator()(location_type const &from, location_type const &to) {
  parent_ptrs.clear();
  heap.clear();

  heap.push(from.node, from.offset);

  while (!heap.empty()) {
    if (heap.peek().key == to.node)
      return extract_path(to.node);
    relax();
  }

  // no valid path
  return {};
}

template <typename graph_type>
route::Route<typename graph_type::cost_type> Dijkstra<graph_type>::
operator()(std::vector<location_type> const &from,
           std::vector<location_type> const &to) {
  parent_ptrs.clear();
  heap.clear();

  std::for_each(from.begin(), from.end(),
                [this](auto const &src) { heap.push(src.node, src.offset); });

  // we cannot stop when we reach a destination. We have to continue until no
  // offset of another target can yield a better route
  auto min_offset = std::min_element(to.begin(), to.end(), [](auto const &lhs,
                                                              auto const &rhs) {
                      return lhs.offset < rhs.offset;
                    })->offset;

  std::optional<NodeID> best_target;
  weight_type best_weight;

  while (!heap.empty()) {
    auto current_minimum = heap.peek();
    // compute a potential new best location
    std::for_each(to.begin(), to.end(),
                  [&best_target, &best_weight, current_minimum](auto location) {
                    if (current_minimum.key == location.node &&
                        (!best_target || location.offset < best_weight)) {
                      best_target = location.node;
                      best_weight = location.offset;
                    }
                  });

    if (best_target && best_weight + min_offset <= current_minimum.weight)
      return extract_path(*best_target);
    relax();
  }

  // no target,
  return {};
}

template <typename graph_type> void Dijkstra<graph_type>::relax() {
  auto const min_heap = heap.pop();
  auto const location = min_heap.key;
  auto const weight = min_heap.weight;

  auto itr = graph.edges_begin(location);
  auto eid = graph.edge_id(itr);
  auto const end_id = graph.edge_id(graph.edges_end(location));
  while (eid != end_id) {
    auto const target = *itr;
    auto const cost = weight + graph.cost(eid);
    auto const entry = heap.entry(target);
    // if the heap does not contain an entry, we add it
    if (!entry) {
      heap.push(target, cost);
      parent_ptrs[target] = {location, eid};
      // else if the entry is strictly larger, we found an improvement
    } else if (entry->weight > cost) {
      parent_ptrs[target] = {location, eid};
      heap.update(target, cost);
    }
    ++eid;
    ++itr;
  }
}

template <typename graph_type>
route::Route<typename graph_type::cost_type>
Dijkstra<graph_type>::extract_path(NodeID destination) const {
  route::Route<weight_type> route;

  auto itr = parent_ptrs.find(destination);
  while (itr != parent_ptrs.end()) {
    route.segments.push_back(
        {heap.entry(destination)->weight, itr->second.via_edge});
    destination = itr->second.parent_node;
    itr = parent_ptrs.find(destination);
  }

  std::reverse(route.segments.begin(), route.segments.end());
  return route;
}

} // namespace algorithm
} // namespace project_x

#endif // PROJECT_X_ALGORITHM_DIJKSTRA_HPP_
