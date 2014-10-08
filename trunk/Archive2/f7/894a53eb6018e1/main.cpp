#include <iostream>
using namespace std;

class S{};
class A:public S{
    virtual void fun()=0;
};
class B{};
class C:public B,public A{};

int main(){
cout<<sizeof(A)<<endl;// result is 4
cout<<sizeof(C)<<endl;//result is 8
} 