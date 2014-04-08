#include <iostream>

template<int N> struct Fib { enum { value = Fib<N-1>::value + Fib<N-2>::value }; };
template<> struct Fib<1> { enum { value = 1 }; };
template<> struct Fib<0> { enum { value = 0 }; };
int main() { std::cout << Fib<20>::value; }
