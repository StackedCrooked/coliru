#include <iostream>
#include <string>
#include <vector>
#include <typeinfo>

using namespace std;

struct A
{
    virtual int f() { cout << "A" << endl; return 0u; }  
};

struct B : A
{
    int f() { cout << "B" << endl; return 0; }
};

int main()
{
    B b;
    A* pb = &b;
    
    auto i = pb->f();
    
    cout << typeid(int).name() << endl;
    cout << typeid(float).name() << endl;
    cout << typeid(i).name() << endl;
}