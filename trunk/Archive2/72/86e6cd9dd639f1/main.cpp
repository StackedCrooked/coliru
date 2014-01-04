#include <type_traits>
#include <iostream>

template<bool B>
struct static_if {
  template<typename T, typename F, typename... Args>
  auto operator() (T const& t, F const& f, Args... args) {
    return t (args...);
  }
};

template<>
struct static_if<false> {
  template<typename T, typename F, typename... Args>
  auto operator() (T const& t, F const& f, Args... args) {
    return f (args...);
  }
};