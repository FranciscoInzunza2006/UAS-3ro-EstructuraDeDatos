//
// Created by Franc on 30/10/2025.
//

#include "../include/benchmarker.hpp"

BenchmarkResults Benchmarker::foo(const ArrayFunction& algorithm) const
{
    BenchmarkResults results;
    results.reserve(sample_generators.size());
    for (const auto& sample_generator : sample_generators)
    {
        std::vector<PreciseMilliseconds> sample_type_results;
        for (const auto& sample_length : sample_sizes)
        {
            sample_generator(test_data_buffer.get(), sample_length);

            const auto start = std::chrono::steady_clock::now();
            algorithm(test_data_buffer.get(), sample_length);
            const auto end = std::chrono::steady_clock::now();

            const PreciseMilliseconds time_taken = end - start;
            sample_type_results.push_back(time_taken);
        }

        results.push_back(sample_type_results);
    }

    return results;
}

void Benchmarker::addAverages(BenchmarkResults& results) const
{
    const std::size_t types = sample_generators.size();
    const std::size_t sizes = sample_sizes.size();

    // Add sample type average
    for (auto & result : results)
    {
        float type_average = 0;
        for (auto size_index : result)
        {
            type_average += size_index.count();
        }
        type_average /= static_cast<float>(sizes);
        result.emplace_back(type_average);
    }

    // Add sample size average + algorithm average
    std::vector<float> size_averages;
    size_averages.resize(sizes+1);
    for (auto & result : results)
    {
        for (int i = 0; i < sizes+1; i++)
        {
            size_averages[i] += result[i].count() / static_cast<float>(types);
        }
    }

    results.resize(types+1);
    for (auto size_average : size_averages)
    {
        results.back().emplace_back(size_average);
    }
}

BenchmarkResults Benchmarker::runBenchmark(const ArrayFunction& algorithm) const
{
    BenchmarkResults results = foo(algorithm);
    addAverages(results);

    return results;
}
