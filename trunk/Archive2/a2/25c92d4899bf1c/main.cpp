#include <cstdio>
#include <string>
#include <type_traits>

template<typename T, size_t = sizeof std::declval<std::enable_if<std::is_integral<T>::value, T>::type>()>
inline void f(T) 
{
    puts("addable");
}

template<typename...T>
inline void f(T&&......) { // wtf is with this syntax??/
  puts("not addable");
}

int main() {
  f(0);
  f("asd");
  f(std::string("asd"));
}
