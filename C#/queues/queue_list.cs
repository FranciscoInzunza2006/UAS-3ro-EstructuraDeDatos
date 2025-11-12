
Queue queue = new Queue();

int option = -1;
while (option != 3)
{
    printSeparator();
    Console.WriteLine("Colas");
    printSeparator();
    queue.display();
    printSeparator();
    Console.WriteLine("1. Insertar un elemento");
    Console.WriteLine("2. Eliminar un elemento");
    Console.WriteLine("3. Salir");
    printSeparator();
    option = getInt("Ingresa la opcion deseada: ");
    printSeparator();
    switch (option)
    {
        case 1:
            queue.enqueue(getInt("Ingresa el valor que quieres insertar: "));
            break;

        case 2:
            queue.dequeue();
            break;

        case 3:
            Console.WriteLine("Adiós.");
            break;

        default:
            Console.WriteLine("Opción inválida.");
            break;
    }
}

int getInt(string prompt)
{
    Console.Write(prompt);
    return Convert.ToInt32(Console.ReadLine());
}

void printSeparator()
{
    const string SEPARATOR = "-------------------------------------------------";
    Console.WriteLine(SEPARATOR);
}


class Queue
{
    class Node
    {
        public int value;
        public Node? next;

        public Node(int value, Node? next)
        {
            this.value = value;
            this.next = next;
        }
    }
    private Node? queue = null;


    public bool enqueue(int value)
    {
        if (queue == null)
        {
            queue = new Node(value, null);
            return true;
        }

        Node tail = queue;
        while (tail.next != null)
            tail = tail.next;
        tail.next = new Node(value, null);

        return true;
    }

    public int dequeue()
    {
        if (queue == null)
        {
            Console.WriteLine("La cola esta vacía.");
            return -1;
        }

        int val = queue.value;
        queue = queue.next;
        Console.WriteLine("Se sacó el valor" + val + "de la cola .");

        return val;
    }

    public void display()
    {
        if (queue == null)
        {
            Console.WriteLine("La cola esta vacía.");
            return;
        }

        Node current_node = queue;
        while (current_node != null)
        {
            Console.Write(current_node.value + " ");
            current_node = current_node.next!;
        }
        Console.WriteLine();
    }
}