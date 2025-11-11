
Stack stack = new(10);
stack.push(10);
stack.push(20);
stack.push(30);

Console.WriteLine("Elemento superior: " + stack.pop());
Console.WriteLine("Elemento superior (sin extraer): " + stack.peek());
Console.WriteLine("Elemento superior (extraido): " + stack.pop());
Console.WriteLine("Ultimo elemento: " + stack.pop());


class Node(int value, Node next)
{
    public int value = value;
    public Node next = next;
}

class Stack(int capacity)
{
#nullable enable
    Node? stack = null;
#nullable disable
    int top = -1;
    int capacity = capacity;

    public bool push(int value)
    {
        if (isFull())
        {
            Console.WriteLine("La pila esta llena.");
            return false;
        }

        Node node = new Node(value, stack);
        stack = node;
        top++;

        return true;
    }

    public int pop()
    {
        if (isEmpty())
        {
            Console.WriteLine("La pila esta vacia.");
            return -1;

        }

        Node top_node = stack;

        int value = top_node.value;
        stack = top_node.next;
        top--;

        return value;
    }

    public int peek()
    {
        if (isEmpty())
        {
            Console.WriteLine("La pila esta vacia.");
            return -1;
        }

        return stack.value;
    }

    public bool isEmpty()
    {
        return top == -1;
    }

    public bool isFull()
    {
        return top == capacity - 1;
    }
}


