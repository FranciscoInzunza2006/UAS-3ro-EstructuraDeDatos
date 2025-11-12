cmake_minimum_required(VERSION 4.0)
project(SortingAlgorithmsComparison)

set(CMAKE_CXX_STANDARD 14)

include_directories(include)

add_subdirectory(libraries)

add_library(gui
        src/gui.cpp
        include/gui.hpp
)
target_link_libraries(imgui)


add_executable(sorting_algorithms_comparison
        main.cpp
        include/benchmark.hpp
        src/benchmarker.cpp
        include/benchmarker.hpp
        src/benchmark_formatter.cpp
        include/benchmark_formatter.hpp
        src/benchmark_rankings.cpp
        include/benchmark_rankings.hpp
        src/sample_generators.cpp
        include/sample_generators.hpp
        src/sorting_algorithms.cpp
        include/sorting_algorithms.hpp
        src/gui.cpp
)
target_link_libraries(gui)