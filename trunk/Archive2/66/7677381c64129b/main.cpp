#include <iostream>
#include <string>

void f(bool) { std::cout << "f(bool)" << '\n'; }
void f(std::string) { std::cout << "f(string)" << '\n'; }

template <typename T> void f(T&&) = delete;

int main() {
    auto p = "hello";
    f( {p} ); // Call void f(string);
    
    bool b = true;
    f(b); // Call void f(bool);
    
    // f(8); // Error!
}
