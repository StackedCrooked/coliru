#include <iostream>
template <class _Tp> struct split { typedef _Tp ptr; };
template <class _Tp, class _Up> struct split<_Tp _Up::*> { typedef _Tp ptr; typedef _Up base; };

struct X { void f() const;};

int main () {

 typedef split<void (X::*)() const>::ptr  T;
 typedef split<void (X::*)() const>::base  U;
 
 T  X::* a = &X::f;
  std::cout << "A, B: " << std::is_same<void (),T>::value << std::is_same<X,U>::value << std::endl;
}