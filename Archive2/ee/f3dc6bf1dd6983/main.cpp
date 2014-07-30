#include <iostream>
class A {
public:
    virtual ~A() {}
};
class B : public A {};
class C : public B {};
class D {
public:
    virtual ~D() {}
};

int main()
{
    using namespace std;
    
    A* a1 = nullptr;
    B* b1 = dynamic_cast<C*>(a1);
    cout << ( b1 ? "valid" : "invalid") << endl;

    A* a2 = new C();
    B* b2 = dynamic_cast<C*>(a2);
    cout << ( b2 ? "valid" : "invalid") << endl;

    D* d = new D();
    B* b3 = dynamic_cast<C*>(d);
    cout << ( b3 ? "valid" : "invalid") << endl;
}
