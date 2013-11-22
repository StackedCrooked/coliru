#include <type_traits>
#include <iostream>
 
template<class T>
typename std::result_of<T(int)>::type
f(T& t)
{
    std::cout << "overload of f for callable T\n";
    return t(0);
}
 
template<class T, class U>
int f(U u)
{
    std::cout << "overload of f for non-callable T\n";
    return u;
}
 
struct S {};
 
int main() {
  f<S>(1); // fails to compile in C++11, calls the non-callable overload in C++14
}
output=
overload of f for non-callable T