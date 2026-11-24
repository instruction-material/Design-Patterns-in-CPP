cmake_minimum_required(VERSION 3.20)
project(length_lab LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
enable_testing()

add_library(length length.cpp)
add_executable(length_demo main.cpp)
target_link_libraries(length_demo PRIVATE length)

# TODO: Build checks.cpp as length_checks, link it to length and register it with CTest.
