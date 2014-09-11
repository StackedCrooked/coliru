#include <iostream>
struct A
{

    A(int, int) { std::cout <<"constructor with int";}
};

struct B : public A
{
    using A::A;
};
    
int main()
{

     B b(3, 3);
}
