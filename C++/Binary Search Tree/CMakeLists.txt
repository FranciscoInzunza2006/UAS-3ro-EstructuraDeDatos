cmake_minimum_required(VERSION 4.0)
project(Binary_Search_Tree)

set(CMAKE_CXX_STANDARD 14)

add_compile_options(-Wall -Wextra -pedantic)

add_subdirectory(modules)

add_executable(main main.cpp)
target_link_libraries(main BST)

add_executable(tester tester.cpp)
target_link_libraries(tester BST)
