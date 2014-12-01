#include <iostream>
#include <initializer_list>

struct A
{
    bool operator+(A a);
};

bool operator+(A, A)
{
    return false;
}

int main()
{ 
    A a, b;
    std::cout << a + b << std::endl;
}