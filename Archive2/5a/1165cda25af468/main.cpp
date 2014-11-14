#include <iostream>

using namespace std;

class A
{
    int a;
    public:
        A();
        void f();
};

A::A()
{
    cout<<"Constructor"<<endl;
}

void A::f() 
{
    cout << "hello\n";  
}

int main()
{
    A a;
    a.f();
    a.f();
    a.f();
    return 0;
}