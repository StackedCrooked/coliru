#include <iostream>

template<int I, long L>
struct foo {};

template<char L>
struct foo<42, L> {};

int main()
{
    foo<0, 1L> f1;
    foo<1L> f2;
}
