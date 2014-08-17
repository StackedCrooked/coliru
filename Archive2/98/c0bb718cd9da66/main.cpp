#include <iostream>
#include <complex>
#include <type_traits>

namespace detail {
  template<typename T, class Enable = void> class vector;
  
  template<typename T>
  class vector<T, typename std::enable_if<T(0) + T(1) == T(1) && T(1) * T(1) == T(1)>::type> {
    // ...
  };
  template<typename T, template<typename> class C>
  class vector<C<T>, typename std::enable_if<T(0) + T(1) == T(1) && T(1) * T(1) == T(1)>::type> {
    // ...
  };
}

struct foo {};

int main() {  
  detail::vector<int> iv;
  detail::vector<double> dv;
  detail::vector<std::complex<double>> cv;
  // detail::vector<foo> fv; // will not compile
}