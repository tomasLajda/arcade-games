cmake_minimum_required(VERSION 3.27)
project(arcade_games)

set(CMAKE_CXX_STANDARD 17)

find_package(SDL2 REQUIRED)
find_package(SDL2_ttf REQUIRED)

include_directories(${SDL2_INCLUDE_DIRS} ${SDL2_TTF_INCLUDE_DIRS})

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
        shapes/circle.h
        app/app.cpp
        app/app.h
        scenes/scene.h
        scenes/arcadeScene.cpp
        scenes/arcadeScene.h
        input/inputAction.h
        input/gameController.cpp
        input/gameController.h
        input/inputController.cpp
        input/inputController.h
        games/game.h
        scenes/gameScene.cpp
        scenes/gameScene.h
        utils/fileCommandLoader.cpp
        utils/fileCommandLoader.h
        games/BreakOut/breakOut.cpp
        games/BreakOut/breakOut.h
        games/BreakOut/excluder.cpp
        games/BreakOut/excluder.h
        games/BreakOut/boundaryEdge.h
        games/BreakOut/paddle.cpp
        games/BreakOut/paddle.h
        games/BreakOut/ball.cpp
        games/BreakOut/ball.h
        games/BreakOut/levelBoundary.cpp
        games/BreakOut/levelBoundary.h
        games/BreakOut/block.cpp
        games/BreakOut/block.h
        games/BreakOut/breakOutLevel.cpp
        games/BreakOut/breakOutLevel.h
        games/Tetris/tetris.cpp
        games/Tetris/tetris.h
        games/Tetris/blockT.cpp
        games/Tetris/blockT.h
        games/Tetris/tetrimino.cpp
        games/Tetris/tetrimino.h
        games/Tetris/tetriminoTemplate.cpp
        games/Tetris/tetriminoTemplate.h
        games/Tetris/tetrisLevel.cpp
        games/Tetris/tetrisLevel.h
        graphics/text.cpp
        graphics/text.h
)

# CMakeLists.txt
target_link_libraries(arcade_games /usr/lib/x86_64-linux-gnu/libSDL2.so /usr/lib/x86_64-linux-gnu/libSDL2_ttf.so)
