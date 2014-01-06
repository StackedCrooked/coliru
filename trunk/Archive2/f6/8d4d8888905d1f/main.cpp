#include <cstddef>
#include <tuple>

// Approximation of index_sequence stuff from C++14
template <std::size_t... I> struct index_sequence {};
template <std::size_t N, std::size_t... I>
struct make_index_sequence : make_index_sequence<N-1,N-1,I...> {};
template <std::size_t... I>
struct make_index_sequence<0, I...> : index_sequence<I...> {};

// Actual answer
template <typename T, typename F, std::size_t... I>
auto tmap(T&& t, F&& f, index_sequence<I...>) ->
  std::tuple<decltype(f(std::get<I>(std::forward<T>(t))))...> {
  return std::tuple<decltype(f(std::get<I>(std::forward<T>(t))))...>{
    f(std::get<I>(t))...
  };
}

template <typename T, typename F>
auto tmap(T&& t, F&& f) ->
decltype(tmap(std::forward<T>(t),
              std::forward<F>(f),
              make_index_sequence<
                std::tuple_size<
                  typename std::decay<T>::type
                >::value>{})) {
  return tmap(std::forward<T>(t),
              std::forward<F>(f),
              make_index_sequence<
                std::tuple_size<
                  typename std::decay<T>::type
                >::value>{});
}

#include <iostream>

struct some_functor {
  template <typename T>
  bool operator() (const T t) const {
    return t > T{2};
  }
};

struct some_other_functor {
  template <typename T>
  T operator() (const T t) const {
    return t + T{1};
  }
};

template <typename... T, std::size_t... I>
void print(const std::tuple<T...>& t, index_sequence<I...>) {
  std::cout << '(';
  auto _{0, (std::cout << std::get<I>(t) << ',', 0)...};
  (void)_;
  std::cout << std::get<sizeof...(T) - 1>(t) << ")\n";
}

template <typename... T>
void print(const std::tuple<T...>& t) {
  print(t, make_index_sequence<sizeof...(T)-1>{});
}

int main() {
  std::tuple<float, int> t(3, 2);
  print(tmap(t, some_functor()));
  print(tmap(t, some_other_functor()));
}
