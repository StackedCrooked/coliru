#include <boost/type_traits.hpp>
#include <boost/utility/enable_if.hpp>

struct EnumToInt {
  int i;
  template <class E>
  EnumToInt(E e, typename boost::enable_if<boost::is_enum<E> >::type* /*ignored*/= 0)
  {
    i = static_cast<int>(e);
  }
};


enum E1 { Z = 12 };
enum E2 { X = 0 };

#include <iostream>

void f(EnumToInt e) { std::cout << "enum: " << e.i << "\n"; }
void f(int i) { std::cout << "int: " << i << "\n"; }

int
main( int argv, char* argc[] )
{
  f(X);
  f(4);
  f(Z);
}
