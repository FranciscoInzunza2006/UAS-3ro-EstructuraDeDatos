function getInt(prompt) {
    return Number(window.prompt(prompt));
}

function printSeparator() {
    const SEPARATOR = "-------------------------------------------------";
    console.log(SEPARATOR);
}

class Queue {
    static MAX_SIZE = 100;
    constructor() {
        this.queue = new Array(Queue.MAX_SIZE);
        this.front = -1;
        this.rear = -1;
    }

    enqueue(value) {
        if (rear == Queue.MAX_SIZE - 1) {
            console.log("La cola esta llena.");
            return false;
        }

        if (this.front == -1 && this.rear == -1) {
            this.front = 0;
            this.rear = 0;
        } else {
            this.rear++;
        }
        this.queue[this.rear] = value;
        console.log("Valor insertado correctamente.");

        return true;
    }

    dequeue() {
        if (this.front == -1 || this.front > this.rear) {
            console.log("La cola esta vacía.");
            return -1;
        }

        let val = this.queue[this.front];
        if (this.front == this.rear) {
            this.front = -1;
            this.rear = -1;
        } else {
            this.front++;
        }
        console.log(`Se sacó el valor ${val} de la cola .\n`);


        return val;
    }

    display() {
        if (this.front == -1 || this.front > this.rear) {
            console.log("La cola esta vacía.");
            return;
        }

        for (let i = this.front; i <= this.rear; i++) {
            console.log(`${this.queue[i]} `);
        }
        console.log();
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
