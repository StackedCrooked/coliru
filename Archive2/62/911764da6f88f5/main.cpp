#include <iostream>
#include <typeinfo>

using namespace std;

struct Base {
    virtual void Teste();
    virtual void Teste2() { cout << "Base Teste2" << endl; };
};

struct Derived : Base {
    virtual void Teste2() { cout << "Derived Teste2" << endl; }
};

void Base::Teste() {
        cout << "1: " << typeid(this).name() << endl;
        cout << "2: " << typeid(*this).name() << endl;
        this->Teste2(); // The right Teste2 will be grabbed from vtable
}

int main() {
    Base b;
    b.Teste();

    Derived d;
    d.Teste();

    return 0;
}