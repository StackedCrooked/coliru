#include <iostream>

using namespace std;

class A
{
public:
    A(){ cout << "Class A constructor\n";}
    A(const A &a){ cout << "Class A copy constructor\n"; }
};

class B : public A
{
public:
    B(){ cout << "Class B constructor\n";}
    B(const B &a){ cout << "Class B copy constructor\n"; }
};

template <typename T>
class Template
{
public:
    Template() { cout << "Template default\n"; }
    Template(const Template &a) { cout << "Template copy constructor\n"; }

    // This gets called
    template <typename T2>
    explicit Template(const Template<T2> &a)
    {
        cout << "Templated template copy constructor\n";
    }

};

void funcT(const Template<A> &a)
{
}

int main()
{
    Template<B> bt;

    cout << "Calling funcT(bt)\n";
    funcT(bt);

    return 0;
}