#include <iostream>

template <class T, const T& t>
int var = t.a;

struct T
{
    int a;
    constexpr T(): a(31){ }
};

T y;

const T t = y;

const T tt = T();

int main()
{ 
    std::cout << "var <T, t> = " << var<T, t> << std::endl; 
    std::cout << "y.a = " << y.a << std::endl; 
    std::cout <<"var <T, tt> = " << var<T, tt> << std::endl; 
}