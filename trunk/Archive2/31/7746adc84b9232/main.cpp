#include <iostream>

template<unsigned P> struct priority : priority<P-1> {};
template<> struct priority<0> {};

auto f(int);
auto g(int);
auto h(int) { std::cout << "h()"; }

template<class Int> auto call_best(Int i, priority<2>) -> decltype(f(i)) { return f(i); }
template<class Int> auto call_best(Int i, priority<1>) -> decltype(g(i)) { return g(i); }
template<class Int> auto call_best(Int i, priority<0>) -> decltype(h(i)) { return h(i); }

void call_best(int i) { call_best(i, priority<2>{}); }

int main()
{
    call_best(0);
}