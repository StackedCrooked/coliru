#include <iostream>

struct A
{
    struct B { int x; };
    
    B operator()() { auto b = B(); b.x = 42; return b; }
};

int main() { A a; std::cout << a().x << std::endl; }