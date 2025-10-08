
public class MatrixTraversal {
    public static void main(String[] args) {
        final int MATRIX_DIMENSION = 3;

        int[][] matrix = {
                { 1, 4, 7 },
                { 2, 5, 8 },
                { 3, 6, 9 } };

        int[] arr = new int[MATRIX_DIMENSION * MATRIX_DIMENSION];

        for (int x = 0; x < MATRIX_DIMENSION; x++) {
            for (int y = 0; y < MATRIX_DIMENSION; y++) {
                arr[x * MATRIX_DIMENSION + y] = matrix[y][x];
            }
        }

        for (int i = 0; i < MATRIX_DIMENSION * MATRIX_DIMENSION; i++) {
            System.out.print(arr[i]);
            if ((i + 1) % MATRIX_DIMENSION == 0)
                System.out.println();
        }

    }

}