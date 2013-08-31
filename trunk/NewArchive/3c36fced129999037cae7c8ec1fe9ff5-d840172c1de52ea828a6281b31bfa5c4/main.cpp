#include <tuple>

template<typename T> struct ignore;

namespace detail {
    
template<typename Acc, typename... T>
struct ignore_filter { using type = Acc; };

template<typename... Acc, typename Head, typename... Tail>
struct ignore_filter<std::tuple<Acc...>, Head, Tail...>: ignore_filter<std::tuple<Acc..., Head>, Tail...> {};

template<typename... Acc, typename Head, typename... Tail>
struct ignore_filter<std::tuple<Acc...>, ignore<Head>, Tail...>: ignore_filter<std::tuple<Acc...>, Tail...> {};
    
} // detail

template<typename... T> struct ignore_filter: detail::ignore_filter<std::tuple<>, T...> {};

#include <type_traits>

int main()
{
  struct T;
  struct U;

  static_assert (
    std::is_same<
      std::tuple<T,U,U>,
      ignore_filter<ignore<int>, T, ignore<int>, U, ignore<int>, U>::type
    >::value,
    "FCUK"
  );
}