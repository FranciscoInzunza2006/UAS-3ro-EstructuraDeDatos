cmake_minimum_required(VERSION 4.0)
project(SortingAlgorithmsPerformanceTest)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(SortingAlgorithmsPerformanceTest
        main.cpp
        sorting_algorithms.cpp
        sorting_algorithms.hpp
        sorting_benchmark.cpp
        sorting_benchmark.hpp
        sample_generators.cpp
        sample_generators.hpp)
