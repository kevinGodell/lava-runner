cmake_minimum_required(VERSION 3.13)

project(lava_runner)

set(CMAKE_CXX_STANDARD 17)

add_compile_options("-Wall" "-Wendif-labels" "-W" "-Werror" "-Wextra" "-Wpedantic" "-Wunused-parameter")

find_package(THREADS REQUIRED)

find_package(SDL2 REQUIRED)

include_directories(${SDL2_INCLUDE_DIRS})

add_executable(lava_runner src/main.cpp src/Game.cpp src/Game.hpp src/Controls.cpp src/Controls.hpp src/Sprite.cpp src/Sprite.hpp src/Player.cpp src/Player.hpp src/Goal.cpp src/Goal.hpp src/Lava.cpp src/Lava.hpp src/LavaPools.cpp src/LavaPools.hpp  src/RisingLava.cpp src/RisingLava.hpp)

target_link_libraries(lava_runner ${SDL2_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})