
void heapify(int[] tree, int array_length, int root)
{
    int left_node = root * 2 + 1;
    int right_node = root * 2 + 2;

    int max = root;
    if (left_node < array_length && tree[left_node] > tree[max])
    {
        max = left_node;
    }
    if (right_node < array_length && tree[right_node] > tree[max])
    {
        max = right_node;
    }

    if (root != max)
    {
        int aux = tree[root];
        tree[root] = tree[max];
        tree[max] = aux;

        heapify(tree, array_length, max);
    }
}

void heap_sort(int[] array, int array_length)
{
    for (int i = array_length / 2 - 1; i >= 0; i--)
    {
        heapify(array, array_length, i);
    }

    for (int i = array_length - 1; i > 0; i--)
    {
        int aux = array[0];
        array[0] = array[i];
        array[i] = aux;

        heapify(array, i, 0);
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
heap_sort(array, ARRAY_LENGTH);
Console.WriteLine(string.Join(", ", array));

