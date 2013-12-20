#include <iostream>
#include <string>
#include <vector>
#include <type_traits>

void func (int) {
  std::cout << "func (int)\n";
}

template<typename... Ts>
struct callable {
  template<typename... Us>
  static std::true_type test (decltype (func (std::declval<Us> ()...), int { }));

  template<typename...>
  static std::false_type test (...);

  enum { value = decltype (test<Ts...> (0))::value };
};

template<
  typename T,
  typename std::enable_if<callable<T>::value == false>::type * = nullptr
>
void func (T) {
  std::cout << "func (T)\n";
}

void func (double) {
  std::cout << "func (double)\n";
}

int
main (int argc, char *argv[])
{
  // callable<float>::value will yield true,
  // not because of `func(double)`, but because of `func(int)`
    
  // when the template has been taken out of the equation
  // func (double) will be selected BUT if we didn't have
  // func (int) declared BEFORE the template definition
  // func (T) would have been called

  func (float {});
}