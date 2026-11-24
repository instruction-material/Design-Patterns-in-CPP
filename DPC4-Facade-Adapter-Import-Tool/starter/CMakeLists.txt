cmake_minimum_required(VERSION 3.20)
project(record_import LANGUAGES CXX)
add_executable(import_records main.cpp)
target_compile_features(import_records PRIVATE cxx_std_20)
