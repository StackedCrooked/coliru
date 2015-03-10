#include <iostream>
#include <algorithm>
#include <vector>

template<typename...> using void_t = void;
template<typename T> void f(void_t<typename T::foo>);

int main()
{
    f<int>();
}