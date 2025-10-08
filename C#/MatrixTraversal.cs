
int[,] matrix = {
    { 1, 4, 7},
    { 2, 5, 8},
    { 3, 6, 9}
};

int[] arr = new int[9];

for (int x = 0; x < 3; x++)
{
    for (int y = 0; y < 3; y++)
    {
        arr[x * 3 + y] = matrix[y,x];
    }
}

for (int i = 0; i < 3 * 3; i++)
{
    Console.Write(arr[i]);
    if ((i + 1) % 3 == 0)
        Console.WriteLine();
}

return 0;