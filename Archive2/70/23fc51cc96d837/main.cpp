#include <type_traits>

void func (int) { }

template<class U>
void func (U) {
  static_assert (std::is_same<class NaN, U> {}, "!!");
}

int main () {
  func (int {123});
}