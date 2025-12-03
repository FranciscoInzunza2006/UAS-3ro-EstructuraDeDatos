
add_library(DirectorySystem
        file_system.hpp
        file_system.cpp
        file_system_commands.cpp
        path_parser.cpp
)
target_link_libraries(DirectorySystem
        PUBLIC CommandLine
        PUBLIC File
)
target_include_directories(DirectorySystem PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# Tests
add_executable(directory_system_tests tests.cpp)
target_link_libraries(directory_system_tests
        PRIVATE DirectorySystem
        PRIVATE CommandLine
        PRIVATE File
        PRIVATE GTest::gtest_main
)
gtest_discover_tests(directory_system_tests)