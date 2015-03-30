#include <iostream>

extern void* v;
extern void* y;

template<void*&>
void f() {
    static auto i = 0u;
    std::cout << i++ << std::endl;
}

int main()
{
    f<v>();
    f<y>();
    f<y>();
}
