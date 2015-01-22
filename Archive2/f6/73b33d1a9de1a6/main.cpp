#include <cstddef>
#include <iostream>

template<typename T, std::size_t N>
constexpr std::size_t arraySize(T(&)[N]) noexcept { return N; }

struct S
{
    char c[10];
};

int main()
{
    S s;
    S* ps = &s;
    
    constexpr std::size_t xsize = arraySize(s.c);
    constexpr std::size_t ysize = arraySize(ps->c);
    

    return 0;
}