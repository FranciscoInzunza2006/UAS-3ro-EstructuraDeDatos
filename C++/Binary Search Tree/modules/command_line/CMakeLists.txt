
add_library(Command command.cpp command.hpp)

add_library(CommandLine command_line.cpp command_line.hpp)
target_link_libraries(CommandLine Command)
target_include_directories(CommandLine PUBLIC .)