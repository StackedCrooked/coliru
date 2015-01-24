#include <iostream>
struct Foo {
    int n;
    Foo() {
       std::clog << "static constructor\n";
    }
    ~Foo() {
       std::clog << "static destructor\n";
    }
};
Foo f; // static object
int main()
{
    std::clog << "main function\n";
}