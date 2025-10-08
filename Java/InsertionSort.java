
import java.util.Arrays;
import java.util.Random;

public class InsertionSort {
    static int MAX_VALUE = 101;

    public static void main(String[] args) {
        Random random = new Random();
        int array[] = new int[32];
        for (int i = 0; i < array.length; i++) {
            array[i] = random.nextInt(MAX_VALUE);
        }

        System.out.println(Arrays.toString(array));
        insertion_sort(array);
        System.out.println(Arrays.toString(array));
    }

    private static void insertion_sort(int array[]) {
        for (int i = 1; i < array.length; i++) {
            int j = i - 1;
            while (j >= 0 && array[j] > array[j + 1]) {
                final int aux = array[j];
                array[j] = array[j + 1];
                array[j + 1] = aux;

                j--;
            }
        }
    }
}