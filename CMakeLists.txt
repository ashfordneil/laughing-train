# Generic CMake
cmake_minimum_required(VERSION 2.8)
project(laughing-train)

# CMake Variables
set(CMAKE_C_STANDARD 11)

# Main Library
add_subdirectory(src)
include_directories(src)
