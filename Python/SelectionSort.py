

import random


def insertion_sort(array):
    for i in range(len(array)):    
        min = i
        for j in range(i+1, len(array)):        
            if (array[j] < array[min]):
                min = j
        array[i], array[min] = array[min], array[i]
    
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