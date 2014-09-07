#include <utility>
#include <iostream>
using namespace std; // Don't pay attention to this :)
 
class Base {
    public:
    virtual void hello() { cout << "hello base"; }
};
class Derived : public Base {
    public:
    virtual void hello() { cout << "hello derived"; }
};
int main()
{
    Derived * p = static_cast<Derived *>(operator new(sizeof(Derived)));

    Base& r = *p;
    r.hello(); // invalid vtable
}