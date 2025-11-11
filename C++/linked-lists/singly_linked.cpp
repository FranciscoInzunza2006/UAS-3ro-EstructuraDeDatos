#include <iostream>

#define SEPARATOR "-------------------------------------------------\n";

class LinkedList
{
    class Node
    {
    public:
        int value;
        Node* next;

        Node(const int v, Node* n) : value(v), next(n)
        {
        }
    };

    Node* head = nullptr;

public:
    ~LinkedList()
    {
        while (head != nullptr)
        {
            const Node* current_node = head;
            head = head->next;
            delete current_node;
        }
    }

    void pushFirst(const int value)
    {
        std::cout << "Se inserto el nodo.\n";
        if (head == nullptr)
        {
            head = new Node(value, nullptr);
            return;
        }

        head = new Node(value, head);
    }

    void pushLast(const int value)
    {
        if (head == nullptr)
        {
            pushFirst(value);
            return;
        }

        Node* tail = head;
        while (tail->next != nullptr)
        {
            tail = tail->next;
        }
        tail->next = new Node(value, nullptr);
        std::cout << "Se inserto el nodo.\n";
    }

    void pushAt(const int value, const int index)
    {
        if (index == 0)
        {
            pushFirst(value);
            return;
        }

        if (head == nullptr)
        {
            std::cout << "No se pudo insertar el nodo.\n";
            return;
        }

        Node* previous_node = nullptr;
        Node* current_node = head;
        for (int i = 0; i < index && current_node != nullptr; i++)
        {
            previous_node = current_node;
            current_node = current_node->next;
        }

        if (previous_node == nullptr || (current_node == nullptr && index > 0))
        {
            std::cout << "No se pudo insertar el nodo.\n";
            return;
        }

        std::cout << "Se inserto el nodo.\n";
        previous_node->next = new Node(value, current_node);
    }

    // Pop
    void popFirst()
    {
        if (head == nullptr)
        {
            std::cout << "La lista esta vacia.\n";
            return;
        }

        std::cout << "Se elimino el nodo.\n";

        const Node* ptr = head;
        head = head->next;
        delete ptr;
    }

    void popLast()
    {
        if (head == nullptr)
        {
            std::cout << "La lista esta vacia.\n";
            return;
        }

        std::cout << "Se elimino el nodo.\n";
        if (head->next == nullptr)
        {
            delete head;
            head = nullptr;
            return;
        }

        Node* new_tail = head;
        while (new_tail->next->next != nullptr)
        {
            new_tail = new_tail->next;
        }
        delete new_tail->next;
        new_tail->next = nullptr;
    }

    void popAt(const int index)
    {
        if (head == nullptr)
        {
            std::cout << "La lista esta vacia.\n";
            return;
        }

        if (index == 0)
        {
            popFirst();
            return;
        }

        Node* previous_node = nullptr;
        Node* current_node = head;

        for (int i = 0; i < index && current_node != nullptr; i++)
        {
            previous_node = current_node;
            current_node = current_node->next;
        }

        if (current_node == nullptr)
        {
            std::cout << "No se pudo eliminar el nodo.\n";
            return;
        }

        std::cout << "Se elimino el nodo.\n";
        previous_node->next = current_node->next;
        delete current_node;
    }

    // Extra
    void display() const
    {
        if (head == nullptr)
        {
            std::cout << "La lista esta vacia.\n";
            return;
        }

        const Node* current_node = head;
        while (current_node != nullptr)
        {
            std::cout << current_node->value << ' ';
            current_node = current_node->next;
        }
        std::cout << '\n';
    }

    void search(const int needle) const
    {
        if (head == nullptr)
        {
            std::cout << "La lista esta vacia.\n";
            return;
        }

        bool found = false;
        int i = 0;
        const Node* current_node = head;
        while (current_node != nullptr)
        {
            if (current_node->value == needle)
            {
                found = true;
                std::cout << "El valor esta en el nodo con el indice " << i << '\n';
            }

            current_node = current_node->next;
            i++;
        }

        if (!found)
        {
            std::cout << "El valor buscado no esta en la lista.\n";
        }
    }
};

int main()
{
    auto list = LinkedList();

    int choice = 0;
    do
    {
        std::system("cls");
        std::cout << SEPARATOR;
        std::cout << "Lista enlazada\n";
        std::cout << SEPARATOR;
        list.display();
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

        std::cout << SEPARATOR;

        int val = -1;
        int index = -1;
        switch (choice)
        {
        case 1:
            std::cout << "Ingresa un valor: ";
            std::cin >> val;

            list.pushFirst(val);
            break;
        case 2:
            std::cout << "Ingresa un valor: ";
            std::cin >> val;

            list.pushLast(val);

            break;
        case 3:
            std::cout << "Ingresa un valor: ";
            std::cin >> val;

            std::cout << "Ingresa el indice deseado: ";
            std::cin >> index;

            list.pushAt(val, index);
            break;

        case 4:
            list.popFirst();
            break;

        case 5:
            list.popLast();
            break;
        case 6:
            std::cout << "Ingresa el indice deseado: ";
            std::cin >> index;

            list.popAt(index);
            break;
        case 7:
            std::cout << "Ingresa un valor: ";
            std::cin >> val;

            list.search(val);
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
    }
    while (choice != 8);
}
