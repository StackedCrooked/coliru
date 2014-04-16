#include <iostream>

template<class T>
struct has {
  typedef char yes;
  typedef yes (&no)[2];    
  template<int> struct foo;    
  template<class U> static yes test(foo<U::bar>*);      
  template<class U> static no  test(...);    
  static bool const value = sizeof(test<T>(0)) == sizeof(yes);
};

enum foo { bar };

int main()
{
    std::cout << (has<foo>::value ? "yes" : "no") << std::endl;
}