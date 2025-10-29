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

void SortingBenchmark::runBenchmark(const NamedAlgorithm& algorithm) const
{
    std::cout << "Algoritmo: " << algorithm.name << std::endl;

    for (const auto& input_generator : input_generators)
    {
        std::cout << "Tipo de muestra: " << input_generator.name << std::endl;
        std::cout << "Tiempo tomado en muestra con tamaño de: \n";
        for (const auto& sample_length : sample_sizes)
        {
            input_generator.funct(test_data_buffer, sample_length);

            auto start = std::chrono::steady_clock::now();
            algorithm.funct(test_data_buffer, sample_length);
            auto end = std::chrono::steady_clock::now();

            std::chrono::duration<float, std::milli> time_taken = end - start;
            std::cout << "\t" << sample_length << ": " << time_taken.count() << "ms\n";
        }
    }
}
