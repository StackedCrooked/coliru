#include <iostream>
#include <type_traits>

class A {};

void foo(const A&  ) { std::cout << "Reference" << std::endl; }

void foo(      A&& ) { std::cout << "Move" << std::endl; }

template <typename T>
auto bar(T&& a) -> decltype(void(foo(std::forward<T>(a))))
{
    //Other things, which treat "a" as a const reference
    foo(std::forward<T>(a));
}

int main() {
    A a;
    bar(a);
    bar(A());
}
