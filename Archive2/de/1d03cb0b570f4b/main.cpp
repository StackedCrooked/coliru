#include <iostream>
// class-specific allocation functions
struct X {
    static void* operator new(std::size_t sz)
    {
        std::cout << "custom new for size " << sz << '\n';
        return ::operator new(sz);
    }
    static void* operator new[](std::size_t sz)
    {
        std::cout << "custom new for size " << sz << '\n';
        return ::operator new(sz);
    }
};
int main() {
     X* p1 = new X;
     delete p1;
     X* p2 = new X[10];
     delete[] p2;
}