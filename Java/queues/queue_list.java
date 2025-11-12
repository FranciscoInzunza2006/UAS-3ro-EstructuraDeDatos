import java.util.Scanner;

abstract class DriverCode {
    static final String SEPARATOR = "-------------------------------------------------";
    static final Scanner scanner = new Scanner(System.in);

    public static void main(String[] args) {
        Queue queue = new Queue();

        int option = -1;
        while (option != 3) {
            printSeparator();
            System.out.println("Colas");
            printSeparator();
            queue.display();
            printSeparator();
            System.out.println("1. Insertar un elemento");
            System.out.println("2. Eliminar un elemento");
            System.out.println("3. Salir");
            printSeparator();

            switch (option) {
                case 1:
                    queue.enqueue(getInt("Ingresa el valor que quieres insertar: "));
                    break;

                case 2:
                    queue.dequeue();
                    break;

                case 3:
                    System.out.println("Adiós.");
                    break;

                default:
                    System.out.println("Opción inválida.");
                    break;
            }
        }
    }

    private static int getInt(final String prompt) {
        System.out.print(prompt);
        return scanner.nextInt();
    }

    private static void printSeparator() {
        System.out.println(SEPARATOR);
    }
}

class Queue {    
    class Node {
        int value;
        Node next;
    }
    Node queue = null;

    public boolean enqueue(final int val) {

        return true;
    }

    public boolean dequeue() {
        return true;
    }

    public void display() {

    }
}