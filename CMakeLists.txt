cmake_minimum_required(VERSION 3.7)

# Configuration of the version to test files/compatibilities
set(VERSION_MAJOR 0)
set(VERSION_MINOR 0)
set(VERSION_PATCH 0)
set(VERSION_TAG )

# Compilation
add_compile_options(${CMAKE_CXX_FLAGS} -std=c++14)
add_compile_options(${CMAKE_CXX_FLAGS} -fvisibility-inline-hidden)
add_compile_options(${CMAKE_CXX_FLAGS} -W)
add_compile_options(${CMAKE_CXX_FLAGS} -Wall)
add_compile_options(${CMAKE_CXX_FLAGS} -Wextra)
add_compile_options(${CMAKE_CXX_FLAGS} -pedantic)
add_compile_options(${CMAKE_CXX_FLAGS} -Wuninitialized)
add_compile_options(${CMAKE_CXX_FLAGS} -Wreturn-type)
add_compile_options(${CMAKE_CXX_FLAGS} -Wunreachable-code)
add_compile_options(${CMAKE_CXX_FLAGS} -Wstrict-overflow=2)

# General set-up
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/cmake/version.h.in
               ${CMAKE_CURRENT_SOURCE_DIR}/include/version.h)

include_directories("${CMAKE_CURRENT_SOURCE_DIR}/include")

# Sub-Projects
add_subdirectory(src/graph)

enable_testing()
add_subdirectory(test)
