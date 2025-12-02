cmake_minimum_required(VERSION 4.0)
project(Directory_System)

set(CMAKE_CXX_STANDARD 17)

add_compile_options(-Wall -Wextra -pedantic)

add_subdirectory(modules)

add_executable(main main.cpp)
target_link_libraries(main
        PRIVATE CommandLine
        PRIVATE File
        PRIVATE DirectorySystem
)
