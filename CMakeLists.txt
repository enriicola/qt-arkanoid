cmake_minimum_required(VERSION 3.16)

project(qt-arkanoid VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

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
    src/SoundManager.h
    src/SoundManager.cpp
    src/Particle.h
    src/Particle.cpp
    src/SettingsDialog.h
    src/SettingsDialog.cpp
    src/HighScoreManager.h
    src/HighScoreManager.cpp
    src/HighScoreDialog.h
    src/HighScoreDialog.cpp
    src/Level.h
    src/Level.cpp
    src/LevelManager.h
    src/LevelManager.cpp
    resources.qrc
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
