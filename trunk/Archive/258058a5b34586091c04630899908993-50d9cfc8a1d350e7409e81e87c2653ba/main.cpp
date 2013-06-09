#include <iostream>

template <size_t N>
static int f()
{
    int m[N] = {};
    
    m[0] = 42;
    
    return m[0];
}

int main()
{
    int m[f<4>()];
    
    std::cout << sizeof(m) / sizeof(int);
}