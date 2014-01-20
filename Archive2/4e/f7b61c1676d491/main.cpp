#include <iostream>


namespace nn {
template<typename T>
struct aa {
};

template<typename T>
aa<T> f(T) {
  std::cout << "one-arg" << std::endl;
  return {};
}

template<typename T>
aa<T> f(T, T) {
  std::cout << "two-arg" << std::endl;
  return {};
}
}


namespace mm {
// how do I bring the nn::f function templates to this namespace with out using namespace nn;
// in such manner that when called through mm::f they return nn::a<double>? if it wasn't overloaded I could do:
// constexpr auto f = &nn::f<double>;
// but that's a variable and can't have more than one variable with the same name
using nn::f;
}


int
main() {
  mm::f(0);
  mm::f(0, 1);
}

