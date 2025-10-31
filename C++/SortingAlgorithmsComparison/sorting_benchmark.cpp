//
// Created by Franc on 28/10/2025.
//

#include "sorting_benchmark.hpp"

#include <chrono>
#include <iostream>
#include <ostream>

void printArray(int array[], const std::size_t array_length)
{
    for (std::size_t i = 0; i < array_length; i++)
    {
        std::cout << array[i] << " ";
    }
}

BenchmarkResults SortingBenchmark::runBenchmark(const ArrayFunction& algorithm) const
{
    BenchmarkResults results;
    results.reserve(input_generators.size());
    for (const auto& input_generator : input_generators)
    {
        std::vector<PreciseMilliseconds> sample_type_results;
        sample_type_results.reserve(sample_sizes.size());
        for (const auto& sample_length : sample_sizes)
        {
            input_generator(test_data_buffer, sample_length);

            const auto start = std::chrono::steady_clock::now();
            algorithm(test_data_buffer, sample_length);
            const auto end = std::chrono::steady_clock::now();

            const PreciseMilliseconds time_taken = end - start;
            sample_type_results.push_back(time_taken);
        }
        results.push_back(sample_type_results);
    }

    return results;
}
