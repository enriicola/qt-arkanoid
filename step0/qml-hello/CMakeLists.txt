# Find Qt6 components we need
find_package(Qt6 REQUIRED COMPONENTS Core Qml Quick)

# Create the executable
add_executable(qml-hello
    main.cpp
)

# Link Qt libraries
target_link_libraries(qml-hello PRIVATE
    Qt6::Core
    Qt6::Qml
    Qt6::Quick
)