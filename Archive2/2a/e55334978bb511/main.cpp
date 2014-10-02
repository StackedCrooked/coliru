#include <iostream>

struct Speaker {
    void speak() const {
        std::cout << "Module A says hello\n";
    }
};

void function_a() {
    Speaker s;
    s.speak();
}