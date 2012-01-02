cmake_minimum_required(VERSION 2.8.0)

# EXECUTABLE (GENERAL)
set(source_files main.cpp AppConfig.cpp AppConfig.h ctypes.h float2.cpp float2.h float3.cpp float3.h float4.cpp float4.h Mat44.cpp Mat44.h strutils.cpp strutils.h util.cpp util.h)
add_executable("${PROJECT_NAME}" ${source_files})

IF(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
target_link_libraries("${PROJECT_NAME}" rt GL GLU GLEW glut AntTweakBar) # libs to link
ENDIF(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
