#include <type_traits>

namespace detail{
  template<class T, class A0>
  static auto test_stream(A0&& a0, int) -> decltype(void(std::declval<T>().stream(a0)));
  template<class, class A0>
  static char test_stream(A0&&, long);
} // detail::

template<class T, class Arg>
struct has_stream : std::is_void<decltype(detail::test_stream<T>(std::declval<Arg>(), 0))>{};

struct X{ void stream(int){} };
struct Y{};

static_assert(has_stream<X, int>() == true, "fail X");
static_assert(has_stream<Y, int>() == false, "fail Y");

int main(){}