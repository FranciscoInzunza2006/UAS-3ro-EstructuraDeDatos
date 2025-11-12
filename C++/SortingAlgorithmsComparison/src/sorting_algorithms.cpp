//
// Created by Franc on 28/10/2025.
//

#include "../include/sorting_algorithms.hpp"

#include <algorithm>

// Helpers prototypes
void merge(int arr[], std::size_t left, std::size_t mid, std::size_t right);
void mergeSortMain(int arr[], std::size_t left, std::size_t right);

void heapify(int tree[], std::size_t array_length, std::size_t root);

void countSort(int arr[], std::size_t n, int exp);

// Sorting algorithms
void bubbleSort(int array[], const std::size_t array_length)
{
    for (std::size_t i = 0; i < array_length; i++)
    {
        bool swapped = false;
        for (std::size_t j = 0; j < array_length - 1 - i; j++)
        {
            if (array[j] > array[j + 1])
            {
                swapped = true;

                const int aux = array[j];
                array[j] = array[j + 1];
                array[j + 1] = aux;
            }
        }

        if (!swapped)
            return;
    }
}

void selectionSort(int array[], const std::size_t array_length)
{
    for (std::size_t i = 0; i < array_length - 1; i++)
    {
        std::size_t min_index = i;
        for (std::size_t j = i + 1; j < array_length; j++)
        {
            if (array[j] < array[min_index])
                min_index = j;
        }
        const int aux = array[min_index];
        array[min_index] = array[i];
        array[i] = aux;
    }
}

void insertionSort(int array[], const std::size_t array_length)
{
    for (std::size_t i = 1; i < array_length; i++)
    {
        const int key = array[i];
        std::size_t j = i;

        while (j > 0 && array[j - 1] > key)
        {
            array[j] = array[j - 1];
            j--;
        }
        array[j] = key;
    }
}

void quickSort(int array[], std::size_t array_length)
{
    while (array_length > 1)
    {
        const std::size_t pivot_index = array_length - 1;
        std::size_t swap_marker = 0;

        for (std::size_t i = 0; i < pivot_index; i++)
        {
            if (array[i] <= array[pivot_index])
            {
                const int aux = array[i];
                array[i] = array[swap_marker];
                array[swap_marker] = aux;
                swap_marker++;
            }
        }

        const int aux = array[pivot_index];
        array[pivot_index] = array[swap_marker];
        array[swap_marker] = aux;

        std::size_t left_length = swap_marker;
        std::size_t right_length = array_length - swap_marker - 1;

        if (left_length < right_length)
        {
            quickSort(array, left_length);
            array += swap_marker + 1;
            array_length = right_length;
        }
        else
        {
            quickSort(array + swap_marker + 1, right_length);
            array_length = left_length;
        }
    }
}

void mergeSort(int array[], const std::size_t array_length)
{
    mergeSortMain(array, 0, array_length - 1);
}

void heapSort(int array[], const std::size_t array_length)
{
    for (std::size_t i = array_length / 2 - 1; i > 0; i--)
    {
        heapify(array, array_length, i);
    }

    for (std::size_t i = array_length - 1; i > 0; i--)
    {
        const int aux = array[0];
        array[0] = array[i];
        array[i] = aux;

        heapify(array, i, 0);
    }
}

void radixSort(int array[], const std::size_t array_length)
{
    int max = array[0];
    for (std::size_t i = 1; i < array_length; i++)
    {
        if (array[i] > max)
        {
            max = array[i];
        }
    }

    int iterations = 0;
    while (max > 0)
    {
        max /= 10;
        iterations++;
    }

    int exp = 10;
    for (int i = 0; i < iterations; i++)
    {
        countSort(array, array_length, exp);

        exp *= 10;
    }
}

void shellSort(int array[], const std::size_t array_length)
{
    for (std::size_t gap = array_length / 2; gap > 0; gap /= 2)
    {
        for (std::size_t i = gap; i < array_length; i += 1)
        {
            const int temp = array[i];

            std::size_t j;
            for (j = i; j >= gap && array[j - gap] > temp; j -= gap)
                array[j] = array[j - gap];

            array[j] = temp;
        }
    }
}

void builtInSort(int array[], const std::size_t array_length)
{
    std::sort(array, array + array_length);
}

// Helpers
void merge(int arr[], const std::size_t left, const std::size_t mid, const std::size_t right)
{
    const std::size_t n1 = mid - left + 1;
    const std::size_t n2 = right - mid;

    const auto left_sub = new int[n1];
    const auto right_sub = new int[n2];

    for (int i = 0; i < n1; i++)
        left_sub[i] = arr[left + i];
    for (int j = 0; j < n2; j++)
        right_sub[j] = arr[mid + 1 + j];

    std::size_t i = 0;
    std::size_t j = 0;
    std::size_t k = left;

    while (i < n1 && j < n2)
    {
        if (left_sub[i] <= right_sub[j])
        {
            arr[k] = left_sub[i];
            i++;
        }
        else
        {
            arr[k] = right_sub[j];
            j++;
        }
        k++;
    }

    while (i < n1)
    {
        arr[k] = left_sub[i];
        i++;
        k++;
    }

    while (j < n2)
    {
        arr[k] = right_sub[j];
        j++;
        k++;
    }

    delete[] left_sub;
    delete[] right_sub;
}

void mergeSortMain(int arr[], const std::size_t left, const std::size_t right)
{
    if (left < right)
    {
        const std::size_t mid = left + (right - left) / 2;

        mergeSortMain(arr, left, mid);
        mergeSortMain(arr, mid + 1, right);

        merge(arr, left, mid, right);
    }
}

void heapify(int tree[], const std::size_t array_length, const std::size_t root)
{
    const std::size_t left_node = root * 2 + 1;
    const std::size_t right_node = root * 2 + 2;

    std::size_t max = root;
    if (left_node < array_length && tree[left_node] > tree[max])
    {
        max = left_node;
    }
    if (right_node < array_length && tree[right_node] > tree[max])
    {
        max = right_node;
    }

    if (root != max)
    {
        const int aux = tree[root];
        tree[root] = tree[max];
        tree[max] = aux;

        heapify(tree, array_length, max);
    }
}

void countSort(int arr[], const std::size_t n, const int exp)
{

    // Output array
    int output[n];
    int count[10] = { 0 };

    std::size_t i;

    // Store count of occurrences
    // in count[]
    for (i = 0; i < n; i++)
        count[(arr[i] / exp) % 10]++;

    // Change count[i] so that count[i]
    // now contains actual position
    // of this digit in output[]
    for (i = 1; i < 10; i++)
        count[i] += count[i - 1];

    // Build the output array
    for (i = n - 1; i > 0; i--) {
        output[count[(arr[i] / exp) % 10] - 1] = arr[i];
        count[(arr[i] / exp) % 10]--;
    }

    // Copy the output array to arr[],
    // so that arr[] now contains sorted
    // numbers according to current digit
    for (i = 0; i < n; i++)
        arr[i] = output[i];
}