cmake_minimum_required(VERSION 3.16)

project(qt-arkanoid VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_AUTOMOC ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets)

add_executable(qt-arkanoid
    src/main.cpp
    src/Game.h
    src/Game.cpp
    src/GameScene.h
    src/GameScene.cpp
    src/Paddle.h
    src/Paddle.cpp
    src/Ball.h
    src/Ball.cpp
    src/Brick.h
    src/Brick.cpp
    src/PowerUp.h
    src/PowerUp.cpp
)

target_link_libraries(qt-arkanoid PRIVATE
    Qt6::Widgets
)

include(GNUInstallDirs)
install(TARGETS qt-arkanoid
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
