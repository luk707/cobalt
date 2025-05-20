include(FetchContent)

# Fetch CLI11
FetchContent_Declare(
  CLI11
  GIT_REPOSITORY https://github.com/CLIUtils/CLI11.git
  GIT_TAG        v2.5.0
)

FetchContent_MakeAvailable(CLI11)

add_executable(glb-info main.cc)

target_link_libraries(glb-info PRIVATE CLI11::CLI11 glb)
