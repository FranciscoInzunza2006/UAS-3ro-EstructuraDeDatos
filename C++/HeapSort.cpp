
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

void heapify(int tree[], const int array_length, const int root)
{
    int left_node = root * 2 + 1;
    int right_node = root * 2 + 2;

    int max = root;
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

void heap_sort(int array[], const int array_length)
{
    for (int i = array_length / 2 - 1; i >= 0; i--)
    {
        heapify(array, array_length, i);
    }

    for (int i = array_length - 1; i > 0; i--)
    {
        const int aux = array[0];
        array[0] = array[i];
        array[i] = aux;

        heapify(array, i, 0);
    }
}

int main()
{
    srand(time(0));
    int array[ARRAY_LENGTH];
    for (int i = 0; i < ARRAY_LENGTH; i++)
        array[i] = rand() % MAX_VALUE;

    print_array(array, ARRAY_LENGTH);
    heap_sort(array, ARRAY_LENGTH);
    print_array(array, ARRAY_LENGTH);

    return 0;
}