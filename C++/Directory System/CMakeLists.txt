cmake_minimum_required(VERSION 4.0)
project(Directory_System)

# GoogleTest requires at least C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/52eb8108c5bdec04579160ae17225d66034bd723.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()
include(GoogleTest)

add_compile_options(-Wall -Wextra -pedantic)

add_subdirectory(modules)

add_executable(main main.cpp)
target_link_libraries(main
        PRIVATE CommandLine
        PRIVATE File
        PRIVATE DirectorySystem
)
