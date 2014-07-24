#include <iostream>
#include <typeinfo>
#include <type_traits>

struct C
{
  template<class T>
  C(T && t) {
    // T is int&, not just int  
    static_assert(std::is_same<T,int&>::value, "Oops");
    std::cout << typeid(T).name() << std::endl;
  }
};

struct D
{
  D(int && t) { }
};

int main() 
{
    int i = 1;
    std::cout << typeid(i).name() << std::endl;

    C c(i);     // OK
    // D d(i);     // error
}
