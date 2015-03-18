#include <type_traits>
#include <cassert>

struct bar
{
  using baz = int;
};

template<class T> struct is_bar : std::false_type {};
template<> struct is_bar<bar> : std::true_type {};

template<class Bar>
struct baz_type
{
  using type = typename Bar::baz;
};

template<
    class T,
    typename=typename std::enable_if<is_bar<T>::value>::type,
    typename=typename std::enable_if<std::is_integral<typename baz_type<T>::type>::value>::type
>
int foo(T x)
{
  return 7;
}

template<
    class T,
    typename=typename std::enable_if<!is_bar<T>::value>::type
>
int foo(T x)
{
  return 13;
}

int main()
{
  assert(foo(bar()) == 7);
  assert(foo(0) == 13);

  return 0;
}
