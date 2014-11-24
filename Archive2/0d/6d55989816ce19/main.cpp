#include <iostream>


struct Foo
{
    Foo(int i = 42): i(i) { std::cout << "Foo ctor\n"; }
    
    Foo(const Foo&op): i(op.i) { std::cout << "Foo copy ctor\n"; }
    Foo(Foo&&op): i(op.i) { std::cout << "Foo move ctor\n"; }
    
    Foo& operator=(const Foo&op) { i = op.i; std::cout << "Foo copy assign\n"; return *this; }
    Foo& operator=(Foo&&op) { i = op.i; std::cout << "Foo move assign\n"; return *this; }
    
    int i;
};

Foo bar()
{
    return Foo(99);
}

int main() {
    auto f = bar();
    std::cout << f.i << std::endl;
}