#include <iostream>

using namespace std;

template< typename T >
class Base {
public:
    Base() : b(0) {}
    Base(T b_) : b(b_) {}
    T get();
    virtual void sayhello() { cout << "Hello from Base with b: " << b << endl; }
protected:
    T b;
};

template< typename T >
T Base<T>::get() {sayhello(); return b;} 

class Derived : public Base<double> {
public:
    Derived(double b_):Base(b_){}
    void sayhello() { cout << "Hello from Derived with b: " << this->b << endl; }
};

int main() {
    Derived d(10.0);
    Base<double>* b = &d;
    
    cout << "Derived b: " << d.get() << endl;
    cout << "Base b: " << b->get() << endl;
}
