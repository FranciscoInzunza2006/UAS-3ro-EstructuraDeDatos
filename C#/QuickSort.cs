
static void quick_sort(int[] array, int begin, int end)
{
    if (end - begin <= 1)
        return;

    int swap_marker = begin - 1;
    int pivot = array[end - 1];
    for (int i = begin; i < end; i++) {
        if (array[i] <= pivot) {
            swap_marker += 1;

            int aux = array[i];
            array[i] = array[swap_marker];
            array[swap_marker] = aux;
        }
    }

    quick_sort(array, begin, swap_marker);
    quick_sort(array, swap_marker+1, end);
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
quick_sort(array, 0, ARRAY_LENGTH);
Console.WriteLine(string.Join(", ", array));

