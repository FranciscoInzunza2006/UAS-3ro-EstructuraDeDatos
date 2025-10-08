
static void insertion_sort(int[] array, int array_length)
{
    for (int i = 1; i < array_length; i++)
    {
        int j = i-1;
        while (j >= 0 && array[j] > array[j+1]) {
            int aux = array[j];
            array[j] = array[j+1];
            array[j+1] = aux;

            j--;
        }
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
insertion_sort(array, ARRAY_LENGTH);
Console.WriteLine(string.Join(", ", array));

