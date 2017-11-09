set (io_SOURCES
  "file.cpp")

add_library(Xio STATIC
  ${io_SOURCES})

#required libs to build static graph library
target_link_libraries(Xio
  ${MAYBE_COVERAGE_LIBRARIES})

#additional includes for graph library
target_include_directories(Xio SYSTEM PUBLIC
  )
