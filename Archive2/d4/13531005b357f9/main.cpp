#include <iostream>

class A
{
public:
    ~A() {
        std::cout << "A destructed" << std::endl;
    }
};

A a;

int main() {
    std::cout << "main start" << std::endl;
    a.~A();
    std::cout << "main end" << std::endl;
}
