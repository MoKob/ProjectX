set (geometry_SOURCES
  "projection.cpp")

add_library(Xgeometry STATIC
  ${geometry_SOURCES})

#required libs to build static geometry library
target_link_libraries(Xgeometry
  ${MAYBE_COVERAGE_LIBRARIES})

#additional includes for geometry library
target_include_directories(Xgeometry SYSTEM PUBLIC
  )
