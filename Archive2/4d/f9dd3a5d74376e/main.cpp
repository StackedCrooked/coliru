#include <iostream>

static unsigned int instances = 0;
struct HeapInteger {
    const unsigned int instance = ++instances;
    
    HeapInteger() = delete;

    explicit HeapInteger(int initialData) {
        std::cout << "Constructing HeapInteger #" << instance << " @" << this << "." << std::endl;
    }
    
    HeapInteger(const HeapInteger& other) {
        std::cout << "Copy-constructing HeapInteger #" << instance << " @" << this << " from HeapInteger #" << other.instance << " @" << &other << "." << std::endl;
    }
    
    HeapInteger(HeapInteger&& other) {
        std::cout << "Move-constructing HeapInteger #" << instance << " @" << this << " from HeapInteger #" << other.instance << " @" << &other << "." << std::endl;
    }
    
    ~HeapInteger() {
        std::cout << "Destructing HeapInteger #" << instance << " @" << this << "." << std::endl;
    }
};

HeapInteger foo() {
    HeapInteger h(123);
    return h;
}

int main() {
    HeapInteger x(foo());
}