#include <cstdio>
#include <type_traits>

template<typename E>
typename std::enable_if<std::is_enum<E>::value, std::underlying_type<E>>::type::type
to_integral(E e) {
  return static_cast<typename std::underlying_type<E>::type>(std::move(e));
}
template<typename E>
typename std::enable_if<!std::is_enum<E>::value&&std::is_integral<E>::value,E>::type
to_integral(E e) {
  return std::move(e);
}

enum class MyEnum : int { A = 5 };

int main()
{
  auto a = to_integral(42);
  auto b = to_integral(MyEnum::A);
  printf("%d\n", a);
  printf("%d\n", b);
}