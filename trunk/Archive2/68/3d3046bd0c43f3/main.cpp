#include <iostream>

template<typename T>
void print1(T arg)   { std::cout << arg << '\n'; }

template<typename T>
void print2(T& arg) { std::cout << arg << '\n'; }

struct foo
{
    static int const i = 42;
};
// int const foo::i;  // uncomment this to fix the error

int main()
{
    print1(foo::i);
    print2(foo::i);     // this causes an undefined symbol error
}
