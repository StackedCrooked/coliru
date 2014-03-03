#include <boost/utility/enable_if.hpp>
#include <boost/type_traits.hpp>


enum E1 { Z = 12 };
enum E2 { X = 0 };

#include <iostream>

void f(int i) { std::cout << "int: " << i << "\n"; }
template <class E>
void f(E e, typename boost::enable_if<boost::is_enum<E> >::type* /*ignored*/= 0)
{
    std::cout << "enum-";
    f(static_cast<int>(e));
}

int
main( int argv, char* argc[] )
{
  f(X);
  f(4);
  f(Z);
}
