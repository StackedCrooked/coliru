#include <type_traits>

template<bool B, class T = void>
struct my_enable_if {};
 
template<class T>
struct my_enable_if<true, T> { typedef T type; };

template<typename T>
using my_enable_if_t = typename my_enable_if<T::value, int>::type;

template<typename T>
using enable_if = typename std::enable_if<T::value, int>::type;

template<typename T, my_enable_if_t<std::is_integral<T>> = 0>
void f(const T&) {}

template<typename T, enable_if<std::is_integral<T>> = 0>
void g(const T&) {}

int main() {
    f(1.0);
    g(1.0);
}