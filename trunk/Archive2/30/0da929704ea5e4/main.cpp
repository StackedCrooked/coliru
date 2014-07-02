#include <cstdio>
#include <string>
#include <type_traits>

template<typename T, size_t = sizeof std::declval<std::enable_if<std::is_integral<T>::value, T>::type>()>
inline auto f(T) // wtf is with this syntax??/
    -> void
{
    puts("addable");
}

template<typename...T>
inline void f(T&&......) {
  puts("not addable");
}

auto g = [](auto......) -> auto { return 0; } ;

int main() {
  f(0);
  f("asd");
  f(std::string("asd"));
}
