cmake_minimum_required(VERSION 3.14)
project(lava_runner)

set(CMAKE_CXX_STANDARD 17)

#set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

find_package(SDL2 REQUIRED)

include_directories(${SDL2_INCLUDE_DIRS})

add_executable(lava_runner src/main.cpp src/Game.cpp src/Game.hpp src/Controls.cpp src/Controls.hpp src/Player.cpp src/Player.hpp src/RectBase.cpp src/RectBase.hpp src/Goal.cpp src/Goal.hpp)

target_link_libraries(lava_runner ${SDL2_LIBRARIES})