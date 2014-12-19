#include <iostream>

template <bool B, typename T = void>
struct enable_if { typedef T type; };

template <typename T>
struct enable_if<false, T> {};

template <int N, class V = void>
struct A;

template <int N>
struct A<N, typename enable_if<(0 <= N && N <= 10)>::type>
{
    A() { std::cout << "(0;10)\n"; }
};

template <int N>
struct A<N, typename enable_if<(11 <= N && N <= 20)>::type>
{
    A() { std::cout << "(11;20)\n"; }
};

template <int N>
struct A<N, typename enable_if<(21 <= N && N <= 30)>::type>
{
    A() { std::cout << "(21;30)\n"; }
};

int main()
{
    A<5> a;
    A<15> b;
    A<25> c;
}
