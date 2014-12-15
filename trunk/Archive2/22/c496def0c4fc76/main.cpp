#include <iostream>

struct A
{
private:
    int a = 5;
    friend int foo();
};

int a = foo();

int main(){ std::cout << a << std::endl; }