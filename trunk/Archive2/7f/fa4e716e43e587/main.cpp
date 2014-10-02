#include <iostream>

struct Speaker {
    void speak() const {
        std::cout << "Module B says hello\n";
    }
};

void function_b() {
    Speaker s;
    s.speak();
}