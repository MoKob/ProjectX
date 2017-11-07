set (graph_SOURCES
  forward_star.cpp)

add_library(Xgraph STATIC
  ${graph_SOURCES})

#required libs to build static graph library
target_link_libraries(Xgraph
  ${MAYBE_COVERAGE_LIBRARIES})

#additional includes for graph library
target_include_directories(Xgraph SYSTEM PUBLIC
  )
