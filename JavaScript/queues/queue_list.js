function getInt(prompt) {
    return Number(window.prompt(prompt));
}

function printSeparator() {
    const SEPARATOR = "-------------------------------------------------";
    console.log(SEPARATOR);
}

class Queue {
    constructor() {
        this.queue = null;
    }

    enqueue(value) {
        if (this.queue == null) {
            this.queue = new Node(value, null);
            return true;
        }

        let tail = this.queue;
        while (tail.next != null) tail = tail.next;
        tail.next = new Node(value, null);

        return true;
    }

    dequeue() {
        if (this.queue == null) {
            console.log("La cola esta vacía.");
            return -1;
        }

        let val = this.queue.value;
        this.queue = this.queue.next;
        console.log("Se sacó el valor" + val + "de la cola .");

        return val;
    }

    display() {
        if (this.queue == null) {
            console.log("La cola esta vacía.");
            return;
        }

        let current_node = this.queue;
        while (current_node != null) {
            console.log(current_node.value + " ");
            current_node = current_node.next;
        }
        console.log();
    }
}

class Node {
    constructor(value, next) {
        this.value = value;
        this.next = next;
    }
}

// Driver code
let queue = new Queue();

let option = -1;
while (option != 3) {
    printSeparator();
    console.log("Colas");
    printSeparator();
    queue.display();
    printSeparator();
    console.log("1. Insertar un elemento");
    console.log("2. Eliminar un elemento");
    console.log("3. Salir");
    printSeparator();
    option = getInt("Ingresa la opcion deseada: ");
    printSeparator();
    switch (option) {
        case 1:
            queue.enqueue(getInt("Ingresa el valor que quieres insertar: "));
            break;

        case 2:
            queue.dequeue();
            break;

        case 3:
            console.log("Adiós.");
            break;

        default:
            console.log("Opción inválida.");
            break;
    }
}
