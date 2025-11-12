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
    class Node {
        public int value;
        public Node next;

        public Node(int value, Node next) {
            this.value = value;
            this.next = next;
        }
    }
    Node queue = null;

    public boolean enqueue(final int value) {
        if (queue == null) {
            queue = new Node(value, null);
            return true;
        }

        Node tail = queue;
        while (tail.next != null)
            tail = tail.next;
        tail.next = new Node(value, null);

        return true;
    }

    public int dequeue() {
        if (queue == null) {
            System.out.println("La cola esta vacía.");
            return -1;
        }

        int val = queue.value;
        queue = queue.next;
        System.err.printf("Se sacó el valor %d de la cola .\n", val);

        return val;
    }

    public void display() {
        if (queue == null) {
            System.out.println("La cola esta vacía.");
            return;
        }

        Node current_node = queue;
        while (current_node != null) {
            System.out.printf("%d ", current_node.value);
            current_node = current_node.next;
        }
        System.out.println();
    }
}