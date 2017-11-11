cmake_minimum_required(VERSION 3.7)

project(X)

# Configuration of the version to test files/compatibilities
set(VERSION_MAJOR 0)
set(VERSION_MINOR 0)
set(VERSION_PATCH 0)
set(VERSION_TAG )

option(COVERAGE "Link coverage libraries and generate code coverage data" OFF)
option(SANITIZE "Enable adress sanitizer" OFF)

# Compilation
add_compile_options(${CMAKE_CXX_FLAGS} -std=c++14)
add_compile_options(${CMAKE_CXX_FLAGS} -fvisibility-inlines-hidden)
add_compile_options(${CMAKE_CXX_FLAGS} -W)
add_compile_options(${CMAKE_CXX_FLAGS} -Wall)
add_compile_options(${CMAKE_CXX_FLAGS} -Wextra)
add_compile_options(${CMAKE_CXX_FLAGS} -pedantic)
add_compile_options(${CMAKE_CXX_FLAGS} -Wuninitialized)
add_compile_options(${CMAKE_CXX_FLAGS} -Wreturn-type)
add_compile_options(${CMAKE_CXX_FLAGS} -Wunreachable-code)
add_compile_options(${CMAKE_CXX_FLAGS} -Wstrict-overflow=2)

# General set-up
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/cmake/version.in
               ${CMAKE_CURRENT_SOURCE_DIR}/include/version.h)

include_directories("${PROJECT_SOURCE_DIR}/include")

set(BOOST_COMPONENTS unit_test_framework system filesystem)
find_package (Boost 1.54 COMPONENTS REQUIRED ${BOOST_COMPONENTS})

if(COVERAGE)
  if(${CMAKE_BUILD_TYPE} MATCHES "Debug")
    set(MAYBE_COVERAGE_LIBRARIES "-lgcov")
    add_compile_options(${CMAKE_CXX_FLAGS} -ftest-coverage)
    add_compile_options(${CMAKE_CXX_FLAGS} -fprofile-arcs)
  else()
    message(FATAL_ERROR "Configuration unreasonable: coverage requires debug mode.")
  endif()
endif()

if(SANITIZE)
    add_compile_options(${CMAKE_CXX_FLAGS} -fsanitize=address)
    link_libraries(${CMAKE_EXE_LINKER_FLAGS} -fsanitize=address)
endif()

# Sub-Projects
add_subdirectory(src/graph)
add_subdirectory(src/log)
add_subdirectory(src/io)

enable_testing()
add_subdirectory(test)
