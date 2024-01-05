# CMakeLists.txt
cmake_minimum_required(VERSION 3.10)

# Set project name and language
project(SimpleSFMLProject CXX)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 11)  # You can adjust this to 14, 17, or later

# Add the executable
add_executable(main main.cpp headers/Cell.h Cell.cpp headers/Dijkstra.h Dijkstra.cpp headers/Pathfinder.h Pathfinder.cpp headers/AStar.h AStar.cpp global.hpp)

# Find SFML components
find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)

# Include directories for header files
target_include_directories(main PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

# Link SFML libraries
target_link_libraries(main PRIVATE sfml-graphics sfml-window sfml-system)

