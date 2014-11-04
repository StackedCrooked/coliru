#include <vector>
#include <cstdio>

class A
{
    public :
    virtual void print() const
    {
        printf("A");
    }
};

class B : public A
{
    public :
    virtual void print() const override
    {
        printf("B");
    }
};

class C : public A
{
    public :
    virtual void print() const override
    {
        printf("C");
    }
};

void printme(A* obj)
{
    obj->print();
}

int main()
{
    A* a = new A();
    A* b = new B();
    A* c = new C();
    
    printme(a);
    printme(b);
    printme(c);
    
    return 0;
};