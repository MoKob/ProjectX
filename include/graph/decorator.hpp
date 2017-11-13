#ifndef PROJECT_X_GRAPH_DECORATOR_HPP_
#define PROJECT_X_GRAPH_DECORATOR_HPP_

#include "graph/id.hpp"
#include "io/file.hpp"
#include "io/serialisable.hpp"
#include "io/wrappers.hpp"

#include <string>
#include <vector>

// Decorators are a way of adding user data to a forward star graph
// representation that is supposed to be used within navigation / returned from
// the API. A cost type in general is required to allow shortest path
// computation. We allow cost to be templated, so that we can induce different
// structs and can return combinations of weight/distance/time
namespace project_x {
namespace graph {

// forward declaration to put this into the graph, not the graph::edge namespace
class DecoratorFactory;

namespace edge {
template <typename cost_type_t, class graph_type>
class CostDecorator : public graph_type {
public:
  using cost_type = cost_type_t;
  template <class base_graph> CostDecorator(base_graph &&graph);
  CostDecorator() = default;

  cost_type &cost(EdgeID const);
  cost_type const &cost(EdgeID const) const;

  void serialise(io::File &) const;
  void deserialise(io::File &);

  friend DecoratorFactory;

private:
  std::vector<cost_type> decoration;
};

// The data decorator allows to store whatever kind of additional data we want
// to connect with the graphs edges. Data on edges might be connected to street
// names, road types or similar but could also represent the color of a public
// transit line or other types of data.
template <typename data_type_t, class graph_type>
class DataDecorator : public graph_type {
public:
  using data_type = data_type_t;

  template <class base_graph> DataDecorator(base_graph &&graph);
  DataDecorator() = default;

  data_type &data(EdgeID const);
  data_type const &data(EdgeID const) const;

  void serialise(io::File &) const;
  void deserialise(io::File &);

  friend DecoratorFactory;

private:
  std::vector<data_type> decoration;
};

// Byte decorators are used to store arbitrary data on edges that will be
// returned via the API. If you want to encode data that will be part of any
// path in the graph, put it in here. All the contents will be added to the
// resulting path.
template <class graph_type> class ByteDecorator : public graph_type {
public:
  using byte_string = std::string;
  using wrapped_byte_string = io::SerialisableContainer<std::string>;

  template <class base_graph> ByteDecorator(base_graph &&graph);
  ByteDecorator() = default;

  byte_string &bytes(EdgeID const);
  byte_string const &bytes(EdgeID const) const;

  void serialise(io::File &) const;
  void deserialise(io::File &);

  friend DecoratorFactory;

private:
  std::vector<wrapped_byte_string> decoration;
};

//////////////////////////////////////////////////////////////////
// Implementations
//////////////////////////////////////////////////////////////////

template <typename cost_type_t, class graph_type>
template <class base_graph>
CostDecorator<cost_type_t, graph_type>::CostDecorator(base_graph &&graph)
    : graph_type(std::move(graph)) {}

template <typename cost_type_t, class graph_type>
cost_type_t &CostDecorator<cost_type_t, graph_type>::cost(EdgeID const eid) {
  return decoration[eid];
}

template <typename cost_type_t, class graph_type>
cost_type_t const &
CostDecorator<cost_type_t, graph_type>::cost(EdgeID const eid) const {
  return decoration[eid];
}

template <typename cost_type_t, class graph_type>
void CostDecorator<cost_type_t, graph_type>::serialise(io::File &file) const {
  graph_type::serialise(file);
  file.write_container(decoration);
}

template <typename cost_type_t, class graph_type>
void CostDecorator<cost_type_t, graph_type>::deserialise(io::File &file) {
  graph_type::deserialise(file);
  file.read_container(decoration);
}

//////////////////////////////////////////////////////////////////

template <typename data_type_t, class graph_type>
template <class base_graph>
DataDecorator<data_type_t, graph_type>::DataDecorator(base_graph &&graph)
    : graph_type(std::move(graph)) {}

template <typename data_type_t, class graph_type>
data_type_t &DataDecorator<data_type_t, graph_type>::data(EdgeID const eid) {
  return decoration[eid];
}

template <typename data_type_t, class graph_type>
data_type_t const &
DataDecorator<data_type_t, graph_type>::data(EdgeID const eid) const {
  return decoration[eid];
}

template <typename data_type_t, class graph_type>
void DataDecorator<data_type_t, graph_type>::serialise(io::File &file) const {
  graph_type::serialise(file);
  file.write_container(decoration);
}

template <typename data_type_t, class graph_type>
void DataDecorator<data_type_t, graph_type>::deserialise(io::File &file) {
  graph_type::deserialise(file);
  file.read_container(decoration);
}

//////////////////////////////////////////////////////////////////

template <class graph_type>
template <class base_graph>
ByteDecorator<graph_type>::ByteDecorator(base_graph &&graph)
    : graph_type(std::move(graph)) {}

template <class graph_type>
typename ByteDecorator<graph_type>::byte_string &
ByteDecorator<graph_type>::bytes(EdgeID const eid) {
  return decoration[eid].wrapped_object;
}

template <class graph_type>
typename ByteDecorator<graph_type>::byte_string const &
ByteDecorator<graph_type>::bytes(EdgeID const eid) const {
  return decoration[eid].wrapped_object;
}

template <class graph_type>
void ByteDecorator<graph_type>::serialise(io::File &file) const {
  graph_type::serialise(file);
  file.write_container(decoration);
}

template <class graph_type>
void ByteDecorator<graph_type>::deserialise(io::File &file) {
  graph_type::deserialise(file);
  file.read_container(decoration);
}

} // namespace edge
} // namespace graph
} // namespace project_x

#endif // PROJECT_X_GRAPH_DECORATOR_HPP_
