#include <iostream>

struct A
{
    A(int, int){ std::cout << "A(int, int)" << std::endl; }
};

A a(4,4);
A b{4,4};
A c({4,4});

int main(){ }