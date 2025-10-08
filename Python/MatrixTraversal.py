

matrix = [
    [1, 4, 7],
    [2, 5, 8],
    [3, 6, 9]
]

arr = [0] * 9

for x in range(len(matrix)):
    for y in range(len(matrix)):
        arr[x * 3 + y] = matrix[y][x]

for i in range(0, len(arr), 3):
    print(f"{arr[i]} {arr[i+1]} {arr[i+2]}")
