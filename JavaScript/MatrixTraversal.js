"use strict"

let matrix = [
    [1, 4, 7],
    [2, 5, 8],
    [3, 6, 9]];

let arr = new Array(9);

for (let x = 0; x < 3; x++) {
    for (let y = 0; y < 3; y++) {
        arr[x * 3 + y] = matrix[y][x];
    }
}

for (let i = 0; i < arr.length; i += 3) {
    console.log(`${arr[i]} ${arr[i+1]} ${arr[i+2]}`);        
}