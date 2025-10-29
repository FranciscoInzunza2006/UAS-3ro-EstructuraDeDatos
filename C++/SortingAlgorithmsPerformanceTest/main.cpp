//
// Created by Franc on 28/10/2025.
//

#include <iomanip>
#include <iostream>
#include <ostream>
#include <random>

#include "sample_generators.hpp"
#include "sorting_algorithms.hpp"
#include "sorting_benchmark.hpp"

using NamedArrayFunction = std::pair<const std::string, ArrayFunction>;

int main()
{
    // Set up
    const std::vector<std::size_t> sample_sizes = {100, 500, 1000};

    const std::vector<ArrayFunction> sorting_algorithms = {
        bubbleSort,
        selectionSort,
        quickSort,
    };
    const std::vector<std::string> sorting_algorithms_name = {
        "Bubble Sort",
        "Selection Sort",
        "Quick Sort",
    };


    const std::vector<ArrayFunction> input_generators = {
        inOrder,
        inReverse,
        randomValues,
    };
    const std::vector<std::string> input_generators_name = {
        "En orden",
        "En reversa",
        "Aleatorio",
    };

    const auto benchmarker = SortingBenchmark(sample_sizes, input_generators);

    // Run benchmarks
    std::vector<BenchmarkResults> results;
    results.reserve(sorting_algorithms.size());
    for (const auto& algorithm : sorting_algorithms)
    {
        results.push_back(benchmarker.runBenchmark(algorithm));
    }

    // Print results
    for (std::size_t algorithm = 0; algorithm < sorting_algorithms_name.size(); algorithm++)
    {
        constexpr int cell_width = 14;
        const std::string& algorithm_name = sorting_algorithms_name[algorithm];

        // Header
        std::stringstream results_table;

        results_table << std::left << std::setw(cell_width) << algorithm_name;
        for (const std::size_t& sample_size : sample_sizes)
        {
            results_table << std::right << std::setw(cell_width) << sample_size;
        }
        results_table << "\n";

        // Samples
        for (std::size_t type = 0; type < input_generators.size(); type++)
        {
            const std::string& sample_type = input_generators_name[type];
            results_table << std::left << std::setw(cell_width) << sample_type;

            // Time
            for (size_t size = 0; size < sample_sizes.size(); size++)
            {
                results_table << std::right << std::setw(cell_width) << results[algorithm][type][size].count();
            }
            results_table << "\n";
        }

        std::cout << results_table.str() << std::endl;
    }


    return 0;
}
