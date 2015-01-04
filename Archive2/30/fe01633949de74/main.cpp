#include <iostream>
#include <string>
#include <type_traits>

class A {};

void foo(const A&  a) { std::cout << "Reference" << std::endl; }

void foo(      A&& a) { std::cout << "Move" << std::endl; }

template <typename T>
auto bar(T&& a)
    -> typename std::enable_if<std::is_base_of<A, typename std::decay<T>::type>{}>::type
{
    //Other things, which treat "a" as a const reference
    foo(std::forward<T>(a));
}

void bar(std::string a) 
{
    std::cout << a << std::endl;
}

int main() {
    A a;
    bar(a);
    bar(A());
    bar("abc"); // not ambiguous
}
