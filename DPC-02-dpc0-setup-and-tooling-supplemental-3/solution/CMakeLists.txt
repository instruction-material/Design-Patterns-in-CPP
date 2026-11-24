cmake_minimum_required(VERSION 3.20)
project(length_lab LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
enable_testing()

add_library(length length.cpp)
add_executable(length_demo main.cpp)
target_link_libraries(length_demo PRIVATE length)

add_executable(length_checks checks.cpp)
target_link_libraries(length_checks PRIVATE length)
add_test(NAME centimetre_conversion COMMAND length_checks)
