#include <iostream>
#include <utility>
using std::cout;
using std::endl;

struct CAT
{
    CAT(){}
    int age_;
};


void f(int&& )
{
    cout<<"f(int&&)"<<endl;
}

void f(int &)
{

    cout<<"f(int&)"<<endl;
}


template<typename T>
void foo(T&& t)
{
    f(std::forward<T>(t).age_);
}


int main()
{
    CAT c;  
    foo(c);            //c is lvalue
    foo(std::move(c)); //move(c) is rvalue
}