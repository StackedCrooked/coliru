#include <iostream>
#include <vector>

struct A {
    A() { std::cout << "default constructor\n"; }
    A(const A&) { std::cout << "copy constructor\n"; }
    A(A&&) { std::cout << "move constructor\n"; }
    A& operator=(const A&) { std::cout << "copy assignment\n"; return *this; }
    A& operator=(A&&) { std::cout << "move assignment\n"; return *this; }
    ~A() { std::cout << "destructor\n"; }
};

A pop(A* p) {
    A tmp(std::move(*p));
    p->~A();
    return tmp;
}

int main() {
    void* storage = ::operator new(sizeof(A));
    
    {
        std::cout << "pop result used:\n";
        A* p = new (storage) A();
        A res = pop(p);
    }
    
    {
        std::cout << "pop result unused:\n";
        A* p = new (storage) A();
        pop(p);
    }
    
    ::operator delete(storage);
    
    return 0;
}