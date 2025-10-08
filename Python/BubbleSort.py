
import random

def bubble_sort(array):
    for i in range(len(array)):
        swapped = False
        for j in range(len(array)-1-i):
            if (array[j] > array[j+1]):
                array[j], array[j+1] = array[j+1], array[j]                
                swapped = True
                                
        if not swapped:
            break
    

def main():
    MAX_VALUE = 100
    ARRAY_LENGTH = 32
    
    array = [0] * ARRAY_LENGTH    
    for i in range(len(array)):
        array[i] = random.randint(0, 100)
    
    print(array)
    bubble_sort(array)
    print(array)
    

if __name__ == "__main__":
    main()