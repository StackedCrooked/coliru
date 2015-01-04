#include <iostream>
#include <type_traits>

class A {};

void foo(const A&  ) { std::cout << "Reference" << std::endl; }

void foo(      A&& ) { std::cout << "Move" << std::endl; }

template <typename T, typename U, typename R=void>
using enable_if_compatible = typename std::enable_if<std::is_same<U, typename std::remove_reference<T>::type>::value, R>::type;

template <typename T>
enable_if_compatible<T, A> bar(T&& a)
{
    //Other things, which treat "a" as a const reference
    foo(std::forward<T>(a));
}

int main() {
    A a;
    bar(a);
    bar(A());
}
