//
// Created by Franc on 30/10/2025.
//

#include "benchmark_rankings.hpp"

#include <algorithm>
#include <iomanip>
#include <iostream>

void BenchmarkRankings::createRankings()
{
    std::stringstream average_header;
    average_header << COLOR_SPECIAL << "Average";

    const std::size_t types = sample_generators_names.size();
    const std::size_t sizes = sample_sizes.size();
    for (std::size_t type_index = 0; type_index <= types; type_index++)
    {
        std::stringstream sample_type_header;
        if (type_index < types)
            sample_type_header << COLOR_MAIN << sample_generators_names[type_index];
        else
            sample_type_header << average_header.str();

        for (std::size_t size_index = 0; size_index <= sizes; size_index++)
        {
            // Sort results to make ranking
            auto sorting_lambda = [type_index, size_index](const NamedBenchmarkResults& a,
                                                           const NamedBenchmarkResults& b)
            {
                return a.results[type_index][size_index] < b.results[type_index][size_index];
            };
            std::sort(results.begin(), results.end(), sorting_lambda);

            // Print rankings
            std::stringstream sample_size_header;
            if (size_index < sizes)
                sample_size_header << COLOR_MAIN << sample_sizes[size_index];
            else
                sample_size_header << average_header.str();

            std::cout << sample_type_header.str() << COLOR_RESET << " - " << sample_size_header.str() << '\n';
            int ranking = 1;
            for (auto result : results)
            {
                std::stringstream algorithm_ranking; // Alignment
                algorithm_ranking << COLOR_SECONDARY << "\t#" << ranking << ' ' << result.name << ": ";
                std::cout << std::setw(35) << algorithm_ranking.str();

                std::cout << COLOR_DATA << result.results[type_index][size_index].count() << "ms" << '\n';

                ranking++;
            }
        }
        std::cout << std::endl;
    }

    std::cout << COLOR_RESET;
}
