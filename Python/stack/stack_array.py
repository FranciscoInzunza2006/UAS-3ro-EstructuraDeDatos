class Stack:
    def __init__(self, capacity):
        self.capacity = capacity
        self.stack = [0] * capacity
        self.top = -1

    def push(self, value):
        if self.isFull():
            print("La pila esta llena.")
            return False

        self.top += 1
        self.stack[self.top] = value
        return True

    def pop(self):
        if self.isEmpty():
            print("La pila esta vacia.")
            return -1

        val = self.stack[self.top]
        self.top -= 1
        return val

    def peek(self):
        if self.isEmpty():
            print("La pila esta vacia.")
            return -1

        return self.stack[self.top]

    def isEmpty(self):
        return self.top == -1

    def isFull(self):
        return self.top == self.capacity - 1


stack = Stack(5)
stack.push(10)
stack.push(20)
stack.push(30)

print("Elemento superior: " + str(stack.pop()))
print("Elemento superior (sin extraer): " + str(stack.peek()))
print("Elemento superior (extraido): " + str(stack.pop()))
print("Ultimo elemento: " + str(stack.pop()))
