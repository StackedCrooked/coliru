#include <type_traits>

template<int N, class F>
void c_for_each(F f)
{
    if(N > 0)
    {
        F(std::integral_constant<int, N>{});
        c_for_each<(N>0)?N-1:1>(f);
    }
}

template

#include <iostream>
#include <functional>

void foo(int N)
{
    std::cout << N << std::endl;
}

int main()
{
    c_for_each<10>(foo);
}