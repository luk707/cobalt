cmake_minimum_required(VERSION 3.10)
project(cobalt)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_subdirectory(lib/glb)
add_subdirectory(src/demo)
add_subdirectory(src/glb-info)
