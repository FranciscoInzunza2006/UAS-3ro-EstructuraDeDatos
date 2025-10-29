//
// Created by Franc on 28/10/2025.
//

#pragma once
#include <algorithm>
#include <chrono>
#include <functional>
#include <iostream>
#include <ostream>
#include <string>
#include <vector>

using ArrayFunction = void(int [], std::size_t);

struct NamedAlgorithm
{
    std::string name;
    std::function<ArrayFunction> funct;
};

using PreciseMilliseconds = std::chrono::duration<float, std::milli>;
using BenchmarkResults = std::vector<std::vector<PreciseMilliseconds>>;

// TODO: This function doesn't prints anything so why it need names
class SortingBenchmark
{
    int* test_data_buffer{nullptr};
    const std::vector<std::size_t> sample_sizes;
    const std::vector<NamedAlgorithm> input_generators;

public:
    SortingBenchmark(const std::vector<std::size_t>& sample_sizes,
                     const std::vector<NamedAlgorithm>& input_generators)
        : sample_sizes(sample_sizes),
          input_generators(input_generators)
    {
        const std::size_t max_sample_length = *std::max_element(sample_sizes.begin(), sample_sizes.end());
        test_data_buffer = new int[max_sample_length];

        if (test_data_buffer == nullptr)
        {
            std::cerr << "Error allocating memory" << std::endl;
        }
    }

    ~SortingBenchmark()
    {
        delete[] test_data_buffer;
    };

    BenchmarkResults runBenchmark(const NamedAlgorithm& algorithm) const;

    BenchmarkResults runBenchmark(const std::string& algorithm_name,
                      const std::function<ArrayFunction>& algorithm_function) const
    {
        return runBenchmark({algorithm_name, algorithm_function});
    };
};
