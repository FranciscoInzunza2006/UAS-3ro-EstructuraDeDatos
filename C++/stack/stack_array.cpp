//
// Created by Franc on 10/11/2025.
//

#include <cstddef>
#include <memory>
#include <optional>
#include <iostream>

class Stack
{
    static constexpr std::size_t EMPTY_STACK = -1;

    std::unique_ptr<int[]> stack;
    std::size_t top = -1;
    const std::size_t capacity;

public:
    explicit Stack(const std::size_t capacity)
        : capacity(capacity)
    {
        stack = std::make_unique<int[]>(capacity);
    }

    bool push(const int val)
    {
        if (top == capacity - 1)
        {
            std::cout << "La pila esta llena." << std::endl;
            return false;
        }

        stack[++top] = val;
        return true;
    }

    std::optional<int> pop()
    {
        if (top == EMPTY_STACK)
        {
            std::cout << "La pila esta vacia." << std::endl;
            return std::nullopt;
        }


        return stack[top--];
    }

    [[nodiscard]] std::optional<int> peek() const
    {
        if (top == EMPTY_STACK)
        {
            std::cout << "La pila esta vacia." << std::endl;
            return std::nullopt;
        }

        return stack[top];
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
    auto stack = Stack(10);
    stack.push(10);
    stack.push(20);
    stack.push(30);

    std::cout << "Elemento superior: " << stack.pop().value() << std::endl;
    std::cout << "Elemento superior (sin extraer): " << stack.peek().value() << std::endl;
    std::cout << "Elemento superior (extraido): " << stack.pop().value() << std::endl;
    std::cout << "Ultimo elemento: " << stack.pop().value() << std::endl;

    return 0;
}
