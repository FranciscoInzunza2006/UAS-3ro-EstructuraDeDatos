import java.util.Arrays;
import java.util.Random;

public class BubbleSort {
    static int MAX_VALUE = 101;

    public static void main(String[] args) {
        Random random = new Random();
        int array[] = new int[32];
        for (int i = 0; i < array.length; i++) {
            array[i] = random.nextInt(MAX_VALUE);
        }

        System.out.println(Arrays.toString(array));
        bubble_sort(array);
        System.out.println(Arrays.toString(array));
    }

    private static void bubble_sort(int array[]) {
        for (int i = 0; i < array.length; i++) {
            Boolean swapped = false;
            for (int j = 0; j < array.length - 1 - i; j++) {
                if (array[j] > array[j + 1]) {
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
}