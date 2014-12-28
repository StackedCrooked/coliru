#include <algorithm>
#include <type_traits>
#include <iostream>

class A{};
class B{};
class C{};
class D{};
class collection1 : A, B, C {};
class collection2 : D {};

template<typename X, class Enable = void>
struct enable_if_is_base_of;

template<typename X>
struct enable_if_is_base_of<X, typename std::enable_if<std::is_base_of<X, collection1>::value>::type>
{
  static X fn(X x)
  {
    (void) x;
    std::cout << "collection1" << std::endl;
    return X();
  }
};

template<typename X>
struct enable_if_is_base_of<X, typename std::enable_if<std::is_base_of<X, collection2>::value>::type>
{
  static X fn(X x)
  {
    (void) x;
    std::cout << "collection2" << std::endl;
    return X();
  }
};

int main()
{
  enable_if_is_base_of<A>::fn(A());
  enable_if_is_base_of<B>::fn(B());
  enable_if_is_base_of<C>::fn(C());
  enable_if_is_base_of<D>::fn(D());

  return 0;
}