find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

find_package(Vulkan REQUIRED)
include_directories(${Vulkan_INCLUDE_DIRS})

add_executable(cobalt-demo main.cc app.cc)

# Unified keyword-style linking
target_link_libraries(cobalt-demo
    PRIVATE
    ${SDL2_LIBRARIES}
    ${Vulkan_LIBRARIES}
)

if(APPLE)
    message(STATUS "Linking MoltenVK on macOS")

    # Link MoltenVK manually from Homebrew
    find_library(MOLTENVK_LIB MoltenVK PATHS /opt/homebrew/lib REQUIRED)
    target_link_libraries(cobalt-demo PRIVATE ${MOLTENVK_LIB})

    # Set RPATH so it can find libMoltenVK.dylib at runtime
    set_target_properties(cobalt-demo PROPERTIES
        INSTALL_RPATH "/opt/homebrew/lib"
    )
endif()