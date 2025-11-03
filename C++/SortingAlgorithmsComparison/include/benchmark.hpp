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


// constexpr auto COLOR_RESET = "";
//
// constexpr auto COLOR_MAIN = "";
//
// constexpr auto COLOR_SECONDARY = "";
// constexpr auto COLOR_DATA = "";
//
// constexpr auto COLOR_SPECIAL = "";
// constexpr auto COLOR_SPECIAL_DATA = "";

constexpr auto COLOR_RESET = "\033[0m";

constexpr auto COLOR_MAIN = "\033[0;96m";

constexpr auto COLOR_SECONDARY = "\033[0;95m";
constexpr auto COLOR_DATA = "\033[0;93m";

constexpr auto COLOR_SPECIAL = "\033[0;91m";
constexpr auto COLOR_SPECIAL_DATA = "\033[1;36m";