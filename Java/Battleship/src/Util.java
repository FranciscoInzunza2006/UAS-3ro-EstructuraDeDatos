import java.util.Scanner;

public abstract class Util {
    public static final Scanner SCANNER = new Scanner(System.in);
    static final String SEPARATOR = "-".repeat(32);

    static void clearConsole() {
        printSection("Battleship");
    }

    static void printSection() {
        System.out.println(SEPARATOR);
    }

    static void printSection(String section) {
        printSection();
        System.out.println("\t" + section);
    }

    static void printSection(String[] sections) {
        printSection();
        for (String s : sections) {
            System.out.println("\t" + s);
        }
    }

    static int get_int_range(final int min, final int max) {
        int n;
        while (true) {
            n = SCANNER.nextInt();
            if (n < min || n > max) {
                System.out.printf("Valor fuera de rango %s-%s\nIngresa otro valor: ", min, max);
                continue;
            }

            return n;
        }
    }
}
