#include<iostream>
#include <functional>
char const* h[] = {"Hello ", "world"};
char const** p = h;
class A{
public:
    void operator()(A&) {std::cout<<*p++;}
};

class B{
public:
    A a1, a2;
    B(){}
    B(B &tp);
};
int main(){B a, b=a;}

B::B(B &tp){
    a1(tp.a1);
    a2(tp.a2);
}

