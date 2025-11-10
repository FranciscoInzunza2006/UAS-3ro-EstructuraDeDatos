//
// Created by Franc on 10/11/2025.
//

#include <cstddef>
#include <memory>
#include <optional>
#include <iostream>

struct Node
{
    int value;
    Node* next;

    Node(const int value, Node* next) : value(value), next(next) {}
};

class Stack
{
    static constexpr std::size_t EMPTY_STACK = -1;

    Node* stack = nullptr;
    std::size_t top = -1;
    const std::size_t capacity;

public:
    explicit Stack(const std::size_t capacity = -1)
        : capacity(capacity)
    {

    }

    bool push(const int val)
    {
        if (top == capacity - 1)
        {
            std::cout << "La pila esta llena." << std::endl;
            return false;
        }

        const auto node = new Node(val, stack);
        stack = node;
        top++;

        return true;
    }

    std::optional<int> pop()
    {
        if (top == EMPTY_STACK)
        {
            std::cout << "La pila esta vacia." << std::endl;
            return std::nullopt;
        }

        const auto top_node = stack;

        int value = top_node->value;
        stack = top_node->next;
        top--;

        delete top_node;
        return value;
    }

    [[nodiscard]] std::optional<int> peek() const
    {
        if (top == EMPTY_STACK)
        {
            std::cout << "La pila esta vacia." << std::endl;
            return std::nullopt;
        }

        return stack->value;
    }

    [[nodiscard]] bool isEmpty() const
    {
        return top == EMPTY_STACK;
    }

    [[nodiscard]] bool isFull() const
    {
        return top == capacity - 1;
    }
};

int main()
{
    auto stack = Stack();
    stack.push(10);
    stack.push(20);
    stack.push(30);

    std::cout << "Elemento superior: " << stack.pop().value() << std::endl;
    std::cout << "Elemento superior (sin extraer): " << stack.peek().value() << std::endl;
    std::cout << "Elemento superior (extraido): " << stack.pop().value() << std::endl;
    std::cout << "Ultimo elemento: " << stack.pop().value() << std::endl;

    return 0;
}
