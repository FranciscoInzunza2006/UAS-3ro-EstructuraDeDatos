#include <iostream>

struct Node {
	int value{};
	Node* next{};
	Node* previous{};

	explicit Node(const int value, Node* next = nullptr,
				  Node* previous = nullptr) {
		this->value = value;
		this->next = next;
		this->previous = previous;
	}
};

void pushFirst();
void pushLast();
void pushAt();

void popFirst();
void popLast();
void popAt();

void displayList();
void searchInList();

Node* head = nullptr;

int main() {
	int choice = 0;
	do {
		std::system("cls");

		constexpr auto SEPARATOR =
			"-------------------------------------------------\n";
		std::cout << SEPARATOR;
		std::cout << "Menu de listas enlazadas dobles circulares\n";
		std::cout << SEPARATOR;
		displayList();
		std::cout << SEPARATOR;
		std::cout << "1. Insertar elemento al inicio\n";
		std::cout << "2. Insertar elemento al final\n";
		std::cout << "3. Insertar elemento en una posicion especifica\n";
		std::cout << "4. Eliminar elemento al inicio\n";
		std::cout << "5. Eliminar elemento al final\n";
		std::cout << "6. Eliminar elemento en una posicion especifica\n";
		std::cout << "7. Buscar elemento en la lista\n";
		std::cout << "8. Salir\n";
		std::cout << SEPARATOR;

		std::cout << "Ingresa una opcion: ";
		std::cin >> choice;
		switch (choice) {
			case 1:
				pushFirst();
				break;
			case 2:
				pushLast();
				break;
			case 3:
				pushAt();
				break;
			case 4:
				popFirst();
				break;
			case 5:
				popLast();
				break;
			case 6:
				popAt();
				break;
			case 7:
				searchInList();
				break;
			case 8:
				std::cout << "Adios.\n";
				break;
			default:
				std::cout << "Opcion invalida.\n";
				break;
		}

		std::cout << SEPARATOR;
		std::system("pause");
	} while (choice != 8);

	while (head != nullptr) popFirst();

	return 0;
}

void pushFirst() {
	std::cout << "Ingresa el valor a insertar: ";
	int value;
	std::cin >> value;

	if (head == nullptr) {
		head = new Node(value);
		return;
	}

	Node* new_node = new Node(value, head);
	head->previous = new_node;
	head = new_node;

	std::cout << "Se inserto el nodo.\n";
}

void pushLast() {
	if (head == nullptr) {
		pushFirst();
		return;
	}

	std::cout << "Ingresa el valor a insertar: ";
	int value;
	std::cin >> value;

	Node* tail = head;
	while (tail->next != nullptr) {
		tail = tail->next;
	}
	tail->next = new Node(value, nullptr, tail);

	std::cout << "Se inserto el nodo.\n";
}

void pushAt() {
	std::cout << "Ingresa el valor a insertar: ";
	int value;
	std::cin >> value;

	std::cout << "Ingresa en que posicion (empieza por 0): ";
	int target_position;
	std::cin >> target_position;

	Node* ptr = head;
	int i = 0;
	while (ptr != nullptr && i < target_position) {
		ptr = ptr->next;
		i++;
	}

	if (ptr == nullptr || i < target_position) {
		std::cout << "No se pudo insertar el valor.\n";
		return;
	}

	Node* new_node = new Node(value, ptr, ptr->previous);
    if (ptr->previous != nullptr) {
        ptr->previous->next = new_node;
	    ptr->previous = new_node;
    }
	    
	std::cout << "Se inserto el nodo.\n";
}

void popFirst() {
	if (head == nullptr) {
		std::cout << "La lista esta vacia.\n";
		return;
	}

	std::cout << "Se elimino el nodo.\n";

	Node* temp = head;
	if (head->next == nullptr) {
		head = nullptr;
	} else {
		head = head->next;
		head->previous = nullptr;
	}

	delete temp;
}

void popLast() {
	if (head == nullptr) {
		std::cout << "La lista esta vacia.\n";
		return;
	}

	std::cout << "Se elimino el nodo.\n";
	if (head->next == nullptr) {
		delete head;
		head = nullptr;
		return;
	}

	Node* tail = head;
	while (tail->next != nullptr) {
		tail = tail->next;
	}
	tail->previous->next = nullptr;

	delete tail;
}

void popAt() {
	if (head == nullptr) {
		std::cout << "La lista esta vacia.\n";
		return;
	}

	std::cout << "Ingresa en que posicion (empieza por 0): ";
	int target_position;
	std::cin >> target_position;

	if (target_position == 0) {
		popFirst();
		return;
	}

	Node* ptr = head;
	int i = 0;
	while (ptr != nullptr && i < target_position) {
		ptr = ptr->next;
		i++;
	}

	if (ptr == nullptr) {
		std::cout << "No se pudo eliminar el elemento.\n";
		return;
	}

	if (ptr->next == nullptr) {
		popLast();
		return;
	}

	ptr->previous->next = ptr->next;
	ptr->next->previous = ptr->previous;

	delete ptr;
	std::cout << "Se elimino el nodo.\n";
}

void displayList() {
	if (head == nullptr) {
		std::cout << "La lista esta vacia.\n";
		return;
	}

	const Node* ptr = head;
	while (ptr != nullptr) {
		std::cout << ptr->value << ' ';
		ptr = ptr->next;
	}
	std::cout << '\n';
}

void searchInList() {
	if (head == nullptr) {
		std::cout << "La lista esta vacia.\n";
		return;
	}

	std::cout << "Ingresa el valor a buscar: ";
	int needle;
	std::cin >> needle;

	int i = 0;
	bool found = false;
	const Node* ptr = head;
	while (ptr != nullptr) {
		if (ptr->value == needle) {
			found = true;
			std::cout << "Elemento encontrado en la posicion " << i << ".\n";
		}

		ptr = ptr->next;
		i++;
	}

	if (!found) std::cout << "Elemento no encontrado.\n";
}
