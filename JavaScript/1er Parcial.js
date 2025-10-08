
"use strict"

// 1. Ordenar y buscar 
const HAYSTACK_LENGTH = 10;

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

// Replace with binary search
function find(haystack, needle) {
    for (let i = 0; i < haystack.length; i++) {
        if (haystack[i] == needle)        
            return i;
    }   

    return -1;
}   

let haystack = new Array(HAYSTACK_LENGTH);
haystack = [0, 1, 2, 4, 3, 7, 5, 8, 9, 6];
let needle = 7;

console.log("Array original: ", haystack.join(", "));
bubble_sort(haystack);
console.log("Array ordenado: ", haystack.join(", "));

console.log("Elemento a buscar: ", needle);
let needle_index = find(haystack, needle);
if (needle_index != -1) {
    console.log("El elemento buscado esta en el indice: ", needle_index);
} else {
    console.log("No se encontro el elemento buscado");
}


// 2. Valor máximo
const MATRIX_SIZE = 6;
let matrix = new Array(MATRIX_SIZE);
for (let i = 0; i < matrix.length; i++) {
    matrix[i] = new Array(MATRIX_SIZE);

    for (let j = 0; j < matrix[i].length; j++) {
        matrix[i][j] = i * matrix.length + j;
    }
}

let max = matrix[0][0];
for (let i = 0; i < matrix.length; i++) {
    for (let j = 0; j < matrix[i].length; j++) {
        if (matrix[i][j] > max) {
            max = matrix[i][j];
        }
    }
}

console.log("\n\nMatriz:");
console.log(matrix.join("\n"));
console.log("Valor maximo: ", max);

// Sub arreglos Ordenar (5 x 5 x 5)
const MATRIX_3D_LENGTH = 5;

let matrix3d = new Array(MATRIX_3D_LENGTH);
let idk = MATRIX_3D_LENGTH * MATRIX_3D_LENGTH * MATRIX_3D_LENGTH;
for (let i = 0; i < matrix3d.length; i++) {
    matrix3d[i] = new Array(MATRIX_3D_LENGTH);
    
    for (let j = 0; j < matrix3d[i].length; j++) {
        matrix3d[i][j] = new Array(MATRIX_3D_LENGTH);

        for (let k = 0; k < matrix3d[i][j].length; k++) {
            matrix3d[i][j][k] = idk;
            idk -= 1;
        }
    }
}

console.log("\n\nMatriz 3D:");
for (let i = 0; i < matrix3d.length; i++) {
    const matrix = matrix3d[i];
    console.log(matrix.join("\n"));
    console.log("");
}

// Ordenar la matriz 3d
for (let i = 0; i < matrix3d.length; i++) {
    const matrix = matrix3d[i];
    for (let j = 0; j < matrix.length; j++) {
        const array = matrix[j];
        bubble_sort(array);
    }
    bubble_sort(matrix);
}
bubble_sort(matrix3d);

console.log("Matriz 3D ordenada:");
for (let i = 0; i < matrix3d.length; i++) {
    const matrix = matrix3d[i];
    console.log(matrix.join("\n"));
    console.log("");
}