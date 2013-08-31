#include <iostream>
#include <typeinfo>

struct Null {};

struct S
{
  template<typename, typename = void> struct map { typedef Null type; };
  template<typename T> struct S::map<int, T> { typedef char type; };
  template<typename T> struct S::map<char, T> { typedef int type; };
};

int main()
{
  std::cout << typeid(S::map<int>::type).name() << std::endl;  // c
  std::cout << typeid(S::map<char>::type).name() << std::endl; // i
  std::cout << typeid(S::map<S>::type).name() << std::endl;    // 4Null
}
