
add_library(FileSystem
        file_system.hpp
        file_system.cpp
        file_system_commands.cpp
        file_system_serializer.cpp
        path_parser.cpp
)
target_link_libraries(FileSystem
        PRIVATE CommandLine
        PRIVATE File
)
target_include_directories(FileSystem PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# Tests
add_executable(file_system_tests tests.cpp)
target_link_libraries(file_system_tests
        PRIVATE FileSystem
        PRIVATE File
        PRIVATE CommandLine
        PRIVATE GTest::gtest_main
)
gtest_discover_tests(file_system_tests)