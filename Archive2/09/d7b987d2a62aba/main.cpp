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

void func (std::string) {
  std::cout << "func (std::string)\n";
}


int
main (int argc, char *argv[])
{
  func (char        { });
  func (std::string { });                                 // callable<T>::value in func (T) yields true
  std::cout << callable<std::string>::value << std::endl; // this yields false, why?
}