namespace impl {
  template<char... S> struct str {
    static constexpr char data[] = { S..., '\0' };
  };

  template<char... S>
  constexpr char str<S...>::data[];


  template<char C, int N, char const * Ptr, char... S>
  struct explode_ { typedef typename explode_<*(Ptr+N+1), N+1, Ptr, S..., C>::list list; };

  template<int N, char const * Ptr, char... S>
  struct explode_<'\0', N, Ptr, S...> { typedef str<S...> list; };

  template<char const * Ptr>
  using explode = typename explode_<*Ptr, 0, Ptr>::list;


  template<class...>
  struct join { typedef str<> result; };

  template<char... A, char... B, class... Ts>
  struct join<str<A...>, str<B...>, Ts...> {
    typedef typename join<str<A..., ',', ' ', B...>, Ts...>::result result;
  };

  template<char... A>
  struct join<str<A...>> {
    typedef str<A..., '\n'> result;
  };
}

#include <cstddef>

template<class T> struct format_m;
template<class T> struct format_m<T*>      { static constexpr char fmt[] = "%p";  };
template<> struct format_m<std::nullptr_t> { static constexpr char fmt[] = "%p";  };
template<> struct format_m<int          >  { static constexpr char fmt[] = "%d";  };
template<> struct format_m<float        >  { static constexpr char fmt[] = "%.3f";  };
template<> struct format_m<double       >  { static constexpr char fmt[] = "%.3f";  };
template<> struct format_m<char const*  >  { static constexpr char fmt[] = "\"%s\"";  };
template<> struct format_m<char         >  { static constexpr char fmt[] = "'%c'";  };
template<> struct format_m<unsigned long>  { static constexpr char fmt[] = "%lu"; };


template<class... Ts>
constexpr char const * build_fmt () {
  return impl::join<impl::explode<format_m<Ts>::fmt>...>::result::data;
}

/* ...................................... */

#include <cstdio>
#include <type_traits>

template<class... Ts>
void auto_printf (Ts... args) {
  std::printf (build_fmt<Ts...> (), args...);
}

int main () {
  auto_printf ('A', "hello world", nullptr, "!!!");
  auto_printf ( -1,          -1ul,  3.1415, 7/3.f, new int);
}