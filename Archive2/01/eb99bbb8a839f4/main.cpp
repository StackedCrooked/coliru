#include <iostream>

struct A{
    int i;
    int j;
};


int main()
{
    constexpr A a{1};
    std::cout << a.i << '\n';
}