#include <iostream>

template<class T>
struct has_nested_option{
  typedef char yes;
  typedef yes (&no)[2];

  template<int>
  struct test2;

  template<class U>
  static yes test(test2<U::option>*);
  template<class U>
  static no  test(...);

  static bool const value = sizeof(test<T>(0)) == sizeof(yes);
};


enum test
{
    abc
};

enum test2
{
    option
};



int main()
{
    std::cout << has_nested_option<test2>::value << std::endl;
}