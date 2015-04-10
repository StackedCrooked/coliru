#include <string>
#include <type_traits>

template<class D>
struct Base {
  friend auto func (D);
};

template<class D, class Ret>
struct impl : Base<D> {
  friend auto func (D) {
    return Ret {};
  }
};

#include <vector>
#include <string>

struct A : Base<A> { };
struct B : Base<B> { };

int main () {
  impl<A,      std::string> {};
  impl<B, std::vector<int>> {};

  static_assert (
    std::is_same<decltype(func(A{})), std::string> {},
    "!!!"
  );

  static_assert (
    std::is_same<decltype(func(B{})), std::vector<int>> {},
    "!!!"
  );
}