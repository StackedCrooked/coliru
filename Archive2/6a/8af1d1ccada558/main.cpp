#include <type_traits>

namespace impl {

  template<class T, class... Ts>
  struct hmf {
    template<class U>
    static auto memfun_owner (void(U::*)(Ts...)) -> U;

    template<class U>
    using is_t = typename std::is_same<T, U>::type;

    template<class U> using has_tp_f = is_t<decltype (memfun_owner (&U::template f<Ts...>))>;
    template<class U> using has_nt_f = is_t<decltype (memfun_owner (&U::         f       ))>;

    template<class U> static has_tp_f<U>     test (int);
    template<class U> static has_nt_f<U>     test (int);
    template<class U> static std::false_type test (...);

    typedef decltype (test<T> (123)) type;
  };
}

template<class T, class... Ts>
struct has_member_f
  : impl::hmf<T, Ts...>::type
{ };

//
// ----------------------------------------

struct B {
  template<class U> void f (U&);
};

struct D : B {
  // ...
};


int
main ()
{
  static_assert (has_member_f<D, int&>::value, "!!");
}