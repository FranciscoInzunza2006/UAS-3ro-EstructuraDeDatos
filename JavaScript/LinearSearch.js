"use strict"

let arr = [1, 3, 2, 5, 6, 9, 0, 8, 7, 4];

let target = -1;
let found = -1;
for (let i = 0; i < arr.length; i++) {
    if (arr[i] == target) {
        found = i;
        break;
    }
}

console.log(arr.join());
if (found != -1)
    console.log(`${target} is in the index ${found}`, target, found);
else
    console.log(`${target} isn't on the array`);