
static void shellSort(int[] array, int array_length)
{
    for (int gap = array_length / 2; gap > 0; gap /= 2)
    {
        for (int i = gap; i < array_length; i += 1)
        {
            int temp = array[i];

            int j;
            for (j = i; j >= gap && array[j - gap] > temp; j -= gap)
                array[j] = array[j - gap];

            array[j] = temp;
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
shellSort(array, ARRAY_LENGTH);
Console.WriteLine(string.Join(", ", array));

