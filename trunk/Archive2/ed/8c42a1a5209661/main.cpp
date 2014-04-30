#include <iostream>
#include <functional>
#include <utility>
#include <type_traits>

template<int... N> struct int_seq { };

namespace impl {
  template<int N, int... Ns> struct make_int_seq : make_int_seq<N-1, N-1, Ns...> { };
  template<int... Ns> struct make_int_seq<0, Ns...> { using type = int_seq<Ns...>; };
}

template<int N>
using make_int_seq = typename impl::make_int_seq<N>::type;

/***********************************************************************************/

template<int N>
struct fake_placeholder { };


namespace std {
  template<int N>
  struct is_placeholder<fake_placeholder<N>> : std::integral_constant<int, N> { };
}

/***********************************************************************************/

template <typename T>
struct func;

template <typename Ret, typename... Args>
struct func<Ret (Args...)>
{
  template <typename T, typename I, typename... Bound>
  void reset(T target, I invoker, Bound&&... bound) {
    reset_impl (target, invoker, make_int_seq<sizeof... (Args) - sizeof...(Bound)> {}, std::forward<Bound> (bound)...);
  }

  template<class T, class I, class... Bs, int... Ns> 
   void reset_impl (T x, I a, int_seq<Ns...>, Bs&&... bs ) {
    auto f = std::bind(x, a, std::forward<Bs>(bs)..., fake_placeholder<Ns+sizeof...(Bs)> {}...);
    f(1, 2);
    //f (1); // NOTE: just a simple test
   }
};

struct test
{
  void bar(int a, int b) {
    std::cout << a << " " << b << std::endl; 
  }
};

int main()
{
  test t;
  func<void (int, int)> f;
  f.reset(&test::bar, &t);
}