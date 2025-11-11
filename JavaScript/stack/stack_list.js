class Node {
    constructor(value, next) {
        this.value = value;
        this.next = next;
    }
}

class Stack {
    constructor(capacity) {
        this.capacity = capacity;
        this.stack = null;
        this.top = -1;
    }

    push(value) {
        if (this.isFull()) {
            console.log("La pila esta llena.");
            return false;
        }

        this.stack = new Node(value, this.stack);
        this.top += 1;

        return true;
    }

    pop() {
        if (this.isEmpty()) {
            console.log("La pila esta vacia.");
            return -1;
        }

        let val = this.stack.value;
        this.stack = this.stack.next;
        this.top -= 1;

        return val;
    }

    peek() {
        if (this.isEmpty()) {
            console.log("La pila esta vacia.");
            return -1;
        }

        return this.stack.value;
    }

    isEmpty() {
        return this.top === -1;
    }

    isFull() {
        return this.top === this.capacity - 1;
    }
}


let stack = new Stack(10);
stack.push(5);
stack.push(20);
stack.push(30);

console.log("Elemento superior: " + stack.pop());
console.log("Elemento superior (sin extraer): " + stack.peek());
console.log("Elemento superior (extraido): " + stack.pop());
console.log("Ultimo elemento: " + stack.pop());
