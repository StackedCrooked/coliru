#include <type_traits>

template<class T>
struct A {
  void func (int) {};

  template<class U> void func (U) {
    static_assert (std::is_same<class NaN, T> {}, "!!");
  }
};

int main () {
  A<void> x;

  x.func (int { 0 });
}