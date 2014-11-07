#include <iostream>           
#include <vector>
#include <thread>
#include <new>
#include <algorithm>

using namespace std;

class C {
    public:
C() {
     cout << "C  CTOR!\n";
 }
 ~C() {
    cout << "C  ~DTOR!\n";   
 }

    };

class A {
 public:
 A() {
     cout << "A  CTOR!\n";
     qw.reset(new C);
     
 }
 ~A() {
    cout << "A  ~DTOR!\n";   
 }
    shared_ptr<C> qw;
};

int main ()
{
    shared_ptr<A> a(new A);
//    ad = make_shared<A>(new A);
    cout << "TROLOLO\n";
    return 0;
}






















