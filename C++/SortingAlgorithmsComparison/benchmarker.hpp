//
// Created by Franc on 30/10/2025.
//

#pragma once

#include <memory>

#include "benchmark.hpp"

class Benchmarker
{
    std::unique_ptr<int[]> test_data_buffer{nullptr};
    const std::vector<std::size_t> sample_sizes;
    const std::vector<ArrayFunction> sample_generators;

public:
    Benchmarker(const std::vector<std::size_t>& sample_sizes,
                const std::vector<ArrayFunction>& sample_generators)
        : sample_sizes(sample_sizes),
          sample_generators(sample_generators)
    {
        const size_t max_sample_length = std::max(sample_sizes.front(), sample_sizes.back());
        test_data_buffer = std::make_unique<int[]>(max_sample_length);
    }

    BenchmarkResults runBenchmark(const ArrayFunction& algorithm) const;
};
