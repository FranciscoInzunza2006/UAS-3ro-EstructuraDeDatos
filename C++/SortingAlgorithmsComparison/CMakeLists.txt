cmake_minimum_required(VERSION 4.0)
project(SortingAlgorithmsComparison)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(sorting_algorithms_comparison
        main.cpp
        benchmark.hpp
        benchmarker.cpp
        benchmarker.hpp
        benchmark_formatter.cpp
        benchmark_formatter.hpp
        benchmark_rankings.cpp
        benchmark_rankings.hpp
)
