"use strict";

function bubbleSort(array) {
    for (let i = 0; i < array.length; i++) {
        let swapped = false;

        for (let j = 0; j < array.length - 1 - i; j++) {
            if (array[j] > array[j + 1]) {
                swapped = true;

                [array[j], array[j + 1]] = [array[j + 1], array[j]];
            }
        }

        if (!swapped)
            return;
    }
}

function selectionSort(array) {
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

function insertionSort(array) {
    for (let i = 1; i < array.length; i++) {
        const key = array[i];
        let j = i;

        while (j > 0 && array[j - 1] > key) {
            array[j] = array[j - 1];
            j--;
        }
        array[j] = key;
    }
}

function radixSort(array) {
    if (array.length === 0) return array;

    const max = Math.max(...array);

    for (let exp = 1; Math.floor(max / exp) > 0; exp *= 10) {
        const output = new Array(array.length);
        const count = new Array(10).fill(0);

        for (let i = 0; i < array.length; i++) {
            const digit = Math.floor(array[i] / exp) % 10;
            count[digit]++;
        }

        for (let i = 1; i < 10; i++) {
            count[i] += count[i - 1];
        }

        for (let i = array.length - 1; i >= 0; i--) {
            const digit = Math.floor(array[i] / exp) % 10;
            output[count[digit] - 1] = array[i];
            count[digit]--;
        }

        for (let i = 0; i < array.length; i++) {
            array[i] = output[i];
        }
    }

    return array;
}

function quickSort(array, begin = 0, end = array.length) {
    while (end - begin > 1) {
        const pivotIndex = end - 1;
        let swapMarker = begin;

        for (let i = begin; i < pivotIndex; i++) {
            if (array[i] <= array[pivotIndex]) {
                // Swap elements
                [array[i], array[swapMarker]] = [array[swapMarker], array[i]];
                swapMarker++;
            }
        }

        [array[pivotIndex], array[swapMarker]] = [array[swapMarker], array[pivotIndex]];

        const leftLength = swapMarker - begin;
        const rightLength = end - swapMarker - 1;

        // Always recurse on smaller partition first, then handle larger partition iteratively
        if (leftLength < rightLength) {
            quickSort(array, begin, swapMarker);  // Sort left partition
            begin = swapMarker + 1;               // Process right partition in next iteration
            // end remains the same
        } else {
            quickSort(array, swapMarker + 1, end); // Sort right partition
            end = swapMarker;                      // Process left partition in next iteration
            // begin remains the same
        }
    }
}

function mergeSort(array, left = 0, right = array.length - 1) {
    function merge(array, left, mid, right) {
        const n1 = mid - left + 1;
        const n2 = right - mid;

        const L = new Array(n1);
        const R = new Array(n2);

        for (let i = 0; i < n1; i++)
            L[i] = array[left + i];
        for (let j = 0; j < n2; j++)
            R[j] = array[mid + 1 + j];

        let i = 0, j = 0;
        let k = left;

        while (i < n1 && j < n2) {
            if (L[i] <= R[j]) {
                array[k] = L[i];
                i++;
            } else {
                array[k] = R[j];
                j++;
            }
            k++;
        }

        while (i < n1) {
            array[k] = L[i];
            i++;
            k++;
        }

        while (j < n2) {
            array[k] = R[j];
            j++;
            k++;
        }
    }

    if (left >= right)
        return;

    const mid = Math.floor(left + (right - left) / 2);
    mergeSort(array, left, mid);
    mergeSort(array, mid + 1, right);
    merge(array, left, mid, right);

}

function heapSort(array) {
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

        if (root !== max) {
            const aux = tree[root];
            tree[root] = tree[max];
            tree[max] = aux;

            heapify(tree, array_length, max);
        }
    }

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

function shellSort(array) {
    for (let gap = array.length / 2; gap > 0; gap = Math.floor(gap / 2)) {
        for (let i = gap; i < array.length; i += 1) {
            let temp = array[i];

            let j;
            for (j = i; j >= gap && array[j - gap] > temp; j -= gap)
                array[j] = array[j - gap];

            array[j] = temp;
        }
    }
}

function builtInSort(array) {
    array.sort((a, b) => a - b);
}