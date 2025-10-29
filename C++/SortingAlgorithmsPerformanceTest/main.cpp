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
    const auto benchmarker = SortingBenchmark(
        //{100, 1'000, 10'000, 100'000},
{100, 1'000, 10'000},
        {
            {"Ordenado", inOrder},
            {"Inverso", inReverse},
            {"Aleatorio", randomValues}
        }
    );

    NamedAlgorithm sorting_algorithms[] = {
        {"Bubble sort", bubbleSort},
        {"Selection sort", selectionSort},
        {"Quick sort", quickSort},
    };

    for (const auto& algorithm : sorting_algorithms)
    {
        benchmarker.runBenchmark(algorithm);
        std::cout << std::endl;
    }

    return 0;
}
