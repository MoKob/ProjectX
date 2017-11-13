#ifndef PROJECT_X_GRAPH_DECORATOR_FACTORY_HPP_
#define PROJECT_X_GRAPH_DECORATOR_FACTORY_HPP_

#include "decorator.hpp"
#include "forward_star.hpp"

namespace project_x {
namespace graph {
class DecoratorFactory {
public:
  template <typename decorated_graph_type, typename edge_container,
            typename converter>
  void decorate(decorated_graph_type &graph, edge_container &edges,
                converter cvt) const;
};

template <typename decorated_graph_type, typename edge_container,
          typename converter>
void DecoratorFactory::decorate(decorated_graph_type &graph,
                                edge_container &edges, converter cvt) const {
  graph.decoration.reserve(edges.size());
  for (auto const &edge : edges) {
    graph.decoration.push_back(cvt(edge));
  }
}

} // namespace graph
} // namespace project_x

#endif // PROJECT_X_GRAPH_DECORATOR_FACTORY_HPP_
