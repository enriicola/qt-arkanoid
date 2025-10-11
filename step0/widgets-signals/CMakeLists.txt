add_executable(widgets-signals
    src/main.cpp
)

target_link_libraries(widgets-signals PRIVATE
    Qt${QT_VERSION_MAJOR}::Widgets
)