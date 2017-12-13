#include <boost/python/class.hpp>
#include <boost/python/module.hpp>
#include <boost/python/scope.hpp>

#include "builder/graph.hpp"
#include "graph/routing.hpp"

#include <string>
#include <utility>

class ScopeImport {};

using namespace project_x;

// Adapter class to handle variadic template on graph side
class BasicGraph : public builder::Graph<builder::Edge<std::string>> {
  using Base = builder::Graph<builder::Edge<std::string>>;

public:
  void add_edge(std::uint64_t source, std::uint64_t target, std::string str) {
    Base::add_edge(source, target, std::move(str));
  }
};

using WeightedEdge =
    builder::Edge<graph::WeightTimeDistance::weight_type,
                  graph::WeightTimeDistance::time_type,
                  graph::WeightTimeDistance::distance_type, std::string>;
class WeightTimeDistanceGraph : public builder::Graph<WeightedEdge> {
  using Base = builder::Graph<WeightedEdge>;

public:
  void add_edge(std::uint64_t source, std::uint64_t target,
                graph::WeightTimeDistance::weight_type weight,
                graph::WeightTimeDistance::time_type time,
                graph::WeightTimeDistance::distance_type distance,
                std::string str) {
    Base::add_edge(source, target, std::move(weight), std::move(time),
                   std::move(distance), std::move(str));
  }

  void build_weighted_graph_and_store(std::string const path) {
    Base::build_weighted_graph_and_store<graph::WeightTimeDistance>(path);
  }
};

BOOST_PYTHON_MODULE(xpython) {
  using namespace boost::python;
  scope import = class_<ScopeImport>("importer");

  class_<BasicGraph>("BasicGraphBuilder")
      .def("add_edge", &BasicGraph::add_edge)
      .def("build_graph_and_store", &BasicGraph::build_graph_and_store);

  class_<WeightTimeDistanceGraph>("WeightTimeDistanceGraph")
      .def("add_edge", &WeightTimeDistanceGraph::add_edge)
      .def("build_weighted_graph_and_store",
           &WeightTimeDistanceGraph::build_graph_and_store);
}
