#include <cstdlib>
#include <iostream>
#include <new>

struct S {
    void *operator new(std::size_t) {
        std::cout << "My new\n";
        return nullptr;
    }
    
    void operator delete(void *, std::size_t) {
        std::cout << "My delete\n";
    }
};

int main() {
    std::cout << "new:\n";
    auto p1 = new S;
    delete p1;
    
    std::cout << "::new:\n";
    auto p2 = ::new S;
    ::delete p2;
}