
class Node {
    constructor(value, next) {
        this.value = value;
        this.next = next;
    }
}

class LinkedList {
    constructor() {
        this.head = null;
    }

    // Push
    pushFirst(value) {
        console.log("Se inserto el nodo.");
        if (this.head == null) {
            this.head = new Node(value, null);
            this.head.next = this.head;
            return;
        }

        let new_head = new Node(value, this.head);
        this.getTail().next = new_head;
        this.head = new_head;
    }

    pushLast(value) {
        if (this.head == null) {
            this.pushFirst(value);
            return;
        }

        let tail = this.head;
        while (tail.next != this.head) {
            tail = tail.next;
        }
        tail.next = new Node(value, this.head);
        console.log("Se inserto el nodo.");
    }

    pushAt(value, index) {
        if (index == 0) {
            this.pushFirst(value);
            return;
        }

        if (this.head == null) {
            console.log("No se pudo insertar el nodo.");
            return;
        }

        let previous_node = this.head;
        let current_node = this.head.next;
        let i = 1;
        while (i < index && current_node != this.head) {
            previous_node = current_node;
            current_node = current_node.next;
            i++;
        }
        if (i < index) {
            console.log("No se pudo insertar el nodo.");
            return;
        }

        console.log("Se inserto el nodo.");
        previous_node.next = new Node(value, current_node);
    }

    // Pop
    popFirst() {
        if (this.head == null) {
            console.log("La lista esta vacia.");
            return;
        }

        if (this.head.next == this.head) {
            this.head = null;
            return;
        }

        console.log("Se elimino el nodo.");
        this.getTail().next = this.head.next;
        this.head = this.head.next;
    }

    popLast() {
        if (this.head == null) {
            console.log("La lista esta vacia.");
            return;
        }

        console.log("Se elimino el nodo.");
        if (this.head.next == this.head) {
            this.head = null;
            return;
        }

        let new_tail = this.head;
        while (new_tail.next.next != this.head) {
            new_tail = new_tail.next;
        }
        new_tail.next = this.head;
    }

    popAt(index) {
        if (this.head == null) {
            console.log("La lista esta vacia.");
            return;
        }

        if (index == 0) {
            this.popFirst();
            return;
        }

        let previous_node = this.head;
        let current_node = this.head.next;
        let i = 1;

        while (i < index && current_node != this.head) {
            previous_node = current_node;
            current_node = current_node.next;
            i++;
        }

        if (current_node == this.head || i < index) {
            console.log("No se pudo eliminar el nodo.");
            return;
        }
        console.log("Se elimino el nodo.");
        previous_node.next = current_node.next;
    }

    // Extra
    display() {
        if (this.head == null) {
            console.log("La lista esta vacia.");
            return;
        }

        let current_node = this.head;
        let output = "";
        do {
            output += current_node.value + " ";
            current_node = current_node.next;
        } while (current_node != this.head);
        console.log(output);
    }

    search(needle) {
        if (this.head == null) {
            console.log("La lista esta vacia.");
            return;
        }

        let found = false;
        let i = 0;
        let current_node = this.head;
        do {
            if (current_node.value == needle) {
                found = true;
                console.log("El valor esta en el nodo con el indice " + i);
            }
            current_node = current_node.next;
            i++;
        } while (current_node != this.head);

        if (!found) {
            console.log("El valor buscado no esta en la lista.");
        }
    }

    // Util
    getTail() {
        if (this.head == null)
            return null;

        let tail = this.head;
        while (tail.next != this.head) {
            tail = tail.next;
        }
        return tail;
    }
}


let list = new LinkedList();

let choice = 0;
do {
    const SEPARATOR = "-------------------------------------------------";
    console.log(SEPARATOR);
    console.log("Lista circular");
    console.log(SEPARATOR);
    list.display();
    console.log(SEPARATOR);
    console.log("1. Insertar elemento al inicio");
    console.log("2. Insertar elemento al final");
    console.log("3. Insertar elemento en una posicion especifica");
    console.log("4. Eliminar elemento al inicio");
    console.log("5. Eliminar elemento al final");
    console.log("6. Eliminar elemento en una posicion especifica");
    console.log("7. Buscar elemento en la lista");
    console.log("8. Salir");
    console.log(SEPARATOR);

    choice = Number(prompt("Ingresa una opcion: "));

    console.log(SEPARATOR);
    let val = -1;
    let index = -1;
    switch (choice) {
        case 1:
            val = Number(prompt("Ingresa un valor: "));
            list.pushFirst(val);
            break;
        case 2:
            val = Number(prompt("Ingresa un valor: "));
            list.pushLast(val);
            break;
        case 3:
            val = Number(prompt("Ingresa un valor: "));
            index = Number(prompt("Ingresa el indice deseado: "));
            list.pushAt(val, index);
            break;
        case 4:
            list.popFirst();
            break;
        case 5:
            list.popLast();
            break;
        case 6:
            index = Number(prompt("Ingresa el indice deseado: "));
            list.popAt(index);
            break;
        case 7:
            val = Number(prompt("Ingresa un valor: "));
            list.search(val);
            break;
        case 8:
            console.log("Adios.");
            break;
        default:
            console.log("Opcion invalida.");
            break;
    }
} while (choice != 8);
