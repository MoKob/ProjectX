set (builder_SOURCES
  "graph.cpp")

add_library(Xbuilder STATIC
  ${builder_SOURCES})

#required libs to build static builder library
target_link_libraries(Xbuilder
  ${MAYBE_COVERAGE_LIBRARIES})

#additional includes for builder library
target_include_directories(Xbuilder SYSTEM PUBLIC
  )
