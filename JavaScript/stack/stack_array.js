class Stack {
    constructor(capacity) {
        this.capacity = capacity;
        this.stack = [];
        this.top = -1;
    }

    push(value) {
        if (this.isFull()) {
            console.log("La pila esta llena.");
            return false;
        }

        this.top += 1;
        this.stack[this.top] = value;
        return true;
    }

    pop() {
        if (this.isEmpty()) {
            console.log("La pila esta vacia.");
            return -1;
        }

        let val = this.stack[this.top];
        this.top -= 1;
        return val;
    }

    peek() {
        if (this.isEmpty()) {
            console.log("La pila esta vacia.");
            return -1;
        }

        return this.stack[this.top];
    }

    isEmpty() {
        return this.top === -1;
    }

    isFull() {
        return this.top === this.capacity - 1;
    }
}


let stack = new Stack(10);
stack.push(10);
stack.push(20);
stack.push(30);

console.log("Elemento superior: " + stack.pop());
console.log("Elemento superior (sin extraer): " + stack.peek());
console.log("Elemento superior (extraido): " + stack.pop());
console.log("Ultimo elemento: " + stack.pop());
