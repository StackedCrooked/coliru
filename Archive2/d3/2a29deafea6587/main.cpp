#include <iostream>
#include <string>
#include <vector>
#include <tuple>

struct A {
    void foo() const { std::cout << "A" << std::endl;}
};

struct B {
    void foo() const { std::cout << "B" << std::endl;}
};

namespace std {
  template<int I, class Tuple, typename F> struct for_each_impl {
    static void for_each(const Tuple& t, F f) {
      for_each_impl<I - 1, Tuple, F>::for_each(t, f);
      f(get<I>(t));
    }
  };
  template<class Tuple, typename F> struct for_each_impl<0, Tuple, F> {
    static void for_each(const Tuple& t, F f) {
      f(get<0>(t));
    }
  };
  template<class Tuple, typename F>
  void for_each(const Tuple& t, F f) {
    for_each_impl<tuple_size<Tuple>::value - 1, Tuple, F>::for_each(t, f);
  }
}

int main()
{
    auto t = std::make_tuple(A(),B(),A());
    std::for_each(t,[](auto &&t){t.foo();});
}
