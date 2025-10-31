#include <iostream>

#include "benchmark.hpp"
#include "benchmarker.hpp"
#include "benchmark_formatter.hpp"
#include "benchmark_rankings.hpp"
#include "sample_generators.hpp"
#include "sorting_algorithms.hpp"

void foo(const std::vector<std::size_t>& sample_sizes,
         const std::vector<std::pair<std::string, ArrayFunction>>& generators,
         const std::vector<std::pair<std::string, ArrayFunction>>& algorithms)
{
#pragma region Separate Arguments
    std::vector<std::string> generators_name;
    std::vector<ArrayFunction> generators_function;
    for (const auto& generator : generators)
    {
        generators_name.push_back(generator.first);
        generators_function.push_back(generator.second);
    }
#pragma endregion

    // Run Benchmarks
    std::cout << "Running benchmarks...\n";
    const Benchmarker benchmarker(sample_sizes, generators_function);

    std::vector<NamedBenchmarkResults> benchmark_results;
    benchmark_results.reserve(algorithms.size());
    for (const auto& algorithm : algorithms)
    {
        benchmark_results.push_back({
            algorithm.first,
            benchmarker.runBenchmark(algorithm.second)
        });
    }
    std::cout << "Done!\n\n";

    // Print Benchmarks
    std::cout << "Benchmark results: (Time is in milliseconds)\n";
    const BenchmarkerFormatter formatter(sample_sizes, generators_name);
    for (const auto & benchmark_result : benchmark_results)
    {
        formatter.printBenchmarkResult(benchmark_result);
        std::cout << std::endl;
    }
    // Make benchmark rankings
    std::cout << "Rankings:\n";
    BenchmarkRankings rankings(sample_sizes, generators_name, benchmark_results);
    rankings.createRankings();
}

int main()
{
    const std::vector<std::size_t> sample_sizes = {
        100,
        500,
        1'000,
        //10'000,
        //100'000,
        //1'000'000
    };

    const std::vector<std::pair<std::string, ArrayFunction>> sample_generators = {
        {"En order", inOrder},
        {"En reversa", inReverse},
        {"Aleatorio", randomValues}
    };

    const std::vector<std::pair<std::string, ArrayFunction>> sorting_algorithms = {
        {"Bubble Sort", bubbleSort},
        {"Selection Sort", selectionSort},
        {"Quick Sort", quickSort}
    };

    foo(sample_sizes, sample_generators, sorting_algorithms);

    return 0;
}
