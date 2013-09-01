#include <string>
#include <iostream>

template<size_t N>
void f(const char (&arr)[N]) {
    std::cout << "f(1)\n";
}

void f(const std::string& w) {
    std::cout << "f(2)\n";
}

int main() {
    f("hello");
    f(std::string("Hello"));
    
    char* str = new char('e');
    f(str);
    
    char c = 10;
    f(&c);
    delete str;
}