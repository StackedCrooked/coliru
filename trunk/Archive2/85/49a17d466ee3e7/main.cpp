#include <iostream>

auto& Foo() {
    double pi = 3.14159;
    return &pi;
}

int main() {
   const auto& pi = Foo();
   std::cout << *pi;
}