
int[] arr = [1, 3, 2, 5, 6, 9, 0, 8, 7, 4];


int target = -1;
int found = -1;
for (int i = 0; i < arr.Length; i++)
{
    if (arr[i] == target)
    {
        found = i;
        break;
    }
}

for (int i = 0; i < arr.Length; i++)
{
    Console.Write(arr[i] + " ");
}

Console.WriteLine();
if (found != -1)
    Console.WriteLine($"{target} is in the index {found}");
else
    Console.WriteLine($"{target} isn't on the array");