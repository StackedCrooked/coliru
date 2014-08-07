#include <cstdlib>
#include <iostream>
#include <new>

struct S {
    void *operator new(std::size_t) {
        std::cout << "My new\n";
        return ::new S;
    }
    
    void operator delete(void *p, std::size_t) {
        std::cout << "My delete\n";
        ::delete (S*)p;
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