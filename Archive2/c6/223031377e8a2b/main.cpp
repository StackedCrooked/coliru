#include <iostream>
#include <type_traits>

namespace impl { struct unimplemented; }

impl::unimplemented f (...);

// ----------------------------------------------------------------------------

template<class Impl>
struct Serialize {

  template<class U>
  struct Hack { operator U (); };

  template<class... Us>
  static decltype (f (Hack<Us> {}...)) plash_hack ();

  template<class... Ts>
  using use_mem_f = std::is_same<impl::unimplemented, decltype (plash_hack<Ts...> ())>;

  template<
    class U,
    class X = typename std::enable_if<use_mem_f<Impl&, U&>::value == false>::type
  > void do_it (U& val) {
    f (Impl {}, val);
  }

  template<
    class U,
    class = typename std::enable_if<use_mem_f<Impl&, U&>::value == true>::type
  > void do_it (U const& val) {
    Impl {}.f (val);
  }
};

// ----------------------------------------------------------------------------

struct A {};
struct B {
  template<class T>
  void f (T&) { std::cerr << "B::f" << std::endl; }
};

template<typename T>
void f (T, A&) { std::cerr << "::f" << std::endl; }

// ----------------------------------------------------------------------------


int main() {
  A a;
  B b;

  Serialize<A> {}.do_it (a);
  Serialize<B> {}.do_it (b);
}