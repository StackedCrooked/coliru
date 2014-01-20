#include <iostream>

#define OFFSET(T, m) ([]{ T t; return (char*)(&t.m) - (char*)(&t); }())

struct A
{
    int a, b;
};


int main()
{
    std::cout << OFFSET(A, a) << std::endl;
    std::cout << OFFSET(A, b) << std::endl;
}