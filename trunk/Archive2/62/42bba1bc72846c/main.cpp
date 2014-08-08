#include <iostream>

template<typename T, typename U> struct bar{};

template<typename T>
struct my_template
{
    static void print() { std::cout << "primary template\n"; }
};

template<typename A, typename B>
struct my_template< bar<A, B> >
{
    static void print() { std::cout << "partial specialization\n"; }
};

int main()
{
    my_template<int>::print();
    my_template< bar<int, double> >::print();
}