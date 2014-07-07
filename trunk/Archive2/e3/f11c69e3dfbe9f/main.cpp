#include <iostream>

template<bool> struct test;
template<> struct test<true>{ using type = void; };

template<bool B>
typename test<B>::type f(int)
{ std::cout << "true\n"; }

template<bool>
void f(...)
{ std::cout << "false\n"; }

int main()
{
    f<true>(0);
    f<false>(0);
}