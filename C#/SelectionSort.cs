
static void selection_sort(int[] array, int array_length)
{
    for (int i = 0; i < array_length - 1; i++)
    {
        int min = i;
        for (int j = i + 1; j < array_length; j++)
        {
            if (array[j] < array[min])
                min = j;
        }
        const int aux = array[min];
        array[min] = array[i];
        array[i] = aux;
    }
}

const int ARRAY_LENGTH = 32;
const int MAX_VALUE = 100;
int[] array = new int[ARRAY_LENGTH];
Random random = new Random();
for (int i = 0; i < ARRAY_LENGTH; i++)
{
    array[i] = random.Next(MAX_VALUE + 1);
}

Console.WriteLine(string.Join(", ", array));
selection_sort(array, ARRAY_LENGTH);
Console.WriteLine(string.Join(", ", array));

