#include <cstddef>
#include <tuple>
#include <type_traits>
#include <utility>

namespace impl {

template<size_t N>
struct _apply {
  template<typename F, typename T, typename... A>
  static inline auto _(F&& f, T&& t, A&&... a) {
    return _apply<N-1>::_(::std::forward<F>(f), ::std::forward<T>(t), ::std::get<N-1>(::std::forward<T>(t)), ::std::forward<A>(a)...);
  }
};

template<>
struct _apply<0> {
  template<typename F, typename T, typename... A>
  static inline auto _(F&& f, T&&, A&&... a) {
    return ::std::forward<F>(f)(::std::forward<A>(a)...);
  }
};

} // namespace impl

template<typename F, typename T>
inline auto apply(F&& f, T&& t) {
  return impl::_apply< ::std::tuple_size<typename ::std::decay<T>::type>::value>::_(::std::forward<F>(f), ::std::forward<T>(t));
}

extern "C" {

extern int foo(char, bool);
extern ::std::tuple<char, bool> bar();

int test1() {
  return apply(foo, bar());
}

int test2() {
  auto a = bar();
  return foo(::std::get<0>(::std::move(a)), ::std::get<1>(::std::move(a)));
}

}
