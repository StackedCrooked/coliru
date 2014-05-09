#include <type_traits>

namespace detail{
  template<class> struct sfinae_true : std::true_type{};
    
  template<class T, class A0>
  static auto test_stream( int)
    -> sfinae_true<decltype(std::declval<T>().stream(std::declval<A0>()))>;
  template<class, class A0>
  static auto test_stream(long) -> std::false_type;
} // detail::

template<class T, class Arg>
struct has_stream : decltype(detail::test_stream<T, Arg>(0)){};

struct X{ void stream(int){} };
struct Y{};

static_assert(has_stream<X, int>() == true, "fail X");
static_assert(has_stream<Y, int>() == false, "fail Y");

int main(){}