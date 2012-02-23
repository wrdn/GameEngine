cmake_minimum_required(VERSION 2.8.0)

# workaround to get visual studio to put the exe in the correct directory
IF(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/../")
ENDIF(${CMAKE_SYSTEM_NAME} MATCHES "Windows")

# maths
set(math_headers float2.h float3.h float4.h Quaternion.h Mat44.h Quaternion.h float4_sse.h)
set(math_src float2.cpp float3.cpp float4.cpp Mat44.cpp Quaternion.cpp)

# shading
set(shading_headers Light.h color.h Camera.h RenderTarget.h TextureManager.h Texture.h ShaderManager.h Shader.h)
set(shading_src Camera.cpp RenderTarget.cpp TextureManager.cpp Texture.cpp ShaderManager.cpp Shader.cpp)

# utilities
set(util_headers ctypes.h strutils.h util.h AppConfig.h EngineConfig.h Namable.h GameTime.h PerfTimer.h stb_image.h testobjects.h AntTweakBarFunctions.h)
set(util_src strutils.cpp util.cpp AppConfig.cpp EngineConfig.cpp PerfTimer.cpp)

# other non categorised files
set(others main.cpp)

# use the lists to make groups from
source_group("Header Files\\Math" FILES ${math_headers})
source_group("Header Files\\Shading" FILES ${shading_headers})
source_group("Header Files\\Utilities" FILES ${util_headers})

source_group("Source Files\\Math" FILES ${math_src})
source_group("Source Files\\Shading" FILES ${shading_src})
source_group("Source Files\\Utilities" FILES ${util_src})

# concatenate the lists
set(source_files ${math_headers} ${math_src} ${shading_headers} ${shading_src} ${util_headers} ${util_src} ${others})

add_executable("${PROJECT_NAME}" ${source_files})

IF(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
target_link_libraries("${PROJECT_NAME}" rt GL GLU GLEW glut AntTweakBar) # libs to link
ENDIF(${CMAKE_SYSTEM_NAME} MATCHES "Linux")

IF(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
target_link_libraries("${PROJECT_NAME}" AntTweakBar freeglut glew32)
ENDIF(${CMAKE_SYSTEM_NAME} MATCHES "Windows")