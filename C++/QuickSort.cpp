
#include <iostream>
#include <cstdlib>
#include <ctime>

#define ARRAY_LENGTH 100
#define MAX_VALUE 101

void print_array(const int array[], const int array_length)
{
    for (int i = 0; i < array_length; i++)
    {
        std::cout << array[i];
        if (i < array_length - 1)
            std::cout << ", ";
        else
            std::cout << std::endl;
    }
}

void quick_sort(int array[], const int array_length)
{
    if (array_length <= 1)
        return;

    int swap_marker = -1;
    const int pivot = array_length - 1;

    for (int i = 0; i < array_length; i++)
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
    const int left_length = &(array[swap_marker]) - left;
    quick_sort(left, left_length);

    int *right = array + swap_marker + 1;
    const int rigth_length = array_length - left_length - 1;
    quick_sort(right, rigth_length);
}

int main()
{
    srand(time(0));
    int array[ARRAY_LENGTH];
    for (int i = 0; i < ARRAY_LENGTH; i++)
        array[i] = rand() % MAX_VALUE;

    print_array(array, ARRAY_LENGTH);
    quick_sort(array, ARRAY_LENGTH);
    print_array(array, ARRAY_LENGTH);

    return 0;
}