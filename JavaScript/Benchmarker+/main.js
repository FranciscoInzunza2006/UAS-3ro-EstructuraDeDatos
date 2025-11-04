
"use strict";

const samples_size = [
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

const sample_generators_name = [
    "En Orden",
    "En Semi-Orden",
    "En reversa"
];

const sorting_algorithms = [
    bubbleSort,
    insertionSort,
];

const sorting_algorithms_name = [
    "Bubble Sort",
    "Insertion Sort",
];

let results = [];
function runBenchmarks() {
    const benchmarker = new Benchmarker(samples_size, sample_generators);
    for (let i = 0; i < sorting_algorithms.length; i++) {
        results.push(benchmarker.runBenchmark(sorting_algorithms[i]));
    }
    console.log(results);
}


