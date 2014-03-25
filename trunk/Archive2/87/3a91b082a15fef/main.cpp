#include <type_traits>

namespace impl { struct unimplemented; }

impl::unimplemented f (...);

// ----------------------------------------------------------------------------

namespace impl {
  template<class... Ts>
  struct hgf {

    template<class U>
    struct Hack { operator U (); };

    template<class... Us>
    static decltype (f (Hack<Us> {}...)) plash_hack ();

    using reversed_type = std::is_same<impl::unimplemented, decltype (plash_hack<Ts...> ())>;
    using type = std::integral_constant<bool, reversed_type::value == false>;
  };
}

// ----------------------------------------------------------------------------

template<class... Ts>
struct has_global_f : impl::hgf<Ts...>::type { };

// ----------------------------------------------------------------------------

struct A {};

template<typename T> void f (T, A&); // comment to trigger assert

// ----------------------------------------------------------------------------


int main() {
  static_assert (has_global_f<int, A&>::value, "!!");
}