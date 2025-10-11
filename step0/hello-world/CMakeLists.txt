# Hello World executable
add_executable(hello-world
    src/main.cpp
)

target_link_libraries(hello-world PRIVATE
    Qt${QT_VERSION_MAJOR}::Widgets
)
