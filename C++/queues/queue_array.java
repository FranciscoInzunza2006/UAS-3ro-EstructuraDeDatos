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
            option = getInt("Ingresa la opcion deseada: ");
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

        scanner.close();
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
    public static final int MAX_SIZE = 10;
    int[] queue = new int[MAX_SIZE];
    int front = -1;
    int rear = -1;

    public boolean enqueue(final int value) {
        if (rear == MAX_SIZE - 1) {
            System.out.println("La cola esta llena.");
            return false;
        }

        if (front == -1 && rear == -1) {
            front = 0;
            rear = 0;
        } else {
            rear++;
        }
        queue[rear] = value;
        System.out.println("Valor insertado correctamente.");

        return true;
    }

    public int dequeue() {
        if (front == -1 || front > rear) {
            System.out.println("La cola esta vacía.");
            return -1;
        }

        int val = queue[front];
        if (front == rear) {
            front = -1;
            rear = -1;
        } else {
            front++;
        }
        System.err.printf("Se sacó el valor %d de la cola .\n", val);

        return val;
    }

    public void display() {
        if (front == -1 || front > rear) {
            System.out.println("La cola esta vacía.");
            return;
        }

        for (int i = front; i <= rear; i++) {
            System.out.printf("%d ", queue[i]);
        }
        System.out.println();
    }
}