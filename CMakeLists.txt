cmake_minimum_required(VERSION 3.10)
project(cobalt)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include(FetchContent)

# Fetch CLI11
FetchContent_Declare(
  CLI11
  GIT_REPOSITORY https://github.com/CLIUtils/CLI11.git
  GIT_TAG        v2.5.0
)

FetchContent_MakeAvailable(CLI11)

add_executable(glb-info src/glb-info/main.cc)
target_link_libraries(glb-info PRIVATE CLI11::CLI11)
