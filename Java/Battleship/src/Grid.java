public class Grid {
    static final char EMPTY = ' ';
    static final char SHOOT = '*';
    static final char FLAG = 'X';
    static final char SHIP = '#';

    static final int GRID_WIDTH = 5;
    static final int GRID_HEIGHT = 5;

    final int width;
    final int height;
    private final char[][] grid;

    public Grid(int width, int height) {
        this.width = width;
        this.height = height;

        this.grid = new char[width][height];
        for (int x = 0; x < width; x++) {
            for (int y = 0; y < height; y++) {
                this.grid[x][y] = EMPTY;
            }
        }
    }

    public void set(final int x, final int y, final char c) {
        grid[x][y] = c;
    }

    public void set(final Coordinates coordinates, final char c) {
        grid[coordinates.x][coordinates.y] = c;
    }

    public char get(final int x, final int y) {
        return grid[x][y];
    }

    public char get(final Coordinates coordinates) {
        return grid[coordinates.x][coordinates.y];
    }

    public void drawGrid() {
        Util.printSection();
        final String row_separator = "\t+" + "---+".repeat(width);

        System.out.print("\t ");
        for (int x_axis = 0; x_axis < width; x_axis++) {
            System.out.printf(" %d  ", x_axis + 1);
        }
        System.out.println();

        for (int y = 0; y < height; y++) {
            System.out.println(row_separator);

            System.out.printf("%d\t", y + 1);
            for (int x = 0; x < width; x++) {
                String color = switch (this.grid[x][y]) {
                    case SHIP -> Colors.GREEN;
                    case SHOOT -> Colors.YELLOW;
                    case FLAG -> Colors.RED;
                    default -> Colors.WHITE;
                };

                System.out.printf("| " + color + "%c " + Colors.RESET, this.grid[x][y]);
            }
            System.out.println('|');
        }
        System.out.println(row_separator);
    }
}
