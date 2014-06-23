#include<iostream>
using namespace std;
namespace test {
    template <class T>
    class A {
    public:
      void foo() { cout << "A::foo()" << endl; }
    };
}

template <class T>
class B : public test::A<T> { 
};

template <class T>
class C : public B<T>{
};


int main() {
  C<int>* p = new C<int>();
  p->A<int>::foo(); 
}