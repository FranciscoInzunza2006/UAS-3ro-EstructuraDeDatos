def getInt(prompt):
    return int(input(prompt))


def printSeparator():
    print("-------------------------------------------------")


class Queue:
    class Node:
        # noinspection PyShadowingBuiltins
        def __init__(self, value, next):
            self.value = value
            self.next = next

    def __init__(self):
        self.queue = None

    def enqueue(self, value):
        if self.queue is None:
            self.queue = self.Node(value, None)
            return True

        tail = self.queue
        while tail.next is not None: tail = tail.next
        tail.next = self.Node(value, None)

        return True

    def dequeue(self):
        if self.queue is None:
            print("La cola esta vacía.")
            return -1

        val = self.queue.value
        self.queue = self.queue.next
        print("Se sacó el valor" + str(val) + "de la cola .")

        return val

    def display(self):
        if self.queue is None:
            print("La cola esta vacía.")
            return

        current_node = self.queue
        while current_node is not None:
            print(current_node.value, end=" ")
            current_node = current_node.next

        print()


# Driver code
if __name__ == '__main__':
    queue = Queue()

    option = -1
    while option != 3:
        printSeparator()
        print("Colas")
        printSeparator()
        queue.display()
        printSeparator()
        print("1. Insertar un elemento")
        print("2. Eliminar un elemento")
        print("3. Salir")
        printSeparator()
        option = getInt("Ingresa la opción deseada: ")
        printSeparator()
        match option:
            case 1:
                queue.enqueue(getInt("Ingresa el valor que quieres insertar: "))

            case 2:
                queue.dequeue()

            case 3:
                print("Adiós.")

            case _:
                print("Opción inválida.")
