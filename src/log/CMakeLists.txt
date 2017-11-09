set (logging_SOURCES
  logger.cpp)

add_library(Xlogging STATIC
  ${logging_SOURCES})

#required libs to build static logging library
target_link_libraries(Xlogging
  ${MAYBE_COVERAGE_LIBRARIES})

#additional includes for logging library
target_include_directories(Xlogging SYSTEM PUBLIC
  )
