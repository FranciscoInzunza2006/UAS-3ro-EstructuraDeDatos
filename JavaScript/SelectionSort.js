"use strict"

function selection_sort(array) {
    for (let i = 0; i < array.length - 1; i++) {
        let min = i;
        for (let j = i + 1; j < array.length; j++) {
            if (array[j] < array[min])
                min = j;
        }
        const aux = array[min];
        array[min] = array[i];
        array[i] = aux;
    }
}

const ARRAY_LENGTH = 32;
const MAX_VALUE = 100;
let array = new Array(ARRAY_LENGTH);
for (let i = 0; i < array.length; i++) {
    array[i] = Math.floor(Math.random() * MAX_VALUE + 1);
}

console.log(array.join());
selection_sort(array);
console.log(array.join());