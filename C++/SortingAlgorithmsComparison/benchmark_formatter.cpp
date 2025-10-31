//
// Created by Franc on 30/10/2025.
//

#include "benchmark.hpp"
#include "benchmark_formatter.hpp"

#include <iomanip>
#include <iostream>
#include <sstream>

constexpr int CELL_WIDTH = 14;

void BenchmarkerFormatter::printBenchmarkResult(const std::string& algorithm_name, const BenchmarkResults& result) const
{
    std::stringstream results_table;
    results_table << COLOR_ALGORITHM << std::left << std::setw(CELL_WIDTH) << algorithm_name;

    // Sample size
    results_table << COLOR_HEADER << std::right;
    for (const std::size_t& sample_size : sample_sizes)
    {
        results_table << std::setw(CELL_WIDTH) << sample_size;
    }
    results_table << "\n";

    // Samples
    for (std::size_t type = 0; type < sample_generators_names.size(); type++)
    {
        results_table << COLOR_HEADER << std::setw(CELL_WIDTH) << std::left << sample_generators_names[type];

        // Benchmark result
        results_table << COLOR_TIME << std::right;
        for (size_t size = 0; size < sample_sizes.size(); size++)
        {
            results_table << std::setw(CELL_WIDTH) << result[type][size].count();
        }
        results_table << "\n";
    }

    std::cout << results_table.str() << COLOR_RESET << std::endl;
}
