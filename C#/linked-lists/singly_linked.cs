LinkedList list = new LinkedList();

int choice = 0;
do
{
    const String SEPARATOR = "-------------------------------------------------";
    Console.WriteLine(SEPARATOR);
    Console.WriteLine("Lista circular");
    Console.WriteLine(SEPARATOR);
    list.display();
    Console.WriteLine(SEPARATOR);
    Console.WriteLine("1. Insertar elemento al finalinicio");
    Console.WriteLine("2. Insertar elemento al final");
    Console.WriteLine("3. Insertar elemento en una posicion especifica");
    Console.WriteLine("4. Eliminar elemento al finalinicio");
    Console.WriteLine("5. Eliminar elemento al final");
    Console.WriteLine("6. Eliminar elemento en una posicion especifica");
    Console.WriteLine("7. Buscar elemento en la lista");
    Console.WriteLine("8. Salir");
    Console.WriteLine(SEPARATOR);

    Console.Write("Ingresa una opcion: ");
    choice = Convert.ToInt32(Console.ReadLine());

    Console.WriteLine(SEPARATOR);
    int val = -1;
    int index = -1;
    switch (choice)
    {
        case 1:
            Console.Write("Ingresa un valor: ");
            val = Convert.ToInt32(Console.ReadLine());

            list.pushFirst(val);
            break;
        case 2:
            Console.Write("Ingresa un valor: ");
            val = Convert.ToInt32(Console.ReadLine());

            list.pushLast(val);

            break;
        case 3:
            Console.Write("Ingresa un valor: ");
            val = Convert.ToInt32(Console.ReadLine());

            Console.Write("Ingresa el indice deseado: ");
            index = Convert.ToInt32(Console.ReadLine());

            list.pushAt(val, index);
            break;

        case 4:
            list.popFirst();
            break;

        case 5:
            list.popLast();
            break;
        case 6:
            Console.Write("Ingresa el indice deseado: ");
            index = Convert.ToInt32(Console.ReadLine());

            list.popAt(index);
            break;
        case 7:
            Console.Write("Ingresa un valor: ");
            val = Convert.ToInt32(Console.ReadLine());

            list.search(val);
            break;

        case 8:
            Console.WriteLine("Adios.");
            break;

        default:
            Console.WriteLine("Opcion invalida.");
            break;
    }
} while (choice != 8);

class LinkedList {
    Node? head = null;

    // Push
    public void pushFirst( int value) {
        Console.WriteLine("Se inserto el nodo.");
        if (head == null) {
            head = new Node(value, null);
            return;
        }

        head = new Node(value, head);
    }

    public void pushLast( int value) {
        if (head == null) {
            pushFirst(value);
            return;
        }

        Node tail = head;
        while (tail.next != null) {
            tail = tail.next;
        }
        tail.next = new Node(value, null);
        Console.WriteLine("Se inserto el nodo.");
    }

    public void pushAt( int value,  int index) {
        if (index == 0) {
            pushFirst(value);
            return;
        }

        if (head == null) {
            Console.WriteLine("No se pudo insertar el nodo.");
            return;
        }

        Node? previous_node = null;
        Node current_node = head;
        for (int i = 0; i < index && current_node != null; i++) {
            previous_node = current_node;
            current_node = current_node.next!;
        }

        if (previous_node == null || (current_node == null && index > 0)) {
            Console.WriteLine("No se pudo insertar el nodo.");
            return;
        }

        Console.WriteLine("Se inserto el nodo.");
        previous_node.next = new Node(value, current_node);
    }

    // Pop
    public void popFirst() {
        if (head == null) {
            Console.WriteLine("La lista esta vacia.");
            return;
        }

        Console.WriteLine("Se elimino el nodo.");
        head = head.next;
    }

    public void popLast() {
        if (head == null) {
            Console.WriteLine("La lista esta vacia.");
            return;
        }

        Console.WriteLine("Se elimino el nodo.");
        if (head.next == null) {
            head = null;
            return;
        }

        Node new_tail = head;
        while (new_tail.next!.next != null) {
            new_tail = new_tail.next;
        }
        new_tail.next = null;
    }

    public void popAt( int index) {
        if (head == null) {
            Console.WriteLine("La lista esta vacia.");
            return;
        }

        if (index == 0) {
            popFirst();
            return;
        }

        Node? previous_node = null;
        Node current_node = head;

        for (int i = 0; i < index && current_node != null; i++) {
            previous_node = current_node;
            current_node = current_node.next!;
        }

        if (current_node == null) {
            Console.WriteLine("No se pudo eliminar el nodo.");
            return;
        }

        Console.WriteLine("Se elimino el nodo.");
        previous_node!.next = current_node.next;
    }

    // Extra
    public void display() {
        if (head == null) {
            Console.WriteLine("La lista esta vacia.");
            return;
        }

        Node current_node = head;
        while (current_node != null) {
            Console.Write( current_node.value + " ");
            current_node = current_node.next!;
        }
        Console.WriteLine();
    }

    public void search( int needle) {
        if (head == null) {
            Console.WriteLine("La lista esta vacia.");
            return;
        }

        bool found = false;
        int i = 0;
        Node current_node = head;
        while (current_node != null) {
            if (current_node.value == needle) {
                found = true;
                Console.WriteLine("El valor esta en el nodo con el indice" + i);
            }

            current_node = current_node.next!;
            i++;
        }

        if (!found) {
            Console.WriteLine("El valor buscado no esta en la lista.");
        }
    }

    // Node definition
    class Node {
        public int value;
        public Node? next;

        public Node(int value, Node? next) {
            this.value = value;
            this.next = next!;
        }
    }
}
