import java.util.Arrays;
import java.util.Random;

public class SelectionSort {
    static int MAX_VALUE = 101;

    public static void main(String[] args) {
        Random random = new Random();
        int array[] = new int[32];
        for (int i = 0; i < array.length; i++) {
            array[i] = random.nextInt(MAX_VALUE);
        }

        System.out.println(Arrays.toString(array));
        selection_sort(array);
        System.out.println(Arrays.toString(array));
    }

    private static void selection_sort(int array[]) {
        for (int i = 0; i < array.length - 1; i++) {
            int min = i;
            for (int j = i + 1; j < array.length; j++) {
                if (array[j] < array[min])
                    min = j;
            }
            final int aux = array[min];
            array[min] = array[i];
            array[i] = aux;
        }
    }
}