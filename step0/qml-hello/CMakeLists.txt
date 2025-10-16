# Find Qt6 components we need
find_package(Qt6 REQUIRED COMPONENTS Core Qml Quick)

# Enable automatic MOC (Meta-Object Compiler) - needed for Q_OBJECT
set(CMAKE_AUTOMOC ON)

# Enable automatic RCC (Resource Compiler) - needed for .qrc files
set(CMAKE_AUTORCC ON)

# Create the executable
add_executable(qml-hello
    src/main.cpp
    src/qml.qrc
)

# Link Qt libraries
target_link_libraries(qml-hello PRIVATE
    Qt6::Core
    Qt6::Qml
    Qt6::Quick
)