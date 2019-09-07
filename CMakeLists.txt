cmake_minimum_required(VERSION 3.13)

project(lava_runner)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_VERBOSE_MAKEFILE ON)

set(THREADS_PREFER_PTHREAD_FLAG ON)

add_compile_options(-Wall -Wextra -Wshadow -Wnon-virtual-dtor -pedantic -Werror)

find_package(Threads REQUIRED)

find_package(SDL2 REQUIRED)

include_directories(${SDL2_INCLUDE_DIRS} ${THREADS_INCLUDE_DIRS})

add_executable(lava_runner src/main.cpp src/Game.cpp src/Controls.cpp src/Sprite.cpp src/Player.cpp src/Goal.cpp src/Lava.cpp)

target_link_libraries(lava_runner ${SDL2_LIBRARIES} Threads::Threads)

message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")