//
// Created by Franc on 30/10/2025.
//

#include "benchmark_rankings.hpp"

#include <algorithm>
#include <iomanip>
#include <iostream>

// TODO: Add averages
void BenchmarkRankings::createRankings()
{
    const std::size_t types = sample_generators_names.size();
    const std::size_t sizes = sample_sizes.size();

    for (std::size_t type_index = 0; type_index < types; type_index++)
    {
        for (std::size_t size_index = 0; size_index < sizes; size_index++)
        {
            // Sort results to make ranking
            auto sorting_lambda = [type_index, size_index](const NamedBenchmarkResults& a,
                                                           const NamedBenchmarkResults& b)
            {
                return a.results[type_index][size_index] < b.results[type_index][size_index];
            };
            std::sort(results.begin(), results.end(), sorting_lambda);

            // Print rankings
            std::cout << COLOR_ALGORITHM << sample_generators_names[type_index] << " - " << sample_sizes[size_index] <<
                '\n';

            int ranking = 1;
            for (auto result : results)
            {
                std::stringstream ss; // Alignment
                ss << COLOR_HEADER_AVERAGE << "\t#" << ranking << ' ' << COLOR_HEADER_TIME << result.name << ": ";
                std::cout << std::setw(35) << ss.str();

                std::cout << COLOR_TIME << result.results[type_index][size_index].count() << "ms" << '\n';

                ranking++;
            }
        }
        std::cout << std::endl;
    }

    std::cout << COLOR_RESET;
}
