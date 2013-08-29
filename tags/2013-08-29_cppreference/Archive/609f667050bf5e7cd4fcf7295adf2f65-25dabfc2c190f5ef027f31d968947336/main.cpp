#include<iostream>

struct A
{
    A() {std::cout<<"def"<<'\n';}
    void foo() const & {std::cout<<"called on lvalue"<<'\n';}
};

int main()
{   
    A a;
    a.foo();
    A().foo();
    return 0;
}