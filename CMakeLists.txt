cmake_minimum_required(VERSION 3.10)

# Project setup
project(proceduralGeneration)

# Enable exporting compile commands
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Add Program Files (x86) to CMake search paths
list(APPEND CMAKE_PREFIX_PATH "E:\raylib\w64devkit\external")

# Source files
set(SOURCES ./src/main.c)

# Find raylib package
find_package(raylib REQUIRED)

# Add executable
add_executable(plots ${SOURCES})

# Link libraries (raylib handles dependencies automatically)
target_link_libraries(plots PRIVATE ${raylib_LIBRARIES} winmm gdi32 kernel32)

# Include directories
target_include_directories(plots PRIVATE ${raylib_INCLUDE_DIRS})

# Custom target to build and run
add_custom_target(build_and_run
    COMMAND ${CMAKE_COMMAND} --build ${CMAKE_BINARY_DIR} --target plots
    COMMAND plots
    DEPENDS plots
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
)

# Custom target to run only
add_custom_target(run
    COMMAND plots
    DEPENDS plots
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
)
