"use strict"

function bubble_sort(array) {
    for (let i = 0; i < array.length; i++) {
        let swapped = false;
        for (let j = 0; j < array.length - 1 - i; j++) {
            if (array[j] > array[j + 1]) {
                [array[j], array[j + 1]] = [array[j + 1], array[j]];
                swapped = true;
            }
        }

        if (!swapped)
            break;
    }
}

const ARRAY_LENGTH = 32;
const MAX_VALUE = 100;
let array = new Array(ARRAY_LENGTH);
for (let i = 0; i < array.length; i++) {
    array[i] = Math.floor(Math.random() * MAX_VALUE + 1);
}

console.log(array.join());
bubble_sort(array);
console.log(array.join());