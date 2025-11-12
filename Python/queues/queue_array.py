def getInt(prompt):
    return int(input(prompt))


def printSeparator():
    print("-------------------------------------------------")


class Queue:
    MAX_SIZE = 100

    def __init__(self):
        self.queue = [0] * Queue.MAX_SIZE
        self.front = -1
        self.rear = -1

    def enqueue(self, value):
        if self.rear == Queue.MAX_SIZE - 1:
            print("La cola esta llena.")
            return False

        if self.front == -1 and self.rear == -1:
            self.front = 0
            self.rear = 0
        else:
            self.rear += 1

        self.queue[self.rear] = value
        print("Valor insertado correctamente.")

        return True

    def dequeue(self):
        if self.front == -1 or self.front > self.rear:
            print("La cola esta vacía.")
            return -1

        val = self.queue[self.front]
        if self.front == -1 and self.rear == -1:
            self.front = 0
            self.rear = 0
        else:
            self.front += 1

        print("Se sacó el valor" + str(val) + "de la cola .")

        return val

    def display(self):
        if self.front == -1 or self.front > self.rear:
            print("La cola esta vacía.")
            return

        i = self.front
        while i <= self.rear:
            print(self.queue[i], end=" ")
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
