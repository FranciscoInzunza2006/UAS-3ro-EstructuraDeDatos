
class Stack {
    int[] stack;
    int top = -1;
    int capacity;

    Stack(int capacity) {
        this.capacity = capacity;
        this.stack = new int[capacity];
    }

    public boolean push(int value) {
        if (this.isFull()) {
            System.out.println("La pila esta llena.");
            return false;
        }

        stack[++top] = value;
        return true;
    }

    public int pop() {
        if (this.isEmpty()) {
            System.out.println("La pila esta vacia.");
            return -1;
        }

        return stack[top--];
    }

    public int peek() {
        if (this.isEmpty()) {
            System.out.println("La pila esta vacia.");
            return -1;
        }

        return stack[top];
    }

    public boolean isEmpty() {
        return top == -1;
    }

    public boolean isFull() {
        return top == capacity - 1;
    }
}

class StackArray {
    public static void main(String[] args) {
        Stack stack = new Stack(10);
        stack.push(10);
        stack.push(20);
        stack.push(30);

        System.out.println("Elemento superior: " + Integer.toString(stack.pop()));
        System.out.println("Elemento superior (sin extraer): " + Integer.toString(stack.peek()));
        System.out.println("Elemento superior (extraido): " + Integer.toString(stack.pop()));
        System.out.println("Ultimo elemento: " + Integer.toString(stack.pop()));
    }
}
