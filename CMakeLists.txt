cmake_minimum_required(VERSION 3.27)
project(arcade_games)

set(CMAKE_CXX_STANDARD 17)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

add_executable(arcade_games main.cpp
        utils/utils.cpp
        utils/utils.h
        utils/vec2D.cpp
        utils/vec2D.h
        graphics/color.cpp
        graphics/color.h
        graphics/screenBuffer.cpp
        graphics/screenBuffer.h
        graphics/screen.cpp
        graphics/screen.h
        shapes/line2D.cpp
        shapes/line2D.h
        shapes/star2D.cpp
        shapes/star2D.h
        shapes/shape.cpp
        shapes/shape.h
        shapes/triangle.cpp
        shapes/triangle.h
        shapes/AARectangle.cpp
        shapes/AARectangle.h
        shapes/circle.cpp
        shapes/circle.h)

target_link_libraries(arcade_games ${SDL2_LIBRARIES})
