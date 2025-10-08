
#include <iostream>

int main()
{
    int arr[] = {1, 3, 2, 5, 6, 9, 0, 8, 7, 4};
    size_t arr_length = sizeof(arr) / sizeof(arr[0]);

    int target = -1;
    int found = -1;
    for (int i = 0; i < arr_length; i++)
    {
        if (arr[i] == target)
        {
            found = i;
            break;
        }
    }

    for (int i = 0; i < arr_length; i++)
    {
        std::cout << arr[i] << " ";
    }

    std::cout << std::endl;

    if (found != -1)
        std::cout << target << " is in the index " << found;
    else
        std::cout << target << " isn't on the array";

    return 0;
}