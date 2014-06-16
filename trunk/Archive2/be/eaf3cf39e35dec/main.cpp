#include <iostream>
#include <string>
#include <vector>
#include <typeinfo>

using namespace std;

class A
{ 
    public:
        virtual void f() {cout << 'a';}
};

class B : public A
{
    public:
        void f() {cout << 'b';}
};

class C : public B
{
    public:
        void f() {cout << 'c';}
};

int main(void)
{
    A* pa = new C();
    
    pa -> f();
}


  
