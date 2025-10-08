"use strict"

function insertion_sort(array) {
    for (let i = 1; i < array.length; i++)
    {
        let j = i-1;
        while (j >= 0 && array[j] > array[j+1]) {
            [array[j], array[j + 1]] = [array[j + 1], array[j]];
            j--;
        }
    }
}

const ARRAY_LENGTH = 32;
const MAX_VALUE = 100;
let array = new Array(ARRAY_LENGTH);
for (let i = 0; i < array.length; i++) {
    array[i] = Math.floor(Math.random() * MAX_VALUE + 1);
}

console.log(array.join());
insertion_sort(array);
console.log(array.join());