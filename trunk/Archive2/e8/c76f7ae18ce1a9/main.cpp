#include <iostream>

class A
{
    public:
    int a;
    void printA();
    A();
    private:
    A(const A& a);
    
};

A::A()
{
    a=2;
}

void A::printA()
{
    std::cout<<a;
}


class B
{
    public:
    A a;
    void printY();
    int y;
    B();
    B(const B& b);
};

B::B()
{
}

B::B(const B& b)
{
    y=b.a.a;
}
void B::printY()
{
    std::cout<<y;
}
int main()
{
    B b;
    B bb(b);
    bb.printY();
    return 0;
}
