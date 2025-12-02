
add_library(DirectorySystem directory_system.cpp directory_system.hpp)
target_link_libraries(DirectorySystem
        PRIVATE CommandLine
        PRIVATE File
)
target_include_directories(DirectorySystem PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
