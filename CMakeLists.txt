cmake_minimum_required(VERSION 2.8.0)
project("GameEngine")

# Debug or Release only
IF((NOT CMAKE_BUILD_TYPE) OR (NOT(CMAKE_BUILD_TYPE MATCHES Debug OR CMAKE_BUILD_TYPE MATCHES Release)))
set (CMAKE_BUILD_TYPE Debug)
ENDIF((NOT CMAKE_BUILD_TYPE) OR (NOT(CMAKE_BUILD_TYPE MATCHES Debug OR CMAKE_BUILD_TYPE MATCHES Release)))

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/${PROJECT_NAME}/${CMAKE_BUILD_TYPE}")

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/lib/noplatform/rapidxml-1.13/)

# LINUX (SETTING VARIABLES)
IF(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
set(CMAKE_CXX_FLAGS "-Wall -Wextra -Werror -msse3") # gcc/g++ flags (Highest warning level, warnings as errors, Debug build)

IF(${CMAKE_BUILD_TYPE} MATCHES Debug)
add_definitions(-D_DEBUG)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")
ENDIF(${CMAKE_BUILD_TYPE} MATCHES Debug)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/lib/linux/AntTweakBar/include/) # include directories
link_directories(${CMAKE_CURRENT_SOURCE_DIR}/lib/linux/AntTweakBar/lib) # additional library directories
ENDIF(${CMAKE_SYSTEM_NAME} MATCHES "Linux")

# WINDOWS (SETTING VARIABLES)
IF(${CMAKE_SYSTEM_NAME} MATCHES "Windows")

set(CMAKE_CXX_FLAGS "/W4 /WX /EHsc /MP") # visual studio flags (Warning Level 4, Warnings as errors)
add_definitions(-D_CRT_SECURE_NO_WARNINGS)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/lib/win32/freeglut260/ ${CMAKE_CURRENT_SOURCE_DIR}/lib/win32/AntTweakBar/include/)
link_directories(${CMAKE_CURRENT_SOURCE_DIR}/lib/win32/AntTweakBar/lib ${CMAKE_CURRENT_SOURCE_DIR}/lib/win32/freeglut260/${CMAKE_BUILD_TYPE})

# Debug libs (Debug)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/lib/win32/freeglut260/Debug/freeglut.dll ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/../Debug/freeglut.dll COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/lib/win32/freeglut260/Debug/glew32.dll ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/../Debug/glew32.dll COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/lib/win32/AntTweakBar/lib/AntTweakBar.dll ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/../Debug/AntTweakBar.dll COPYONLY)

# Release libs (Release)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/lib/win32/freeglut260/Release/freeglut.dll ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/../Release/freeglut.dll COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/lib/win32/freeglut260/Release/glew32.dll ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/../Release/glew32.dll COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/lib/win32/AntTweakBar/lib/AntTweakBar.dll ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/../Release/AntTweakBar.dll COPYONLY)

# MinSizeRel libs (Release)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/lib/win32/freeglut260/Release/freeglut.dll ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/../MinSizeRel/freeglut.dll COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/lib/win32/freeglut260/Release/glew32.dll ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/../MinSizeRel/glew32.dll COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/lib/win32/AntTweakBar/lib/AntTweakBar.dll ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/../MinSizeRel/AntTweakBar.dll COPYONLY)

# RelWithDebInfo libs (Release)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/lib/win32/freeglut260/Release/freeglut.dll ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/../RelWithDebInfo/freeglut.dll COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/lib/win32/freeglut260/Release/glew32.dll ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/../RelWithDebInfo/glew32.dll COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/lib/win32/AntTweakBar/lib/AntTweakBar.dll ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/../RelWithDebInfo/AntTweakBar.dll COPYONLY)

ENDIF(${CMAKE_SYSTEM_NAME} MATCHES "Windows")

add_subdirectory(src)
add_subdirectory(Data)
