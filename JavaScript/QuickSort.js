"use strict"

function quick_sort(array, begin, end) {
    if (end - begin <= 1)
        return;

    let swap_marker = begin - 1;
    const pivot = array[end - 1];
    for (let i = begin; i < end; i++) {
        if (array[i] <= pivot) {
            swap_marker += 1;

            const aux = array[i];
            array[i] = array[swap_marker];
            array[swap_marker] = aux;
        }
    }

    quick_sort(array, begin, swap_marker);
    quick_sort(array, swap_marker+1, end);
}

const ARRAY_LENGTH = 100;
const MAX_VALUE = 100;
let array = new Array(ARRAY_LENGTH);
for (let i = 0; i < array.length; i++) {
    array[i] = Math.floor(Math.random() * MAX_VALUE + 1);
}

console.log(array.join());
quick_sort(array, 0, array.length);
console.log(array.join());