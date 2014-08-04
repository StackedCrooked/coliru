#include <iostream>

struct B {
    virtual ~B() = default;
    void operator delete(void* ptr) { std::cout << "B's operator delete" << std::endl; ::operator delete(ptr); }
};
struct D : B {
    void operator delete(void* ptr) { std::cout << "D's operator delete" << std::endl; ::operator delete(ptr); }
};
int main() {
    B* bp = new D;
    delete bp; //1: uses D::operator delete(void*)
}