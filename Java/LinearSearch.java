public class LinearSearch {
    public static void main(String[] args) {
        int[] arr = { 1, 3, 2, 5, 6, 9, 0, 8, 7, 4 };

        int target = -1;
        int found = -1;
        for (int i = 0; i < arr.length; i++) {
            if (arr[i] == target) {
                found = i;
                break;
            }
        }

        for (int i = 0; i < arr.length; i++) {
            System.out.printf("%d ", arr[i]);
        }

        System.out.println();

        if (found != -1)
            System.out.printf("%d is in the index %d", target, found);
        else
            System.out.printf("%d isn't on the array", target);
    }
}