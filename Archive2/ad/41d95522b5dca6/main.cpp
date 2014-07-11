#include <type_traits>
#include <iostream>

template <class T>
class X {
};

template <class T>
void f(X<T>)
{
    std::cout << std::is_same<T, int>::value;
}

int main()
{
    f(X<int>());
}