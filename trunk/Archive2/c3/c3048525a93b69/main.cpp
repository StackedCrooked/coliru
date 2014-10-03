#include <type_traits>
#include <iostream>

template<typename T>
typename std::enable_if< std::is_rvalue_reference<T>::value >::type
f(T&& t) { std::cout << "T&&\n"; }

template<typename T> void f(T const& t) { std::cout << "const T&\n"; }

int main()
{
    int i;
    f(i);
    f(10);
}