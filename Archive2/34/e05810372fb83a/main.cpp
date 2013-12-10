#include <iostream>

template<typename T> struct Wrap  { T next;  };
template<typename T> struct Final { T value; };

namespace N {

template<typename R, typename T>
R get_value (T x) {
  return get_value<R> (x.next);
}

template<typename R, typename _>
R get_value (Final<_> x) {
  return x.value;
}

}

int
main (int argc, char *argv[])
{
  Wrap<Wrap<Final<int>>> x = {{{ 123 }}};

  std::cout << N::get_value<int> (x) << " ";
}