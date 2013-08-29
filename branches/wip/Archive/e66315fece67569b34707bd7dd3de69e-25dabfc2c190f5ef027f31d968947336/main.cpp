#include<iostream>

struct A
{
    A() {std::cout<<"def"<<'\n';}
    void foo() & {std::cout<<"called on lvalue"<<'\n';}
    void foo() && {std::cout<<"called on rvalue"<<'\n';}
};

int main()
{   
    A a;
    a.foo();
    A().foo();
    return 0;
}