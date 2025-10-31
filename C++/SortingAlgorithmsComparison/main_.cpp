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

#define CELL_WIDTH 14

using NamedArrayFunction = std::pair<const std::string, ArrayFunction>;

void printBenchmarkResult(const BenchmarkResults& result, const std::string& algorithm_name,
                          const std::vector<std::string>& input_generators_name,
                          const std::vector<std::size_t>& sample_sizes)
{
    constexpr auto COLOR_ALGORITHM = "\033[0;96m";
    constexpr auto COLOR_HEADER = "\033[0;95m";
    // ReSharper disable once CppTooWideScope
    constexpr auto COLOR_TIME = "\033[0;93m";
    constexpr auto COLOR_RESET = "\033[0m";

    std::stringstream results_table;
    results_table << COLOR_ALGORITHM << std::left << std::setw(CELL_WIDTH) << algorithm_name;

    // Sample size
    for (const std::size_t& sample_size : sample_sizes)
    {
        results_table << COLOR_HEADER << std::right << std::setw(CELL_WIDTH) << sample_size;
    }
    results_table << "\n";

    // Samples
    for (std::size_t type = 0; type < input_generators_name.size(); type++)
    {
        results_table << COLOR_HEADER << std::left << std::setw(CELL_WIDTH) << input_generators_name[type];

        // Benchmark result
        for (size_t size = 0; size < sample_sizes.size(); size++)
        {
            results_table << COLOR_TIME << std::right << std::setw(CELL_WIDTH) << result[type][size].count();
        }
        results_table << "\n";
    }

    std::cout << results_table.str() << COLOR_RESET << std::endl;
}

void printBenchmarkResults(const std::vector<BenchmarkResults>& results,
                           const std::vector<std::string>& sorting_algorithms_name,
                           const std::vector<std::string>& input_generators_name,
                           const std::vector<std::size_t>& sample_sizes)
{
    // Header
    // std::cout << std::setw(CELL_WIDTH) << "Ordenamiento: " << std::setw(CELL_WIDTH) << ' ' << std::setw(CELL_WIDTH) <<
    //     "Tamaño de muestra" << '\n';

    // Print results
    for (std::size_t algorithm = 0; algorithm < sorting_algorithms_name.size(); algorithm++)
    {
        printBenchmarkResult(results[algorithm], sorting_algorithms_name[algorithm], input_generators_name,
                             sample_sizes);
    }
}

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

    const auto benchmarker = BenchmarkerFormatter(sample_sizes, input_generators);

    // Run benchmarks
    std::vector<BenchmarkResults> results;
    results.reserve(sorting_algorithms.size());
    for (const auto& algorithm : sorting_algorithms)
    {
        results.push_back(benchmarker.runBenchmark(algorithm));
    }
    printBenchmarkResults(results, sorting_algorithms_name, input_generators_name, sample_sizes);

    return 0;
}
