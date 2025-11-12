"use strict";

function inOrder(array) {
    for (let i = 0; i < array.length; i++) {
        array[i] = i;
    }
}

function inSemiOrder(array) {
    for (let i = 0; i < array.length; i++) {
        array[i] = i;

        if (i % 3 === 0) {
            array[i] += i % 2 === 0 ? 3 : -3;
        }
    }
}

function inReverse(array) {
    for (let i = 0; i < array.length; i++) {
        array[i] = array.length - i;
    }
}

function randomValues(array) {
    for (let i = 0; i < array.length; i++) {
        array[i] = Math.floor(Math.random() * array.length); // LMAO this thing is unfair af
    }
}