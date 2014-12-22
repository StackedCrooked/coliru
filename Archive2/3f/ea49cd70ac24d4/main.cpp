#include <utility>
#include <iostream>
#include <stdio.h>
#include <cstring>

typedef struct test_s
{
    int a;
    char* some_vals;
}test_t;



int main()
{
    test_t *test;
    test = (test_t*)malloc(sizeof(test_t));
    test_t filled = {};
    filled.a = 3;
    
    memcpy(test, &filled, sizeof(test_t));
    std::cout << "out " << test->a << " addr: " << &filled.some_vals << " addr: "<< &test->some_vals<< std::endl;
}