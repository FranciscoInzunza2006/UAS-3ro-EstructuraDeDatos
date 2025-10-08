
import random

def quick_sort(array, begin, end):
    if (end - begin <= 1):
        return
    
    swap_marker = begin - 1
    pivot = array[end - 1]
    for i in range(begin, end):
        if (array[i] <= pivot):
            swap_marker += 1
            array[i], array[swap_marker] = array[swap_marker], array[i]            

    quick_sort(array, begin, swap_marker)
    quick_sort(array, swap_marker+1, end)

def main():
    MAX_VALUE = 100
    ARRAY_LENGTH = 32
    array = [0] * ARRAY_LENGTH    
    for i in range(len(array)):
        array[i] = random.randint(0, 100)
    print(array)
    quick_sort(array, 0, len(array))
    print(array)
    
if __name__ == "__main__":
    main()