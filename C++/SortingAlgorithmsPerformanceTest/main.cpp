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
    const std::vector<ArrayFunction> input_generators = {
        inOrder,
        inReverse,
        randomValues
    };
    const auto benchmarker = SortingBenchmark(sample_sizes, input_generators);


    const std::vector<ArrayFunction> sorting_algorithms = {
        bubbleSort,
        selectionSort,
        quickSort
    };

    std::vector<BenchmarkResults> results;
    results.reserve(sorting_algorithms.size());
    for (const auto& algorithm : sorting_algorithms)
    {
        results.push_back(benchmarker.runBenchmark(algorithm));
    }

    std::string samples_name[] = {
        "En orden",
        "En reversa",
        "Elementos aleatorios"
    };

    std::string algorithms_name[] = {
        "Bubble Sort",
        "Selection Sort",
        "Quick Sort"
    };

    constexpr std::size_t al = sizeof(algorithms_name) / sizeof(algorithms_name[0]);
    constexpr std::size_t sl = sizeof(samples_name) / sizeof(samples_name[0]);
    for (int i = 0; i < al; i++)
    {
        std::cout << algorithms_name[i] << std::endl;
        for (int j = 0; j < sl; j++)
        {
            std::cout << samples_name[j] << std::endl;

            for (std::size_t k = 0; k < sample_sizes.size(); k++)
            {
                std::cout << "\t" << sample_sizes[k] << ": " << results[i][j][k].count() << "ms" << std::endl;
            }
        }
        std::cout << std::endl;
    }

    return 0;
}
