// header file
#ifndef EXAMPLE_H
#define EXAMPLE_H
// function included in multiple source files must be inline
inline int sum(int a, int b) 
{
    return a + b;
}
#endif
 
// source file #2
#include "example.h"
int a()
{
    return sum(1, 2);
}
 
// source file #1
#include "example.h"
int b()
{
    return sum(3, 4);
}