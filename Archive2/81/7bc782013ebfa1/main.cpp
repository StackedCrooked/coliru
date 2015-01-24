#include <iostream>
template <typename T> void Foo(T&&) {std::cout << "A";}
void Foo(const char*) {std::cout << "B";}

int main() {
    const char* thing = nullptr;
    Foo(thing); //prints A, because it matches `Foo<const char*&>`
}