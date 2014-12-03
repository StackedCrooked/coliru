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
  C() { cout << "C" << endl; ptr1 = new B(); }
  ~C() { cout << "~C" << endl; delete ptr1; }
  void foo() {
    cout << "foo()" << endl;
  }
};


int main ()
{
    shared_ptr<void> sp1(new B());
    
    sp1.reset(new A());
    cout << "magicku # 1" << endl;
    sp1.reset(new C);
    cout << "magicku # 2" << endl;
    (C*)sp1->foo();
}






















