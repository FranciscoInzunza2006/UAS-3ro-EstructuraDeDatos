
#include <iostream>

int main () {
    int arr[] = {1,3,2,5,6,9,0,8,7,4};
    size_t arr_length = sizeof(arr) / sizeof(arr[0]);

    int value_to_insert = 404;
    int index_to_insert = 3;

    for (int i = arr_length-1; i > index_to_insert; i--) {
        arr[i] = arr[i-1];
    }
    arr[index_to_insert] = value_to_insert;

    for (int i = 0; i < arr_length; i++) {
        std::cout << arr[i] << " ";
    }

    return 0;
}