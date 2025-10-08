
import random

def heapify(arr, n, i):    
    l = 2 * i + 1 
    r = 2 * i + 2  
    largest = i 
    if l < n and arr[l] > arr[largest]:
        largest = l
    if r < n and arr[r] > arr[largest]:
        largest = r

    if largest != i:
        arr[i], arr[largest] = arr[largest], arr[i]
        heapify(arr, n, largest)

def heap_sort(arr):
    n = len(arr) 
    for i in range(n // 2 - 1, -1, -1):
        heapify(arr, n, i)

    for i in range(n - 1, 0, -1):
        arr[0], arr[i] = arr[i], arr[0] 
        heapify(arr, i, 0)

def main():
    MAX_VALUE = 100
    ARRAY_LENGTH = 32
    array = [0] * ARRAY_LENGTH    
    for i in range(len(array)):
        array[i] = random.randint(0, 100)
    print(array)
    heap_sort(array)
    print(array)
    
if __name__ == "__main__":
    main()