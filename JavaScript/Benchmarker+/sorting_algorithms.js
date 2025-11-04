"use strict";

function bubbleSort(array) {
    for (let i = 0; i < array.length; i++) {
        let swapped = false;

        for (let j = 0; j < array.length - 1 - i; j++) {
            if (array[j] > array[j + 1]) {
                swapped = true;

                [array[j], array[j + 1]] = [array[j + 1], array[j]];
            }
        }

        if (!swapped)
            return;
    }
}

function insertionSort(array) {
    for (let i = 1; i < array.length; i++) {
        const key = array[i];
        let j = i;

        while (j > 0 && array[j - 1] > key) {
            array[j] = array[j - 1];
            j--;
        }
        array[j] = key;
    }
}