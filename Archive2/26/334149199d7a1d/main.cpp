#include <iostream>
#include <utility>


template<typename T>
T simple_move(T& src)
{
    static_assert(std::is_pod<T>::value, "");
    T dst = src;
    src = T();
    return dst;
}


int main()
{
    int a = 1;
    int b = simple_move(a);
    std::cout << a << ' ' << b;
}
