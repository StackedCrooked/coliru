// file test.h
#ifndef TEST_H
#define TEST_H
inline int sum (int a, int b)
{
    return a+b;
}
#endif
 
// file test1.c
#include <stdio.h>
#include "test.h"
extern int f(void);
 
int main(void)
{
    printf("%d\n", sum(1, 2) + f());
}
 
// file test2.c
#include "test.h"
 
int f(void)
{
    return sum(2, 3);
}