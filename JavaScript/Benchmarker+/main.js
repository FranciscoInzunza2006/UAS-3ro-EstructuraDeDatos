
"use strict";

const sample_sizes = [
    50,
    100,
    500,
    1000,
    //1_000,
    //10_000,
    //100_000
];

const sample_generators = [
    inOrder,
    inSemiOrder,
    inReverse
];

const sample_generators_names = [
    "En Orden",
    "En Semi-Orden",
    "En reversa"
];

const sorting_algorithms = [
    bubbleSort,
];

const sorted_algorithms_names = [
    "Bubble Sort",
];

let benchmarker = new Benchmarker(sample_sizes, sample_generators);

let results = [];
for (let i = 0; i < sorting_algorithms.length; i++) {
    results.push(benchmarker.runBenchmark(sorting_algorithms[i]));
}

console.log(results);