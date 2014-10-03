#include <iostream>
#include <type_traits>

// float f();
void g(int);
int h(int) { return 0; }


template<unsigned P> struct priority : priority<P-1> {};
template<> struct priority<0> {};

template<class Int> auto call_best(Int i, priority<2>) -> decltype(f(i)) { return f(i); }
template<class Int> auto call_best(Int i, priority<1>) -> decltype(g(i)) { /*return g(i);*/ } // removed the call to avoid linker error
template<class Int> auto call_best(Int i, priority<0>) -> decltype(h(i)) { return h(i); }

void call_best(int i) { call_best(i, priority<2>{}); }

int main()
{
    std::cout << std::is_same<decltype(call_best(0)), void>{};
}