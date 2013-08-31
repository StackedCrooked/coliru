#include <type_traits>
#include <iostream>

template <typename T>
struct not_ : std::integral_constant<bool, !T::value> {};

void impl(std::true_type) { std::cout << "true\n"; }
void impl(std::false_type) { std::cout << "false\n"; }

template<typename T>
void dispatch(T&& val)
{
  impl(not_<std::is_integral<T>>());
}

int main()
{
  dispatch(10);
  dispatch("");
}