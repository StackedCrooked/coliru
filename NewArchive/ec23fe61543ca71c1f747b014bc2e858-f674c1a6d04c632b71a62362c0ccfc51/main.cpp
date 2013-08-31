#include <algorithm>
#include <tuple>
#include <iostream>

template<unsigned...>
struct indices { };

template<unsigned N, unsigned... Ns>
struct make_indices {
  using type = typename make_indices<N-1, N, Ns...>::type;
};

template<unsigned... Ns>
struct make_indices<0, Ns...> {
  using type = indices<0, Ns...>;
};

/*
 * */

template<typename Ret, typename... Args, unsigned... Ns>
Ret
call_with (Ret(*p)(Args...), std::tuple<Args...> args, indices<Ns...>)
{
  return p (std::get<Ns> (args) ... );
}

/*
 * */

template<typename H, typename... Args>
struct find_specialization;

template<typename T, typename... Ts, typename... Args>
struct find_specialization<std::tuple<T, Ts...>, Args...>
  : find_specialization<std::tuple<Ts...>, Args...>
{
  using find_specialization<std::tuple<Ts...>, Args...>::operator ();
  using find_specialization<std::tuple<Ts...>, Args...>::find_specialization;

  T operator () (T(*p)(Args...)) {
    return call_with (p, this->args, typename make_indices<sizeof... (Args)-1>::type {});
  }
};

template<typename... Args>
struct find_specialization<std::tuple<>, Args...>
{
  find_specialization (std::tuple<Args...> t) : args (t) { }

  void operator () (...);

  std::tuple<Args...> args;
};

/*
 * */

template<typename T, typename... Args>
auto
call_with_range_of (T&& container, Args&&... args)
  -> find_specialization<
    std::tuple<decltype (std::begin (container)), decltype (std::end (container)), Args...>,
    decltype (std::begin (container)),
    decltype (std::end   (container)),
    Args...
  >
{
  return {
    std::forward_as_tuple (std::begin (container), std::end (container), args...)
  };
}

/*
 * */

int
main (int argc, char *argv[])
{
  std::cerr << call_with_range_of (std::vector<int> {1, 2, 3}, 10) (std::accumulate ) << "\n";
}