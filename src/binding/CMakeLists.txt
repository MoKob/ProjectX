set (Python_SOURCES
  "xpython.cpp")

add_compile_options(${CMAKE_CXX_FLAGS} -lboost_python)

add_library(xpython SHARED
  ${Python_SOURCES})

#required libs to build static Python library
target_link_libraries(xpython
  Xbuilder
  Xgraph
  Xlogging
  Xio
  ${MAYBE_COVERAGE_LIBRARIES}
  ${Boost_LIBRARIES})

#get rid of the `lib` prefix
set_target_properties(xpython PROPERTIES PREFIX "")

#additional includes for Python library
target_include_directories(xpython SYSTEM PUBLIC
  )
