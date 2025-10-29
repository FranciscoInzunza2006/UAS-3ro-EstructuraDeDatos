//
// Created by Franc on 28/10/2025.
//

#pragma once
#include <algorithm>
#include <functional>
#include <iostream>
#include <ostream>
#include <string>
#include <vector>

// TODO: Type template
#define SORTING_ALGORITHM_SIGNATURE void(int[], std::size_t)

struct SortingAlgorithm
{
    std::string name;
    std::function<SORTING_ALGORITHM_SIGNATURE> funct;
};

// TODO: Get better name
class Tester
{
    int* sample {nullptr};
    std::vector<std::size_t> sample_lengths;
    std::vector<SortingAlgorithm> sample_preparing_functions; // TODO: Get better name

public:
    Tester(const std::vector<std::size_t>& test_elements,
           const std::vector<SortingAlgorithm>& sample_preparing_functions)
        : sample_lengths(test_elements),
          sample_preparing_functions(sample_preparing_functions)
    {
        const std::size_t max_sample_length = *std::max_element(test_elements.begin(), test_elements.end());
        sample = new int[max_sample_length];

        if (sample == nullptr)
        {
            std::cerr << "Error allocating memory" << std::endl;
        }
    }

    ~Tester()
    {
        delete[] sample;
    };

    void executeTest(const SortingAlgorithm& algorithm) const;
    void executeTest(const std::string& algorithm_name, const std::function<SORTING_ALGORITHM_SIGNATURE>& algorithm_function)
    {
        executeTest({algorithm_name, algorithm_function});
    };
};
