
#include <iostream>

#define NUMBERS_TO_READ 10

int main()
{
    int arr[NUMBERS_TO_READ];

    std::cout << "Ingresa " << NUMBERS_TO_READ << " numeros.\n";
    for (int i = 0; i < NUMBERS_TO_READ; i++)
    {
        std::cout << "#" << i + 1 << ": ";
        std::cin >> arr[i];
    }

    float media = 0;
    int evens = 0;
    for (int i = 0; i < NUMBERS_TO_READ; i++)
    {
        media += arr[i];

        if (arr[i] % 2 == 0)
            evens++;
    }
    media /= NUMBERS_TO_READ;

    std::cout << "Numeros pares: " << evens << std::endl;
    std::cout << "Numeros impares: " << NUMBERS_TO_READ - evens << std::endl;
    std::cout << "Promedio: " << media << std::endl;

    return 0;
}