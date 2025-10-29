//
// Created by Franc on 28/10/2025.
//

#include <iostream>
#include <ostream>

#include "sorting_algorithms.hpp"
#include "tester.hpp"

void inOrder(int array[], const std::size_t array_length)
{
    for (std::size_t i = 0; i < array_length; i++)
    {
        array[i] = static_cast<int>(i) + 1;
    }
}

void randomValues(int array[], const std::size_t array_length)
{
    for (std::size_t i = 0; i < array_length; i++)
    {
        array[i] = std::rand() % 100;
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
    const auto tester = Tester(
        {100, 1'000, 10'000, 100'000},
        {
            {"Ordenado", inOrder},
            {"Inverso", inReverse},
            {"Aleatorio", randomValues}
        }
    );

    SortingAlgorithm sorting_algorithms[] = {
        {"Bubble sort", bubbleSort},
        {"Selection sort", selectionSort},
        {"Quick sort", quickSort},
    };

    // TODO: Change name
    for (const auto& test : sorting_algorithms)
    {
        tester.executeTest(test);
        std::cout << std::endl;
    }

    return 0;
}
