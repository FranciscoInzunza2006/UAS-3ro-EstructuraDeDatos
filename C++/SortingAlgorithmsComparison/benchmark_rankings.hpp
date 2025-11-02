//
// Created by Franc on 30/10/2025.
//

#pragma once
#include <cstddef>
#include <string>
#include <utility>
#include <vector>

#include "benchmark.hpp"


class BenchmarkRankings
{
    const std::vector<std::size_t> sample_sizes;
    const std::vector<std::string> sample_generators_names;
    std::vector<NamedBenchmarkResults> results;

public:
    BenchmarkRankings(const std::vector<std::size_t>& sample_sizes,
                     const std::vector<std::string>& sample_generators_names,
                     std::vector<NamedBenchmarkResults> results)
        : sample_sizes(sample_sizes),
          sample_generators_names(sample_generators_names),
          results(std::move(results))
    {
    }

    void createRankings();
};
