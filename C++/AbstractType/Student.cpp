
#include <string>
#include <cstdint>
#include <iostream>

class Student
{
public:
    std::string name;
    uint8_t age;

    void sayHello() {
        std::cout << "Hello, my name is " << name << ".\nI'm " << std::to_string(age) << " years old.";
    }

    Student(std::string _name, uint8_t _age)
    {
        name = _name;
        age = _age;
    }
    
};