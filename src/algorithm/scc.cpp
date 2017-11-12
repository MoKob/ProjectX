#include "algorithm/scc.hpp"
#include "graph/forward_star.hpp"
#include "graph/id.hpp"
#include "log/logger.hpp"

#include <limits>
#include <stack>
#include <unordered_set>

#include <iostream>

namespace project_x {
namespace algorithm {

namespace details {

// the state required to identify nodes in Tarjans algorithm. The dfs_index
// identifies the depth (including previous trees) of the node in the search.
// Low_link is the lowest ID which is linked to the node
struct NodeState {
  NodeState(
      std::uint64_t const depth = std::numeric_limits<std::uint64_t>::max(),
      std::uint64_t const low_link = std::numeric_limits<std::uint64_t>::max(),
      bool on_stack = false)
      : depth(depth), low_link(low_link), on_stack(on_stack) {}

  // check if a node has been seen in the DFS so far
  bool seen() const {
    return depth != std::numeric_limits<std::uint64_t>::max();
  }

  // check if a node is a representative of an SCC
  bool is_scc_root() const { return depth == low_link; }

  std::uint64_t depth;
  std::uint64_t low_link;
  bool on_stack;
};

// assign a component ID to all elements on the component stack until we reach
// the root of the component
void assign_scc(std::vector<std::uint64_t> &components,
                std::stack<NodeID> &component_nodes,
                NodeID const component_root, std::uint64_t component_id) {
  while (component_nodes.top() != component_root) {
    components[component_nodes.top()] = component_id;
    component_nodes.pop();
  }
  components[component_root] = component_id;
  component_nodes.pop();
}

// every component is represented by the node seen first in a dfs stack. All
// other nodes in the component, due to it being an SCC have a connection lower
// in the DFS tree to it. We mark the nodes via low_link, which is the lowest
// number we can see over all nodes in the current DFS search. We only need to
// take care to avoid updating low_link on cross edges, that might point into a
// different part of the graph.
void scc(graph::ForwardStar const &graph, std::vector<NodeState> &node_states,
         std::vector<std::uint64_t> &components,
         std::uint64_t &num_components_assigned, std::uint64_t &depth,
         std::uint64_t const root) {
  struct Stackframe {
    NodeID node;
    graph::ForwardStar::const_edge_iterator next_edge;
  };
  std::stack<Stackframe> dfs_stack;
  std::stack<NodeID> component_nodes;

  component_nodes.push(root);
  dfs_stack.push({root, graph.edges_begin(root)});
  node_states[root].on_stack = true;
  node_states[root].depth = node_states[root].low_link = depth++;

  while (!dfs_stack.empty()) {
    // operating on the current frame, we directly update the respective
    // iterators without needing to push/pop
    auto &current_frame = dfs_stack.top();
    // continue on the same node
    if (current_frame.next_edge != graph.edges_end(current_frame.node)) {
      auto const neighbor = *current_frame.next_edge++;
      if (!node_states[neighbor].seen()) {
        // down edge
        node_states[neighbor].on_stack = true;
        node_states[neighbor].depth = node_states[neighbor].low_link = depth++;
        dfs_stack.push({neighbor, graph.edges_begin(neighbor)});
        component_nodes.push(neighbor);
      } else if (node_states[neighbor].on_stack) {
        // back edge
        node_states[current_frame.node].low_link =
            std::min(node_states[current_frame.node].low_link,
                     node_states[neighbor].depth);
      }
      // if an edge is both seen and not on the stack, it is a cross edge into a
      // different component
    } else {
      // backtracking, we have seen all neighbors of the current node
      if (node_states[current_frame.node].is_scc_root()) {
        assign_scc(components, component_nodes, current_frame.node,
                   num_components_assigned++);
      }
      // update the parents dfs_index
      // the parent node of the current node has pushed this node onto the
      // stack. After returning, it would update it's own low-link. However,
      // since that update is not happening after the push, as it would in a
      // normal recursion, we simply update our parents low_link here
      auto low = node_states[current_frame.node].low_link;
      node_states[current_frame.node].on_stack = false;
      dfs_stack.pop();
      // not the root of the search
      if (!dfs_stack.empty()) {
        node_states[dfs_stack.top().node].low_link =
            std::min(node_states[dfs_stack.top().node].low_link, low);
      }
    }
  }
}

} // namespace details

std::vector<std::uint64_t> SCC::compute(graph::ForwardStar const &graph) {
  auto const unset_component_id = std::numeric_limits<std::uint64_t>::max();
  std::vector<std::uint64_t> components(graph.number_of_nodes(),
                                        unset_component_id);

  // tracking the IDs of next components / the depth of the dfs
  std::uint64_t num_components_assigned = 0;
  std::uint64_t depth = 0;

  std::vector<details::NodeState> node_states(graph.number_of_nodes());

  // start a DFS based SCC search at every node that has no valid component id
  for (NodeID node_id = 0; node_id < graph.number_of_nodes(); ++node_id) {
    if (components[node_id] == unset_component_id) {
      details::scc(graph, node_states, components, num_components_assigned,
                   depth, node_id);
    }
  }

  log::Logger logger;
  logger.message(log::Level::INFO,
                 "Graph contains " + std::to_string(num_components_assigned) +
                     " connected components.");

  return components;
}
} // namespace algorithm
} // namespace project_x
