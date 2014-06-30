#include <stdio.h>

class A
{
public:
    static int var;
};

class B: public A
{
};

int A::var = 5;

int main()
{
    printf("%d\n", B::var);
    return 0;
}