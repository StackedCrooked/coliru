#include <iostream>

template<typename T>
class
[[deprecated]]
OldClass {
public:
  void mf(){}
  static void smf(){ std::cout << "Hi!\n";}
};

template<template<typename> class C = OldClass>      // use deprecated template as
void f()                                             // default template parameter
{
  C<int> obj;
  obj.foo();
}



int main()
{  
  //auto pmf = &OldClass<int>::mf;        // take addresses of member functions
  //auto psmf = &OldClass<int>::smf;      // of instantiation of deprecated template
  
  //psmf();       // call static member function
  std::cout << "Done!\n";
}
