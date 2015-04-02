#include <type_traits>

template <bool cond, int id>
using distinct_enable_if = typename std::enable_if<cond, std::integral_constant<int,id>*>::type;

class test
{
public:
  // A constructor that works for any argument list of size 10
  template< class... T,
            typename=typename std::enable_if< sizeof...( T ) == 10 >::type>
  test( T&&... ) {}

  // A conversion operation that can convert to any arithmetic type
  template< class T,
            distinct_enable_if<std::is_arithmetic<T>{}, 0> = nullptr>
  operator T() const { return T{}; }

  // A conversion operation that can convert to any pointer type
  template< class T,
            distinct_enable_if<std::is_pointer<T>{}, 1> = nullptr>
  operator T() const { return T{}; }
};

int main()
{
  // Works
  test test_( 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 );

  // Fails as expected
  //test fail_construction( 1, 2, 3, 4, 5 );

  // Works by calling the conversion operator enabled for arithmetic types
  int arithmetic_object = test_;

  // Works by calling the conversion operator enabled for pointer types
  int* pointer_object = test_;
  
  (void)arithmetic_object; (void)pointer_object;

  // Fails as expected
  //struct {} fail_conversion = test_;
}
