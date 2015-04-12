#include <iostream>

template<int I, int... Is> struct A { };

template<int... Is> void f(A<Is...>)
{
    std::cout << sizeof...(Is) << '\n';
}

int main()
{
	f(A<1, 2>());
}
