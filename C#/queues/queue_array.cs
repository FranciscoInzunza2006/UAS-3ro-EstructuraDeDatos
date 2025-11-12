
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
    public const int MAX_SIZE = 10;
    int[] queue = new int[MAX_SIZE];
    int front = -1;
    int rear = -1;

    public bool enqueue(int value)
    {
        if (rear == MAX_SIZE - 1)
        {
            Console.WriteLine("La cola esta llena.");
            return false;
        }

        if (front == -1 && rear == -1)
        {
            front = 0;
            rear = 0;
        }
        else
        {
            rear++;
        }
        queue[rear] = value;
        Console.WriteLine("Valor insertado correctamente.");

        return true;
    }

    public int dequeue()
    {
        if (front == -1 || front > rear)
        {
            Console.WriteLine("La cola esta vacía.");
            return -1;
        }

        int val = queue[front];
        if (front == rear)
        {
            front = -1;
            rear = -1;
        }
        else
        {
            front++;
        }
        Console.WriteLine("Se sacó el valor" + val + "de la cola .");

        return val;
    }

    public void display()
    {
        if (front == -1 || front > rear)
        {
            Console.WriteLine("La cola esta vacía.");
            return;
        }

        for (int i = front; i <= rear; i++)
        {
            Console.Write(queue[i] + " ");
        }
        Console.WriteLine();
    }
}