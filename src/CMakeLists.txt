cmake_minimum_required(VERSION 2.8.0)
include_directories(.)

# EXECUTABLE DEFINITION
add_executable(GameEngine main.cpp)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/GameEngine/${CMAKE_BUILD_TYPE})

add_definitions(-Wall -g -msse3)
target_link_libraries(GameEngine rt GL GLU GLEW glut AntTweakBar)
