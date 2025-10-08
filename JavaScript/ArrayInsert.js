"use strict"

let arr = [1,3,2,5,6,9,0,8,7,4];

let value_to_insert = 404;
let index_to_insert = 3;

console.log(arr.join());

arr.splice(index_to_insert, 0, value_to_insert);
arr.pop();

console.log(arr.join());