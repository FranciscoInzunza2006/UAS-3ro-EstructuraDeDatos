
add_library(Command command.cpp)

add_library(CommandLine command_line.cpp command_line.hpp)
target_link_libraries(CommandLine PRIVATE Command)
target_include_directories(CommandLine PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
