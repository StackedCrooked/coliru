#include <stdio.h>

class A
{
public:
    virtual void Print()
    {
        printf("A\n");
    }
};

class B : virtual public A
{
public:
    virtual void Print()
    {
        printf("B\n");
    }
};

class C : virtual public A
{
public:
    virtual void Print()
    {
        printf("C\n");
    }
};

class D : public B, public C
{
};

int main()
{
    
}