cmake_minimum_required(VERSION 2.8.0)
project(GameEngine)

include_directories(./lib/linux/AntTweakBar/include/)

if(NOT CMAKE_BUILD_TYPE)
set (CMAKE_BUILD_TYPE Debug)
endif(NOT CMAKE_BUILD_TYPE)

# Only Debug and Release supported
if(NOT(CMAKE_BUILD_TYPE MATCHES Debug OR CMAKE_BUILD_TYPE MATCHES Release))
set(CMAKE_BUILD_TYPE Debug)
endif(NOT(CMAKE_BUILD_TYPE MATCHES Debug OR CMAKE_BUILD_TYPE MATCHES Release))

#file(COPY Data DESTINATION GameEngine/${CMAKE_BUILD_TYPE})

add_subdirectory(src)
add_subdirectory(Data)
