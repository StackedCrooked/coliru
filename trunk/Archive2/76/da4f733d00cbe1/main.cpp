#include <cstdio>
#include <type_traits>

template<typename T, size_t = sizeof(std::declval<std::enable_if<std::is_integral<T>::value, T>::type>(), true)>
inline void f(T) 
{
  puts("integral");
}

inline void f(...) {
  puts("not an integral");
}

int main() {
  f(0);
  f("asd");
}
