#include <cstddef>
#include <iostream>

void* operator new(std::size_t n) {
    static int space;
    std::cout << "operator new called\n";
    return &space;
}
