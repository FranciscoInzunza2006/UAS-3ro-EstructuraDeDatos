#include <iostream>

#define SEPARATOR "-------------------------------------------------\n"

int getInt(const char* prompt);

void printSeparator() { std::cout << SEPARATOR; }

class Queue {
    static const int MAX_SIZE = 10;
	int queue[Queue::MAX_SIZE];
    int front = -1;
    int rear = -1;

   public:
	bool enqueue(const int value) {
        if (rear == Queue::MAX_SIZE - 1) {
            std::cout << "La cola esta llena.\n";
            return false;
        }

        if (front == -1 && rear == -1) {
            front = 0;
            rear = 0;
        } else {
            rear++;
        }
        queue[rear] = value;
        std::cout << "Valor insertado correctamente.\n";

		return true;
	}

	int dequeue() {
        if (front == -1 || front > rear) {
			std::cout << "La cola esta vacía.\n";
			return -1;
		}

        int val = queue[front];
        if (front == rear) {
            front = -1;
            rear = -1;
        } else {
            front++;
        }        
        
		std::cout << "Se sacó el valor " << val << " de la cola .\n";

		return val;
	}

	void display() {
        if (front == -1 || front > rear) {
			std::cout << "La cola esta vacía.\n";
			return;
		}

        for (int i = front; i <= rear; i++) {
			std::cout << queue[i] << ' ';			
		}
		std::cout << '\n';
	}
};

int main() {
	auto queue = Queue();

	int option = -1;
	while (option != 3) {
		printSeparator();
		std::cout << "Colas\n";
		printSeparator();
		queue.display();
		printSeparator();
		std::cout << "1. Insertar un elemento\n";
		std::cout << "2. Eliminar un elemento\n";
		std::cout << "3. Salir\n";
		printSeparator();
		option = getInt("Ingresa la opcion deseada: ");
		printSeparator();
		switch (option) {
			case 1:
				queue.enqueue(
					getInt("Ingresa el valor que quieres insertar: "));
				break;

			case 2:
				queue.dequeue();
				break;

			case 3:
				std::cout << "Adiós.\n";
				break;

			default:
				std::cout << "Opción inválida.\n";
				break;
		}
	}

	return 0;
}

int getInt(const char* prompt) {
	std::cout << prompt;
	int value;
	std::cin >> value;
	return value;
}