//
// Created by Franc on 28/10/2025.
//

#include "tester.hpp"

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

void Tester::executeTest(const SortingAlgorithm& algorithm) const
{
    std::cout << "Algoritmo: " << algorithm.name << std::endl;

    for (const auto& sample_preparing_function : sample_preparing_functions)
    {
        std::cout << "Tipo de muestra: " << sample_preparing_function.name << std::endl;
        std::cout << "Tiempo tomado en muestra con tamaño de: \n";
        for (const auto& sample_length : sample_lengths)
        {
            sample_preparing_function.funct(sample, sample_length);
            //printArray(sample, sample_length);
            //std::cout << std::endl;

            auto start = std::chrono::steady_clock::now();
            algorithm.funct(sample, sample_length);
            auto end = std::chrono::steady_clock::now();
            //printArray(sample, sample_length);

            // TODO: It prints in seconds, change it to milliseconds
            const double time_taken = std::chrono::duration_cast<std::chrono::duration<double>>(end - start).count();
            std::cout << "\t" << sample_length << ": " << time_taken << "s\n";
        }
    }
}
