#include <iostream>
#include <string>

void print_a() { std::cout << &"fuck" << '\n'; }
void print_b() { std::cout << &"fuck" << '\n'; }

int main() {
    std::cout << &"fuck" << '\n';
    print_a();
    print_b();
}