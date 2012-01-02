cmake_minimum_required(VERSION 2.8.0)
project("GameEngine")

if(NOT CMAKE_BUILD_TYPE)
set (CMAKE_BUILD_TYPE Debug)
endif(NOT CMAKE_BUILD_TYPE)

# LINUX (SETTING VARIABLES)
IF(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
set(CMAKE_CXX_FLAGS "-Wall -Wextra -Werror -g -msse3") # gcc/g++ flags
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/lib/linux/AntTweakBar/include/) # include directories
link_directories(${CMAKE_CURRENT_SOURCE_DIR}/lib/linux/AntTweakBar/lib) # additional library directories
ENDIF(${CMAKE_SYSTEM_NAME} MATCHES "Linux")

# WINDOWS (SETTING VARIABLES)
IF(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
ENDIF(${CMAKE_SYSTEM_NAME} MATCHES "Windows")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/${PROJECT_NAME}/${CMAKE_BUILD_TYPE}")

add_subdirectory(src)
add_subdirectory(Data)
