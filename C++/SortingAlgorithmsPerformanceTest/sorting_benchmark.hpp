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

using ArrayFunction = std::function<void(int [], std::size_t)>;

using PreciseMilliseconds = std::chrono::duration<float, std::milli>;
using BenchmarkResults = std::vector<std::vector<PreciseMilliseconds>>;

// TODO: This function doesn't prints anything so why it need names
class SortingBenchmark
{
    int* test_data_buffer{nullptr};
    const std::vector<std::size_t> sample_sizes;
    const std::vector<ArrayFunction> input_generators;

public:
    SortingBenchmark(const std::vector<std::size_t>& sample_sizes,
                     const std::vector<ArrayFunction>& input_generators)
        : sample_sizes(sample_sizes),
          input_generators(input_generators)
    {
        const size_t max_sample_length = std::max(sample_sizes.front(), sample_sizes.back());
        test_data_buffer = new int[max_sample_length];
    }

    ~SortingBenchmark()
    {
        delete[] test_data_buffer;
    };

    BenchmarkResults runBenchmark(const ArrayFunction& algorithm) const;
};
