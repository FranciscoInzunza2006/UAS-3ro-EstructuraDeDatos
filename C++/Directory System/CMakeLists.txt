cmake_minimum_required(VERSION 4.0)
project(Directory_System)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(modules)

add_executable(Directory_System main.cpp)
