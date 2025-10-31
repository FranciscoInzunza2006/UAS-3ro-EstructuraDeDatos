//
// Created by Franc on 30/10/2025.
//

#pragma once
#include <string>
#include <vector>
#include "benchmark.hpp"

class BenchmarkerFormatter
{
    const std::vector<std::size_t> sample_sizes;
    const std::vector<std::string> sample_generators_names;

public:
    BenchmarkerFormatter(const std::vector<std::size_t>& sample_sizes,
                         const std::vector<std::string>& sample_generators_names)
        : sample_sizes(sample_sizes),
          sample_generators_names(sample_generators_names)
    {
    }

    void printBenchmarkResult(const std::string& algorithm_name, const BenchmarkResults& result) const;
    void printBenchmarkResult(const NamedBenchmarkResults& results) const
    {
        printBenchmarkResult(results.name, results.results);
    }
};
