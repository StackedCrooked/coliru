#include <functional>
#include <iostream>

struct A{};
struct B : public A{};

using func = std::function<A*()>;

A* a() {std::cout << "a"; return new A;}
B* b() {std::cout << "b"; return new B;}

int main() {
    func fa = a;
    fa();
    
    func fb = b;
    fb();
}