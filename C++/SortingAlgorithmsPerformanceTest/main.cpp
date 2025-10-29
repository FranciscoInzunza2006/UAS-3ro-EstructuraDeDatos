//
// Created by Franc on 28/10/2025.
//

#include <iostream>
#include <ostream>
#include <random>

#include "sorting_algorithms.hpp"
#include "sorting_benchmark.hpp"

void inOrder(int array[], const std::size_t array_length)
{
    for (std::size_t i = 0; i < array_length; i++)
    {
        array[i] = static_cast<int>(i) + 1;
    }
}

void randomValues(int array[], const std::size_t array_length)
{
    std::default_random_engine generator; // Same values each time to be more consistent NOLINT(*-msc51-cpp)
    std::uniform_int_distribution<> distribution(1, 100);

    for (std::size_t i = 0; i < array_length; i++)
    {
        array[i] = distribution(generator);
    }
}

void inReverse(int array[], const std::size_t array_length)
{
    for (std::size_t i = array_length; i > 0; i--)
    {
        array[i - 1] = static_cast<int>(i);
    }
}

int main()
{
    const std::vector<std::size_t> sample_sizes = {100, 500, 1000};
    const std::vector<NamedAlgorithm> input_generators = {
        {"Ordenado", inOrder},
        {"Inverso", inReverse},
        {"Aleatorio", randomValues}
    };
    const auto benchmarker = SortingBenchmark(sample_sizes, input_generators);

    NamedAlgorithm sorting_algorithms[] = {
        {"Bubble sort", bubbleSort},
        {"Selection sort", selectionSort},
        {"Quick sort", quickSort},
    };

    std::vector<BenchmarkResults> results;
    results.reserve(sizeof(sorting_algorithms) / sizeof(sorting_algorithms[0]));
    for (const auto& algorithm : sorting_algorithms)
    {
        results.push_back(benchmarker.runBenchmark(algorithm));
    }

    for (const auto& result : results)
    {

    }

    return 0;
}
