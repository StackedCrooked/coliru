#include <type_traits>

namespace impl { struct unimplemented; }

template<class... P>
impl::unimplemented f (P...);

// ----------------------------------------------------------------------------

namespace impl {
  template<class... Ts>
  struct hgf {

    /*template<class U>
    struct Hack { operator U (); };*/

    template<class... Us>
    static decltype (f (std::declval<Us>()...)) plash_hack ();

    using reversed_type = std::is_same<impl::unimplemented, decltype (plash_hack<Ts...> ())>;
    using type = std::integral_constant<bool, reversed_type::value == false>;
  };
}

// ----------------------------------------------------------------------------

template<class... Ts>
struct has_global_f : impl::hgf<Ts...>::type { };

// ----------------------------------------------------------------------------

struct A {};

template<class T, class U> void f (T, U&);
//template<class T> void f (T, A&);
//void f(int, A&);

// ----------------------------------------------------------------------------


int main() {
  static_assert (has_global_f<int, A&>::value, "!!");
}
