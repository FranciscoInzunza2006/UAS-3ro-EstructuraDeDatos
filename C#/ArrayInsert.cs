
int[] arr = [1, 3, 2, 5, 6, 9, 0, 8, 7, 4];

int value_to_insert = 404;
int index_to_insert = 3;

for (int i = arr.Length - 1; i > index_to_insert; i--)
{
    arr[i] = arr[i - 1];
}
arr[index_to_insert] = value_to_insert;

for (int i = 0; i < arr.Length; i++)
{
    Console.Write(arr[i] + " ");
}
