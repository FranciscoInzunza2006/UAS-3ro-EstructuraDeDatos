#include <iostream>

#define SEPARATOR "-------------------------------------------------\n"

int getInt(const char* prompt);

void printSeparator() { std::cout << SEPARATOR; }

class Queue {
	struct Node {
		int value;
		Node* next;

		Node(int value, Node* next) : value(value), next(next) {}
	};
	Node* queue = nullptr;

   public:
	bool enqueue(const int value) {
		if (queue == nullptr) {
			queue = new Node(value, nullptr);
			return true;
		}

		Node* tail = queue;
		while (tail->next != nullptr) tail = tail->next;
		tail->next = new Node(value, nullptr);

		return true;
	}

	int dequeue() {
		if (queue == nullptr) {
			std::cout << "La cola esta vacía.\n";
			return -1;
		}

		const int val = queue->value;
        const Node* front = queue;                
		queue = queue->next;
        delete front;
        
		std::cout << "Se sacó el valor " << val << " de la cola .\n";

		return val;
	}

	void display() {
		if (queue == nullptr) {
			std::cout << "La cola esta vacía.\n";
			return;
		}

		Node* current_node = queue;
		while (current_node != nullptr) {
			std::cout << current_node->value << ' ';
			current_node = current_node->next;
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