
add_library(Command command.cpp)

add_library(CommandLine command_line.cpp command_line.hpp)
target_link_libraries(CommandLine PRIVATE Command)
target_include_directories(CommandLine PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# Tests
add_executable(command_line_tests tests.cpp)
target_link_libraries(command_line_tests
        PRIVATE CommandLine
        PRIVATE GTest::gtest_main
)
gtest_discover_tests(command_line_tests)