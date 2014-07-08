#include <memory>
#include <iostream>

struct Foo {
    Foo() : i(c++) {}
    ~Foo() { std::cout << __PRETTY_FUNCTION__ << ": " << i << std::endl; }
    int i;
    static int c;
};
int Foo::c = 100;

int main() {
    {
        Foo * array[5] = (new Foo[5]);
    }
    std::cout << "mark" << std::endl;
    
}