
"use strict";

const samples_size = [
    //50,
    100,
    //500,
    1_000,
    10_000,
    100_000
];

const sample_generators = [
    inOrder,
    inSemiOrder,
    inReverse,
    randomValues,
];

const sample_generators_name = [
    "En Orden",
    "En Semi-Orden",
    "En reversa",
    "Valores Aleatorio",
];

const sorting_algorithms = [
    bubbleSort,
    selectionSort,
    insertionSort,
    radixSort,

    quickSort,
    mergeSort,
    heapSort,
    shellSort,

    builtInSort
];

const sorting_algorithms_name = [
    "Bubble Sort",
    "Selection Sort",
    "Insertion Sort",
    "Radix Sort",

    "Quick Sort",
    "Merge Sort",
    "Heap Sort",
    "Shell Sort",

    "Built-In"
];

let results = [];
function runBenchmarks() {
    const benchmarker = new Benchmarker(samples_size, sample_generators);
    for (let i = 0; i < sorting_algorithms.length; i++) {
        results.push(benchmarker.runBenchmark(sorting_algorithms[i]));
        console.log(sorting_algorithms_name[i] + " done!");
    }
    console.log(results);
}


