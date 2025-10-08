import java.util.Arrays;
import java.util.Random;

public class QuickSort {
    static int MAX_VALUE = 101;

    public static void main(String[] args) {
        Random random = new Random();
        int array[] = new int[32];
        for (int i = 0; i < array.length; i++) {
            array[i] = random.nextInt(MAX_VALUE);
        }

        System.out.println(Arrays.toString(array));
        quick_sort(array, 0, array.length);
        System.out.println(Arrays.toString(array));
    }

    public static void quick_sort(int[] array, int begin, int end) {
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
        quick_sort(array, swap_marker + 1, end);
    }
}
