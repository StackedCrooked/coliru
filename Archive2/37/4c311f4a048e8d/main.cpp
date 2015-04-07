#include <cstdio>
#include <cstdlib>
// replacement of a minimal set of functions:
void* operator new(std::size_t sz) {
    std::printf("global op new called, size = %zu\n",sz);
    return std::malloc(sz);
}
void operator delete(void* ptr) noexcept
{
    std::puts("global op delete called");
    std::free(ptr);
}
struct Ble
{
    int a;
    int b;
    float j;
};
int main() {
     Ble* p1 = new Ble;
     delete p1;
 
     int* p2 = new int[10]; // guaranteed to call the replacement in C++11
     delete[] p2;
}