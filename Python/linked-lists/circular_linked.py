class Node:
    def __init__(self, value, next=None):
        self.value = value
        self.next = next


class LinkedList:
    def __init__(self):
        self.head = None

    # Push methods
    def pushFirst(self, value):
        print("Se inserto el nodo.")
        if self.head is None:
            self.head = Node(value, None)
            self.head.next = self.head
            return

        new_head = Node(value, self.head)
        self.getTail().next = new_head
        self.head = new_head

    def pushLast(self, value):
        if self.head is None:
            self.pushFirst(value)
            return

        tail = self.head
        while tail.next != self.head:
            tail = tail.next

        tail.next = Node(value, self.head)
        print("Se inserto el nodo.")

    def pushAt(self, value, index):
        if index == 0:
            self.pushFirst(value)
            return

        if self.head is None:
            print("No se pudo insertar el nodo.")
            return

        previous_node = self.head
        current_node = self.head.next
        i = 1
        while i < index and current_node != self.head:
            previous_node = current_node
            current_node = current_node.next
            i += 1

        if i < index:
            print("No se pudo insertar el nodo.")
            return

        print("Se inserto el nodo.")
        previous_node.next = Node(value, current_node)

    # Pop methods
    def popFirst(self):
        if self.head is None:
            print("La lista esta vacia.")
            return

        if self.head.next == self.head:
            self.head = None
            return

        print("Se elimino el nodo.")
        self.getTail().next = self.head.next
        self.head = self.head.next

    def popLast(self):
        if self.head is None:
            print("La lista esta vacia.")
            return

        print("Se elimino el nodo.")
        if self.head.next == self.head:
            self.head = None
            return

        new_tail = self.head
        while new_tail.next.next != self.head:
            new_tail = new_tail.next

        new_tail.next = self.head

    def popAt(self, index):
        if self.head is None:
            print("La lista esta vacia.")
            return

        if index == 0:
            self.popFirst()
            return

        previous_node = self.head
        current_node = self.head.next
        i = 1

        while i < index and current_node != self.head:
            previous_node = current_node
            current_node = current_node.next
            i += 1

        if current_node == self.head or i < index:
            print("No se pudo eliminar el nodo.")
            return

        print("Se elimino el nodo.")
        previous_node.next = current_node.next

    # Display and search methods
    def display(self):
        if self.head is None:
            print("La lista esta vacia.")
            return

        current_node = self.head
        while True:
            print(current_node.value, end=" ")
            current_node = current_node.next
            if current_node == self.head:
                break
        print()

    def search(self, needle):
        if self.head is None:
            print("La lista esta vacia.")
            return

        found = False
        i = 0
        current_node = self.head
        while True:
            if current_node.value == needle:
                found = True
                print(f"El valor esta en el nodo con el indice {i}")

            current_node = current_node.next
            i += 1
            if current_node == self.head:
                break

        if not found:
            print("El valor buscado no esta en la lista.")

    # Utility method
    def getTail(self):
        if self.head is None:
            return None

        tail = self.head
        while tail.next != self.head:
            tail = tail.next

        return tail


# Main program
SEPARATOR = "-------------------------------------------------"
list = LinkedList()
choice = 0

while choice != 8:
    print(SEPARATOR)
    print("Lista circular")
    print(SEPARATOR)
    list.display()
    print(SEPARATOR)
    print("1. Insertar elemento al inicio")
    print("2. Insertar elemento al final")
    print("3. Insertar elemento en una posicion especifica")
    print("4. Eliminar elemento al inicio")
    print("5. Eliminar elemento al final")
    print("6. Eliminar elemento en una posicion especifica")
    print("7. Buscar elemento en la lista")
    print("8. Salir")
    print(SEPARATOR)

    choice = int(input("Ingresa una opcion: "))

    print(SEPARATOR)

    if choice == 1:
        val = int(input("Ingresa un valor: "))
        list.pushFirst(val)
    elif choice == 2:
        val = int(input("Ingresa un valor: "))
        list.pushLast(val)
    elif choice == 3:
        val = int(input("Ingresa un valor: "))
        index = int(input("Ingresa el indice deseado: "))
        list.pushAt(val, index)
    elif choice == 4:
        list.popFirst()
    elif choice == 5:
        list.popLast()
    elif choice == 6:
        index = int(input("Ingresa el indice deseado: "))
        list.popAt(index)
    elif choice == 7:
        val = int(input("Ingresa un valor: "))
        list.search(val)
    elif choice == 8:
        print("Adios.")
    else:
        print("Opcion invalida.")