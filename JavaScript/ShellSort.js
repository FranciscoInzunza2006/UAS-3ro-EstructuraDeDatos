"use strict"

function shellSort(array) {
    for (let gap = array_length / 2; gap > 0; gap /= 2) {
        for (let i = gap; i < array_length; i += 1) {
			let temp = array[i];

			let j;
            for (j = i; j >= gap && array[j - gap] > temp; j -= gap)
                array[j] = array[j - gap];

            array[j] = temp;
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
shellSort(array);
console.log(array.join());