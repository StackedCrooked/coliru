#include <iostream>
#include <typeinfo>

using std::cout;
using std::endl;

long unsigned int hash_in_constructor;

struct A {
    virtual void foo() {
        cout << "A" << endl;
    }
    
    A() { 
        hash_in_constructor = typeid(this).hash_code();
    }
};


int main() {
    cout << "static init = " << hash_in_constructor << endl;
    A a;
    a.foo();
    cout << "after ctor = " << hash_in_constructor << endl;
    cout << "typeid(&a) = " << typeid(&a).name() << " : " << typeid(&a).hash_code() << endl;
    cout << "typeid(a) = " << typeid(a).name() << " : " << typeid(a).hash_code() << endl;
    cout << "typeid(A) = " << typeid(A).name() << " : " << typeid(A).hash_code() << endl;
}