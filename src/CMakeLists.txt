cmake_minimum_required(VERSION 2.8.0)

# workaround to get visual studio to put the exe in the correct directory
IF(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/../")
ENDIF(${CMAKE_SYSTEM_NAME} MATCHES "Windows")

# EXECUTABLE (GENERAL)
set(source_files main.cpp AppConfig.cpp AppConfig.h ctypes.h float2.cpp float2.h float3.cpp float3.h float4.cpp float4.h Mat44.cpp Mat44.h strutils.cpp strutils.h util.cpp util.h PerfTimer.cpp PerfTimer.h)
add_executable("${PROJECT_NAME}" ${source_files})

IF(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
target_link_libraries("${PROJECT_NAME}" rt GL GLU GLEW glut AntTweakBar) # libs to link
ENDIF(${CMAKE_SYSTEM_NAME} MATCHES "Linux")

IF(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
target_link_libraries("${PROJECT_NAME}" AntTweakBar freeglut glew32)
ENDIF(${CMAKE_SYSTEM_NAME} MATCHES "Windows")