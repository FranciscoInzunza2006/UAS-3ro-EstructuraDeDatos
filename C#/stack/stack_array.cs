
Stack stack = new(10);
stack.push(10);
stack.push(20);
stack.push(30);

Console.WriteLine("Elemento superior: " + stack.pop());
Console.WriteLine("Elemento superior (sin extraer): " + stack.peek().ToString());
Console.WriteLine("Elemento superior (extraido): " + stack.pop().ToString());
Console.WriteLine("Ultimo elemento: " + stack.pop().ToString());


class Stack(int capacity)
{
    int[] stack = new int[capacity];
    int top = -1;
    int capacity = capacity;

    public bool push(int value)
    {
        if (isFull())
        {
            Console.WriteLine("La pila esta llena.");
            return false;
        }

        stack[++top] = value;
        return true;
    }

    public int pop()
    {
        if (isEmpty())
        {
            Console.WriteLine("La pila esta vacia.");
            return -1;
        }

        return stack[top--];
    }

    public int peek()
    {
        if (isEmpty())
        {
            Console.WriteLine("La pila esta vacia.");
            return -1;
        }

        return stack[top];
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


