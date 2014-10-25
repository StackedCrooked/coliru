#include <iostream>
#include <limits>



union U
{
    struct A
    {
        int a;
    } a;

    struct B
    {
       int b;
    } b;
};

U a;


int main()
{
    a.a.a =5;
    std::cout << a.b.b <<std::endl; //Cause no UB?
}

