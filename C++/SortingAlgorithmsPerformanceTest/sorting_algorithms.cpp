//
// Created by Franc on 28/10/2025.
//

#include "sorting_algorithms.hpp"

// TODO: Implement all

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
}

// FIXME: Segfaults when 100'000
void quickSort(int array[], const std::size_t array_length)
{
    if (array_length <= 1)
        return;

    std::size_t swap_marker = -1;
    const std::size_t pivot = array_length - 1;

    for (std::size_t i = 0; i < array_length; i++)
    {
        if (array[i] <= array[pivot])
        {
            swap_marker++;

            const int aux = array[i];
            array[i] = array[swap_marker];
            array[swap_marker] = aux;
        }
    }

    int *left = array;
    const std::size_t left_length = &(array[swap_marker]) - left;
    quickSort(left, left_length);

    int *right = array + swap_marker + 1;
    const std::size_t right_length = array_length - left_length - 1;
    quickSort(right, right_length);
}

void mergeSort(int array[], const std::size_t array_length)
{
}

void heapSort(int array[], const std::size_t array_length)
{
}

void radixSort(int array[], const std::size_t array_length)
{
}

void shellSort(int array[], const std::size_t array_length)
{
}
