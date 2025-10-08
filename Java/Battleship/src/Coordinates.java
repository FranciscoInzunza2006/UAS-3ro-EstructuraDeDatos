public class Coordinates {
    int x;
    int y;

    Coordinates(int x, int y) {
        this.x = x;
        this.y = y;
    }

    static Coordinates askUser(int width, int height) {
        Util.printSection();
        System.out.print("X: ");
        int x = Util.get_int_range(1, width) - 1;

        System.out.print("Y: ");
        int y = Util.get_int_range(1, height) - 1;

        return new Coordinates(x, y);
    }
}