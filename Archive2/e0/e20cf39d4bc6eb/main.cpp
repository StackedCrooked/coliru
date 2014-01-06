#include <type_traits>
#include <iostream>

template<typename T, typename U>
struct helper {
    helper (T const& x, U const& y) : x(x), y(y) {}

    T const& operator()(std::true_type ) { return x; }
    U const& operator()(std::false_type) { return y; }

    T const& x; U const& y;
};

template<typename T, typename U>
helper<T, U> make_helper (T const& true_handler, U const& false_handler)
{
  return { true_handler, false_handler };
}

template<bool B>
using selector = std::conditional<B, std::true_type, std::false_type>;

template<typename T, typename... Args>
size_t sum (T val, Args... args)
{
  return make_helper (
    [&](auto x, auto... xs) { return x + sum (xs...); }, // multi
    [&](auto x)             { return x;                }  // single
  ) (
    typename selector<sizeof...(args) != 0>::type { }
  ) (val, args...);

}

int
main (int argc, char *argv[])
{
    std::cout << sum (1,2,3,100);
}