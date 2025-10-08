import java.util.Arrays;
import java.util.Random;

class Program {
    static int MAX_VALUE = 101;

    public static void main(String[] args) {
        Random random = new Random();
        int array[] = new int[32];
        for (int i = 0; i < array.length; i++) {
            array[i] = random.nextInt(MAX_VALUE);
        }

        System.out.println(Arrays.toString(array));
        heap_sort(array);
        System.out.println(Arrays.toString(array));
    }

    static void heapify(int tree[], final int array_length, final int root) {
        int left_node = root * 2 + 1;
        int right_node = root * 2 + 2;

        int max = root;
        if (left_node < array_length && tree[left_node] > tree[max]) {
            max = left_node;
        }
        if (right_node < array_length && tree[right_node] > tree[max]) {
            max = right_node;
        }

        if (root != max) {
            final int aux = tree[root];
            tree[root] = tree[max];
            tree[max] = aux;

            heapify(tree, array_length, max);
        }
    }

    static void heap_sort(int array[]) {
        for (int i = array.length / 2 - 1; i >= 0; i--) {
            heapify(array, array.length, i);
        }

        for (int i = array.length - 1; i > 0; i--) {
            final int aux = array[0];
            array[0] = array[i];
            array[i] = aux;

            heapify(array, i, 0);
        }
    }
}
