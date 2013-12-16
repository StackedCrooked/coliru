#include <iostream>

namespace foo {
    
template<typename T> struct Wrap  { T next;  };
template<typename T> struct Final { T value; };

template<typename R, typename T>
R get_value (T x) {
  return get_value<R> (x.next);
}

template<typename R, typename _>
R get_value (Final<_> x) {
  return x.value;
}


void bar()
{
  Wrap<Wrap<Final<int>>> x = {{{ 123 }}};

  std::cout << get_value<int> (x) << " ";
}

}

int main() {
    foo::bar();
}
