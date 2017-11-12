set (algorithm_SOURCES
  "scc.cpp")

add_library(Xalgorithm STATIC
  ${algorithm_SOURCES})

#required libs to build static algorithm library
target_link_libraries(Xalgorithm
  ${MAYBE_COVERAGE_LIBRARIES})

#additional includes for algorithm library
target_include_directories(Xalgorithm SYSTEM PUBLIC
  )
