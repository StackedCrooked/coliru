#include <iostream>

class A
{
    bool foo;
    public:
        A(bool a): foo(a) {}
        bool getFoo(){return foo;}
};

void compare(A &a, A &b)
{
   std::cout<<a.getFoo()<<":"<<b.getFoo()<<"\n";
   if(a.getFoo()==b.getFoo())
       std::cout<<"equal";
   else
       std::cout<<"not equal";
}

int main()
{
    A a1(true), a2(true);
    compare(a1, a2);
}
