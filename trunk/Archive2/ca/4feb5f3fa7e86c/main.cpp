#include <stdio.h>

struct A 
{
    int i;
    A(const A&)
    {
        puts("42");
    }
    A()
    {}
};

int main() 
{
    A a = A(A(A(A(A(A())))));
    printf("a = %d\n", a.i); 
}
