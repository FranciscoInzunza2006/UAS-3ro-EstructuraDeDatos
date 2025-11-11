
class Node {
    int value;
    Node next;

    Node(int value, Node next) {
        this.value = value;
        this.next = next;
    }
}

class Stack {
    Node stack = null;
    int top = -1;
    int capacity;

    Stack(int capacity) {
        this.capacity = capacity;        
    }

    public boolean push(int value) {
        if (this.isFull()) {
            System.out.println("La pila esta llena.");
            return false;
        }

        final Node node = new Node(value, stack);
        stack = node;
        top++;

        return true;
    }

    public int pop() {
        if (this.isEmpty()) {
            System.out.println("La pila esta vacia.");
            return -1;
        
        }

        final Node top_node = stack;

        int value = top_node.value;
        stack = top_node.next;
        top--;

        return value;        
    }

    public int peek() {
        if (this.isEmpty()) {
            System.out.println("La pila esta vacia.");
            return -1;
        }

        return stack.value;
    }

    public boolean isEmpty() {
        return top == -1;
    }

    public boolean isFull() {
        return top == capacity - 1;
    }
}

class StackList {
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
