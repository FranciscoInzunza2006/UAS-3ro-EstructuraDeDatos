
add_library(File file.cpp file.hpp)
target_include_directories(File PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

add_executable(file_tester file_tester.cpp)
target_link_libraries(file_tester PRIVATE File)

# Tests
add_executable(file_tests tests.cpp)
target_link_libraries(file_tests
        PRIVATE File
        PRIVATE GTest::gtest_main
)
gtest_discover_tests(file_tests)