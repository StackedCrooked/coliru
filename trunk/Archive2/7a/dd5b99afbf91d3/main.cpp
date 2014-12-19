#include <iostream>

enum E : long { e = 16 };

struct X 
{
    E e : 5;
};

X x;


int main(){ x.e = E::e; std::cout << static_cast<int>(x.e) << std::endl; }