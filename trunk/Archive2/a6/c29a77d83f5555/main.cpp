#include <iostream>
#include <type_traits>

class MyClass {
    public:
        MyClass operator +() {std::cout << "one"; return (*this); }
};

MyClass operator +(const MyClass& a) { return a; }

int main() {
    MyClass a;
    +a;
}