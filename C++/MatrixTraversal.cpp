
#include <iostream>

#define MATRIX_DIMENSION 3

int main()
{
    int matrix[MATRIX_DIMENSION][MATRIX_DIMENSION] = {
        {1, 4, 7},
        {2, 5, 8},
        {3, 6, 9}};

    int arr[MATRIX_DIMENSION * MATRIX_DIMENSION];

    for (int x = 0; x < MATRIX_DIMENSION; x++)
    {
        for (int y = 0; y < MATRIX_DIMENSION; y++)
        {
            arr[x * MATRIX_DIMENSION + y] = matrix[y][x];
        }
    }

    for (int i = 0; i < MATRIX_DIMENSION * MATRIX_DIMENSION; i++)
    {
        std::cout << arr[i];
        if ((i+1) % MATRIX_DIMENSION == 0)
            std::cout << '\n';
    }

    return 0;
}