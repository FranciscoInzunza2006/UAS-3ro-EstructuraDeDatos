"use strict"

function heapify(tree, array_length, root) {
    let left_node = root * 2 + 1;
    let right_node = root * 2 + 2;

    let max = root;
    if (left_node < array_length && tree[left_node] > tree[max]) {
        max = left_node;
    }
    if (right_node < array_length && tree[right_node] > tree[max]) {
        max = right_node;
    }

    if (root != max) {
        const aux = tree[root];
        tree[root] = tree[max];
        tree[max] = aux;

        heapify(tree, array_length, max);
    }
}

function heap_sort(array) {
    for (let i = array.length / 2 - 1; i >= 0; i--) {
        heapify(array, array.length, i);
    }

    for (let i = array.length - 1; i > 0; i--) {
        const aux = array[0];
        array[0] = array[i];
        array[i] = aux;

        heapify(array, i, 0);
    }
}

const ARRAY_LENGTH = 100;
const MAX_VALUE = 100;
let array = new Array(ARRAY_LENGTH);
for (let i = 0; i < array.length; i++) {
    array[i] = Math.floor(Math.random() * MAX_VALUE + 1);
}

console.log(array.join());
heap_sort(array);
console.log(array.join());