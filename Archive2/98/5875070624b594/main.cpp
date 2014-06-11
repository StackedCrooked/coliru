#include <iostream>
#include <string>
#include <vector>

class A {public: virtual void f() {cout<<"echo A";}};
class B: public A {public: void f() {A::f(); cout<<"echo B";}};
class C: public B {public: void f() {B::f(); cout<<"echo C\n";}};
int main() {A *ptr; B b; C c; int flag=0; randomize(); flag = random(2);
switch (flag) {case 0: ptr=&b; break; case 1: ptr=&c; break;} ptr->f(); 
