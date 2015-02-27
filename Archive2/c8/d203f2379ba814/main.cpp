#include <iostream>

template<int N>
struct A
{
    int a = A<1>::a;
};
    

int main() { }