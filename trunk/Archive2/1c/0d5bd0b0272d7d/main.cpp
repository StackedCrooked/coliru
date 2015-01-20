#include <iostream>
#include <stdio.h>

typedef unsigned long long int64;
typedef unsigned int       int32;

int main()
{
    printf("%.50f\n", 0.01f);
    printf("%.50f\n", 1000 * 0.01f);
    
    int64 test = 1000 * 0.01f;
    printf("Test %u\n",test); // Prints 10

    int64 test2 = 1000;
    test2 = test2 * 0.01f;
    printf("Test2 %u\n",test2); // Prints 9

    int32 test3 = 1000;

    test3 = test3 * 0.01f;
    printf("Test3 %i\n",test3); // Prints 9

    int64 test4 = 1000;
    test4 = test4 * 0.01; 
    printf("Test4 %u\n",test4); // Prints 10

    int32 test5 = 1000;

    test5 = test5 * 0.01;
    printf("Test5 %i\n",test5); // Prints 10

}