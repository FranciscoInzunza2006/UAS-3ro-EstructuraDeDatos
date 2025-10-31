//
// Created by Franc on 30/10/2025.
//

#pragma once
#include <chrono>
#include <functional>
#include <string>
#include <vector>

using ArrayFunction = std::function<void(int [], std::size_t)>;

using PreciseMilliseconds = std::chrono::duration<float, std::milli>;


/**
 * This type is a table with the benchmark results with an EXTRA row and columns with the averages.
*/
/*
 * When used in the BenchmarkFormatter it should look something like this:
 * <Algorithm>  Size1   Size2   SizeN   Average
 *      Type1   -----   -----   -----   -----
 *      Type2   -----   -----   -----   -----
 *      TypeN   -----   -----   -----   -----
 *    Average   -----   -----   -----   -----
 */
using BenchmarkResults = std::vector<std::vector<PreciseMilliseconds>>;

struct NamedBenchmarkResults
{
    std::string name;
    BenchmarkResults results;
};

constexpr auto COLOR_RESET = "\033[0m";

constexpr auto COLOR_ALGORITHM = "\033[0;96m";

constexpr auto COLOR_HEADER_TIME = "\033[0;95m";
constexpr auto COLOR_TIME = "\033[0;93m";

constexpr auto COLOR_HEADER_AVERAGE = "\033[0;91m";
constexpr auto COLOR_AVERAGE = "\033[1;36m";