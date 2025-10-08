
#include <iostream>
#include <cstdlib>
#include <ctime>

#define ARRAY_LENGTH 32
#define MAX_VALUE 101

void print_array(const int array[], const int array_length) {
    for (int i = 0; i < array_length; i++) {
        std::cout << array[i];
        if (i < array_length-1)
            std::cout << ", ";
        else 
            std::cout << std::endl;
    }
}

void bubble_sort(int array[], const int array_length)
{
    for (int i = 0; i < array_length; i++)
    {
        bool swapped = false;
        for (int j = 0; j < array_length - 1 - i; j++)
        {
            if (array[j] > array[j+1]) {
                int aux = array[j];
                array[j] = array[j+1];
                array[j+1] = aux;
                swapped = true;
            }
        }

        if (!swapped)
            break;
    }
}

int main()
{
    srand(time(0));
    int array[ARRAY_LENGTH];
    for (int i = 0; i < ARRAY_LENGTH; i++)
        array[i] = rand() % MAX_VALUE;

    print_array(array, ARRAY_LENGTH);
    bubble_sort(array, ARRAY_LENGTH);
    print_array(array, ARRAY_LENGTH);

    return 0;
}