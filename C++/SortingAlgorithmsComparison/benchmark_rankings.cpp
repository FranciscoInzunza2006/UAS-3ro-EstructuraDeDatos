//
// Created by Franc on 30/10/2025.
//

#include "benchmark_rankings.hpp"

#include <algorithm>
#include <iostream>

void BenchmarkRankings::createRankings()
{
    const std::size_t rows =  sample_generators_names.size();
    const std::size_t cols =  sample_sizes.size();

    for (std::size_t i = 0; i < rows; i++)
    {
        for (std::size_t j = 0; j < cols; j++)
        {
            // Sort results to make ranking
            auto sorting_lambda = [i, j](const NamedBenchmarkResults& a, const NamedBenchmarkResults& b)
            {
                return a.results[i][j] < b.results[i][j];
            };
            std::sort(results.begin(), results.end(), sorting_lambda);

            // Print rankings
            std::cout << sample_generators_names[i] << " - " << sample_sizes[j] << '\n';

            int ranking = 1;
            for (auto result : results)
            {
                std::cout << "\t#" << ranking << ' ' << result.name << ": " << result.results[i][j].count() << "ms" << '\n';
                ranking++;
            }
            std::cout << '\n';
        }
    }
}
