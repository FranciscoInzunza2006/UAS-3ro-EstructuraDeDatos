import java.util.Scanner;

class DriverCode {
    static final String SEPARATOR = "-------------------------------------------------";

    public static void main(String[] args) {
        LinkedList list = new LinkedList();

        Scanner sc = new Scanner(System.in);
        int choice = 0;
        do {
            System.out.println(SEPARATOR);
            System.out.println("Lista circular");
            System.out.println(SEPARATOR);
            list.display();
            System.out.println(SEPARATOR);
            System.out.println("1. Insertar elemento al inicio");
            System.out.println("2. Insertar elemento al final");
            System.out.println("3. Insertar elemento en una posicion especifica");
            System.out.println("4. Eliminar elemento al inicio");
            System.out.println("5. Eliminar elemento al final");
            System.out.println("6. Eliminar elemento en una posicion especifica");
            System.out.println("7. Buscar elemento en la lista");
            System.out.println("8. Salir");
            System.out.println(SEPARATOR);

            System.out.print("Ingresa una opcion: ");
            choice = sc.nextInt();

            System.out.println(SEPARATOR);
            int val = -1;
            int index = -1;
            switch (choice) {
                case 1:
                    System.out.print("Ingresa un valor: ");
                    val = sc.nextInt();

                    list.pushFirst(val);
                    break;
                case 2:
                    System.out.print("Ingresa un valor: ");
                    val = sc.nextInt();

                    list.pushLast(val);

                    break;
                case 3:
                    System.out.print("Ingresa un valor: ");
                    val = sc.nextInt();

                    System.out.print("Ingresa el indice deseado: ");
                    index = sc.nextInt();

                    list.pushAt(val, index);
                    break;

                case 4:
                    list.popFirst();
                    break;

                case 5:
                    list.popLast();
                    break;
                case 6:
                    System.out.print("Ingresa el indice deseado: ");
                    index = sc.nextInt();

                    list.popAt(index);
                    break;
                case 7:
                    System.out.print("Ingresa un valor: ");
                    val = sc.nextInt();

                    list.search(val);
                    break;

                case 8:
                    System.out.println("Adios.");
                    break;

                default:
                    System.out.println("Opcion invalida.");
                    break;
            }
        } while (choice != 8);

        sc.close();
    }
}

class LinkedList {
    Node head = null;

    // Push
    public void pushFirst(final int value) {
        System.out.println("Se inserto el nodo.");
        if (head == null) {
            head = new Node(value, null);
            head.next = head;

            return;
        }
    
        Node new_head = new Node(value, head);        
        getTail().next = new_head;
        head = new_head;
    }

    public void pushLast(final int value) {
        if (head == null) {
            pushFirst(value);
            return;
        }

        Node tail = head;
        while (tail.next != head) {
            tail = tail.next;
        }
        tail.next = new Node(value, head);
        System.out.println("Se inserto el nodo.");
    }

    public void pushAt(final int value, final int index) {
        if (index == 0) {
            pushFirst(value);
            return;
        }

        if (head == null) {
            System.out.println("No se pudo insertar el nodo.");
            return;
        }

        Node previous_node = head;
        Node current_node = head.next;
        int i = 1;
        while (i < index && current_node != head) {
            previous_node = current_node;
            current_node = current_node.next;
            i++;
        }
        if (i < index) {
            System.out.println("No se pudo insertar el nodo.");
            return;
        }

        System.out.println("Se inserto el nodo.");
        previous_node.next = new Node(value, current_node);
    }

    // Pop
    public void popFirst() {
        if (head == null) {
            System.out.println("La lista esta vacia.");
            return;
        }

        if (head.next == head) {
            head = null;
            return;
        }

        System.out.println("Se elimino el nodo.");
        getTail().next = head.next;
        head = head.next;
    }

    public void popLast() {
        if (head == null) {
            System.out.println("La lista esta vacia.");
            return;
        }

        System.out.println("Se elimino el nodo.");
        if (head.next == head) {
            head = null;
            return;
        }

        Node new_tail = head;
        while (new_tail.next.next != head) {
            new_tail = new_tail.next;
        }
        new_tail.next = head;
    }

    public void popAt(final int index) {
        if (head == null) {
            System.out.println("La lista esta vacia.");
            return;
        }

        if (index == 0) {
            popFirst();
            return;
        }

        Node previous_node = head;
        Node current_node = head.next;
        int i = 1;

        while (i < index && current_node != head) {
            previous_node = current_node;
            current_node = current_node.next;
            i++;
        }

        if (current_node == head || i < index) {
            System.out.println("No se pudo eliminar el nodo.");
            return;
        }
        System.out.println("Se elimino el nodo.");
        previous_node.next = current_node.next;
    }

    // Extra
    public void display() {
        if (head == null) {
            System.out.println("La lista esta vacia.");
            return;
        }

        Node current_node = head;
        do {
            System.out.printf("%d ", current_node.value);
            current_node = current_node.next;
        } while (current_node != head);
        System.out.println();
    }

    public void search(final int needle) {
        if (head == null) {
            System.out.println("La lista esta vacia.");
            return;
        }

        boolean found = false;
        int i = 0;
        Node current_node = head;
        do {
            if (current_node.value == needle) {
                found = true;
                System.out.printf("El valor esta en el nodo con el indice %d\n", i);
            }

            current_node = current_node.next;
            i++;
        } while (current_node != head);

        if (!found) {
            System.out.println("El valor buscado no esta en la lista.");
        }
    }

    // Util
    private Node getTail() {
        if (head == null)
            return null;

        Node tail = head;
        while (tail.next != head) {
            tail = tail.next;
        }

        return tail;
    }

    // Node definition
    class Node {
        public int value;
        public Node next;

        public Node(int value, Node next) {
            this.value = value;
            this.next = next;
        }
    }
}
