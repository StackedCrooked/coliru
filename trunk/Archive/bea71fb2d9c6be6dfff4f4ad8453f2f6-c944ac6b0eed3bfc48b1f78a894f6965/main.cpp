#include <type_traits>
#include <iostream>

template <typename T, T value>
inline constexpr std::integral_constant<T, value == T{}>
operator ! (std::integral_constant<T, value>)
{ return {}; }

void impl(std::true_type) { std::cout << "true\n"; }
void impl(std::false_type) { std::cout << "false\n"; }

template<typename T>
void dispatch(T&&)
{
  impl(!std::is_integral<T>());
}

int main()
{
  dispatch(10);    // calls impl(std::true_type)
  dispatch("");    // calls impl(std::false_type)
}
