// author: Filip Roséen <filip.roseen@gmail.com>

#include <type_traits>

template<int N>
using ic = std::integral_constant<int, N>;

// -----------------------------------------
// DECLARE FRIEND FUNCTION
// -----------------------------------------

template<class Tag, int N = 3>
struct declare : declare<Tag, N-1> {
  friend constexpr int adl_func (Tag, ic<N>);
};

template<class Tag>
struct declare<Tag, -1> { /* intentionally left blank */ };

// -----------------------------------------
// DEFINE FRIEND FUNCTION UPON INSTANTIATION
// -----------------------------------------

template<class Tag, int N, int Value>
struct implement : declare<Tag, N> {
  friend constexpr int adl_func (Tag, ic<N>) {
    return Value;
  }
};


// -----------------------------------------
// FINDERS (through SFINAE)
// -----------------------------------------

template<class Tag>
constexpr int get_impl (int, Tag, ic<-1>) {  // (A), fallback
  return -1; 
}

template<class Tag, int N, int = adl_func (Tag{}, ic<N> {})> // (B), we found a defined function! [SFINAE]
constexpr int get_impl (int, Tag, ic<N>) {
  return adl_func (Tag {}, ic<N> {});
}

template<class Tag, int N>
constexpr int get_impl (float, Tag, ic<N>, int C = get_impl (0, Tag {}, ic<N-1> {})) { // try next if (B) failed!
  return C; 
}

// -----------------------------------------
// ACCESSOR
// -----------------------------------------

template<class Tag>
int constexpr get (int C = get_impl (0, Tag {}, ic<3> {})) {
  return C;
}

// -----------------------------------------
// POC
// -----------------------------------------

#include <iostream>

class Foo : declare<Foo> { };
class Bar : declare<Bar> { };

int main () {
  {
    implement<Foo, 0, 42> {};
    implement<Bar, 0, 41> {};

    int constexpr a = get<Foo> (); static_assert (a == 42, "!!");
    int constexpr b = get<Bar> (); static_assert (b == 41, "!!");

    std::cout << a << "\t" << b << std::endl;
  }

  {
    implement<Foo, 1, 1337> {};
    implement<Foo, 2, 1338> {};

    implement<Bar, 1, 8331> {};

    int constexpr a = get<Foo> (); static_assert (a == 1338, "!!");
    int constexpr b = get<Bar> (); static_assert (b == 8331, "!!");

    std::cout << a << "\t" << b << std::endl;
  }

  {
    implement<Foo, 3, 100> {};

    int constexpr a = get<Foo> (); static_assert (a == 100, "!!");
    int constexpr b = get<Bar> (); static_assert (b == 8331, "!!");

    std::cout << a << "\t" << b << std::endl;
  }
}