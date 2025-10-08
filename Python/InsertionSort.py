

import random


def insertion_sort(array):
    for i in range(len(array)):
        j = i-1
        while (j >= 0 and array[j] > array[j+1]):
            array[j], array[j+1] = array[j+1], array[j]
            j -= 1
    


def main():
    MAX_VALUE = 100
    ARRAY_LENGTH = 32
    array = [0] * ARRAY_LENGTH    
    for i in range(len(array)):
        array[i] = random.randint(0, 100)
    print(array)
    insertion_sort(array)
    print(array)
    
if __name__ == "__main__":
    main()