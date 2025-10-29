//
// Created by Franc on 29/10/2025.
//

#include "sample_generators.hpp"

#include <random>

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
