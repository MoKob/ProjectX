#include <boost/python/class.hpp>
#include <boost/python/module.hpp>
#include <boost/python/scope.hpp>

#include "builder/graph.hpp"

class ScopeImport {};

BOOST_PYTHON_MODULE(xpython) {
  using namespace boost::python;
  scope import = class_<ScopeImport>("import");

  class_<project_x::builder::Graph>("GrapBuilder")
      .def("add_edge", &project_x::builder::Graph::add_edge);
}
