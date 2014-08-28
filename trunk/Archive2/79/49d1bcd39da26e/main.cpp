#include <iostream>
#include <string>
#include <vector>

struct A {
    int f() { return 5; }
};

struct B: public A {
    void b() {
        std::cout << f() << std::endl;
    }
};

int main() {
   B b{};
   
   b.b();
   std::cout << b.f() + 5 << std::endl;
}