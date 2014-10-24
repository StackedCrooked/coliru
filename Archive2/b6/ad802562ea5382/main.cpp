#include <iostream>
#include <climits>

struct A
{
    int a = 5;
};

struct B : A
{
    int a = 6;
};

B b;

int main()
{ 
    std::cout << b.B::A::a;
}