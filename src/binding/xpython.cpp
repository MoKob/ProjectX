#include <boost/python/class.hpp>
#include <boost/python/module.hpp>
#include <boost/python/scope.hpp>

#include "builder/graph.hpp"

class ScopeImport {};

BOOST_PYTHON_MODULE(xpython) {
  using namespace boost::python;
  scope import = class_<ScopeImport>("importer");

  class_<project_x::builder::Graph>("GraphBuilder")
      .def("add_edge", &project_x::builder::Graph::add_edge)
      .def("add_weighted_edge", &project_x::builder::Graph::add_edge)
      .def("build_graph_and_store",
           &project_x::builder::Graph::build_graph_and_store);
}
