#include <iostream>
#include <string>
#include <vector>
#include <typeinfo>

using namespace std;

struct P {};
struct Q : P {};

struct A
{
    virtual P* f() { cout << "A" << endl; return new P; }  
};

struct B : A
{
    Q* f() { cout << "B" << endl; return new Q; }
};

int main()
{
    B b;
    A* pb = &b;
    
    auto i = pb->f();
    
    cout << typeid(P*).name() << endl;
    cout << typeid(Q*).name() << endl;
    cout << typeid(i).name() << endl;
}