
#include <iostream>

int main () {
    int arr[] = {1,3,2,5,6,9,0,8,7,4};
    size_t arr_length = sizeof(arr) / sizeof(arr[0]);

    for (int i = 0; i < arr_length; i++) {
        std::cout << arr[i] << " ";
    }

    return 0;
}