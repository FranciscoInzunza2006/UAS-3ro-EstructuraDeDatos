
import random

def shellSort(array):
    n = len(array)
    gap = n // 2
    while (gap > 0):
        for i in range(gap, n):
            temp = array[i]

            j = i
            while (j >= gap and array[j-gap] > temp):
                array[j] = array[j-gap]
                j -= gap
            array[j] = temp

        gap //= 2
    
def main():
    MAX_VALUE = 100
    ARRAY_LENGTH = 32
    array = [0] * ARRAY_LENGTH    
    for i in range(len(array)):
        array[i] = random.randint(0, 100)
    print(array)
    shellSort(array)
    print(array)
    
if __name__ == "__main__":
    main()