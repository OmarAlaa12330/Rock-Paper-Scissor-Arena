# This CMakeLists.txt includes configurations adapted from Raylib's CMake setup
# Source: https://github.com/raysan5/raylib/blob/5767c4cd059e07355ae5588966d0aee97038a86b/CMakeLists.txt


cmake_minimum_required(VERSION 3.11) # FetchContent is available in 3.11+
project(rock-paper-scissors-arena)

# Generate compile_commands.json
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Header files here
set(HEADER_FILES
        include/TextureManager.hpp
        include/config.hpp
)

# Source files here
set(SOURCE_FILES
        src/TextureManager.cpp
)

# Collect all source files recursively from the /src directory
file(GLOB_RECURSE SOURCE_FILES "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")

# Dependencies
set(RAYLIB_VERSION 5.0)
find_package(raylib ${RAYLIB_VERSION} QUIET) # QUIET or REQUIRED
if (NOT raylib_FOUND)
    include(FetchContent)
    FetchContent_Declare(
            raylib
            DOWNLOAD_EXTRACT_TIMESTAMP OFF
            URL https://github.com/raysan5/raylib/archive/refs/tags/${RAYLIB_VERSION}.tar.gz
    )
    FetchContent_GetProperties(raylib)
    if (NOT raylib_POPULATED)
        set(FETCHCONTENT_QUIET NO)
        FetchContent_Populate(raylib)
        set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE) # don't build the supplied examples
        add_subdirectory(${raylib_SOURCE_DIR} ${raylib_BINARY_DIR})
    endif()
endif()

# Copy assets to the build directory during the configuration stage
file(COPY ${CMAKE_SOURCE_DIR}/assets DESTINATION ${CMAKE_BINARY_DIR})

# Create the executable from the source files
add_executable(${PROJECT_NAME} main.cpp ${SOURCE_FILES} ${HEADER_FILES})
target_link_libraries(${PROJECT_NAME} raylib)
