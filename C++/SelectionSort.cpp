
#include <iostream>
#include <cstdlib>
#include <ctime>

#define ARRAY_LENGTH 32
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

void selection_sort(int array[], const int array_length)
{
    for (int i = 0; i < array_length - 1; i++)
    {
        int min = i;
        for (int j = i + 1; j < array_length; j++)
        {
            if (array[j] < array[min])
                min = j;
        }
        const int aux = array[min];
        array[min] = array[i];
        array[i] = aux;
    }
}

int main()
{
    srand(time(0));
    int array[ARRAY_LENGTH];
    for (int i = 0; i < ARRAY_LENGTH; i++)
        array[i] = rand() % MAX_VALUE;

    print_array(array, ARRAY_LENGTH);
    selection_sort(array, ARRAY_LENGTH);
    print_array(array, ARRAY_LENGTH);

    return 0;
}