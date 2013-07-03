#include <cstdio>
#include <iostream>
#include <vector>
#include <iomanip>
#include <sstream>
#include <cstring>
 #include <complex>
 
struct A
{
    struct B
    {
        B() {}
        int i = 0 ;
    };

    B b;

    A(const B& _b = B() )
        : b(_b)
    {}
};

int main()
{
}