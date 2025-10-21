
#include <cstdlib>
#include <ctime>
#include <iostream>

#define ARRAY_LENGTH 99
#define MAX_VALUE 11

void print_array(const int array[], const int array_length);
void shell_sort(int array[],
				const int array_length);  // Good for partial sorting

int main() {
	srand(time(0));
	int array[ARRAY_LENGTH];
	for (int i = 0; i < ARRAY_LENGTH; i++) array[i] = rand() % MAX_VALUE;

	std::cout << "Array before sorting: \n";
	print_array(array, ARRAY_LENGTH);

	shell_sort(array, ARRAY_LENGTH);

	std::cout << "Array after sorting: \n";
	print_array(array, ARRAY_LENGTH);

	return 0;
}

void shell_sort(int array[], const int array_length) {
	for (int gap = array_length / 2; gap > 0; gap /= 2) {
		for (int i = gap; i < array_length; i += 1) {
			int temp = array[i];

			int j;
			for (j = i; j >= gap && array[j - gap] > temp; j -= gap)
				array[j] = array[j - gap];

			array[j] = temp;
		}
	}
}

void print_array(const int array[], const int array_length) {
	for (int i = 0; i < array_length; i++) {
		std::cout << array[i];
		if (i < array_length - 1)
			std::cout << ", ";
		else
			std::cout << std::endl;
	}
}
