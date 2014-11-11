#include <iostream>

template <typename Ty>
class has_foo_function {
  typedef char yes[1];
  typedef char no[2];

  template <typename Inner>
  static yes& test(Inner *I, decltype(I->foo()) * = nullptr);

  template <typename>
  static no& test(...);

public:
  static const bool value = sizeof(test<Ty>(nullptr)) == sizeof(yes);
};

struct Bar {};
struct Baz {
  void foo();
};

int main() {
  std::cout << std::boolalpha << has_foo_function<Bar>::value
            << " " << has_foo_function<Baz>::value;
}