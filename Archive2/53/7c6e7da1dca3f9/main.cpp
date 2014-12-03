#include <iostream>           
#include <queue>
#include <algorithm>
#include <memory>

using namespace std;

class A {
    public:
    A() { cout << "A()" << endl; }
     virtual ~A() { cout << "~A" << endl; }
};

class B : public A {
    public:
    B() { cout << "B()" << endl; }
    ~B() { cout << "~B" << endl; }
};

class C {
  A* ptr1;
  
  public:
  C() { cout << "C()" << endl; ptr1 = new B(); }
  ~C() { cout << "~C" << endl; delete ptr1; }
  void foo() {
    cout << "foo()" << endl;
  }
};


int main ()
{
    shared_ptr<void> sp1(new B()); // sp1 stores B*
     cout << "B* is being deleted" << endl;
    sp1.reset(new A()); // now sp1 stores A*
     cout <<  "A* is being deleted" << endl;
    sp1.reset(new C); // now stores C*
    static_pointer_cast<C>(sp1)->foo(); // C* has method
     cout <<  "C* is being deleted" << endl;
}






















