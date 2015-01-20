
#include <type_traits>
template<class...>
struct voider { using type = void; };
template<class... Ts>
using void_t = typename voider<Ts...>::type;

template<class T, class = void>
struct has_foo : std::false_type
{
};

template<class T>
struct has_foo<T, void_t<typename T::template foo<int>>> : std::true_type {};

struct with_foo
{
  template<class T> struct foo {};
};

struct with_foo_default
{
  template<class T, class = int> struct foo {};
};


struct with_foo_2param
{
  template<class T, class> struct foo {};
};


struct with_foo_sfinae
{
  template<class T, class = typename std::enable_if<!std::is_same<T, int>::value>::type> struct foo {};
};


struct without_foo {};

int main()
{
  static_assert(has_foo<with_foo>::value, "");
  static_assert(has_foo<with_foo_default>::value, "");
  static_assert(!has_foo<with_foo_sfinae>::value, "");
  static_assert(!has_foo<with_foo_2param>::value, "");
  static_assert(!has_foo<without_foo>::value, "");

  return 0;
}