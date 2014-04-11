#include <cstddef>

template<typename T, std::size_t N> void foo(T(&x)[N]);
template<typename T>                void foo(T *x); 

int main()
{
    int x[2] = {0, 1};
    foo(x);
}