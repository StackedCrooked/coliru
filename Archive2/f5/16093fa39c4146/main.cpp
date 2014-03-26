
template<class T, int... Ns>
struct plash_request {
  constexpr plash_request ()
    : array { T (Ns)... }
  { };

  T array[sizeof... (Ns)];
};

// ----------------------------------------------------------------------------

namespace impl {
  template<int...> struct int_seq { };

  template<int N, int... Ns>
  struct int_seq_ : int_seq_<N-1, N, Ns...> { };

  template<int... Ns>
  struct int_seq_<0, Ns...> { using type = int_seq<0, Ns...>; };

  template<class T, int... Ns>
  plash_request<T, Ns...> plash_creator (int_seq<Ns...>);
}

// ----------------------------------------------------------------------------

template<int N>
using int_seq_creator = typename impl::int_seq_<N>::type;

template<class T, int N>
using create_plash = decltype (impl::plash_creator<T> (int_seq_creator<N> {}));
  
// ----------------------------------------------------------------------------

int
main (int argc, char *argv[])
{
  struct Obj {
    constexpr Obj (int i)
      : idx (i)
    { }

    int idx;
  };

  constexpr create_plash<Obj, 10> foo;

  static_assert (foo.array[5].idx == 5, "!!");
}