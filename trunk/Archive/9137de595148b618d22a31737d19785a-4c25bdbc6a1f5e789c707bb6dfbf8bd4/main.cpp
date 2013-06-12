#pragma coliru "a.h"
#ifndef A_H_INCLUDED
#define A_H_INCLUDED

int sum(int, int);

#endif // A_H_INCLUDED


#pragma coliru "a.cpp"
#include "a.h"

int sum(int a, int b)
{
    return a + b;
}


#pragma coliru "main.cpp"
#include "a.h"
#include <iostream>

int main()
{
    std::cout << sum(3, 4) << std::endl;
}
