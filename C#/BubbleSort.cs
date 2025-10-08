
static void bubble_sort(int[] array, int array_length)
{
    for (int i = 0; i < array_length; i++)
    {
        bool swapped = false;
        for (int j = 0; j < array_length - 1 - i; j++)
        {
            if (array[j] > array[j + 1])
            {
                int aux = array[j];
                array[j] = array[j + 1];
                array[j + 1] = aux;
                swapped = true;
            }
        }

        if (!swapped)
            break;
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
bubble_sort(array, ARRAY_LENGTH);
Console.WriteLine(string.Join(", ", array));

