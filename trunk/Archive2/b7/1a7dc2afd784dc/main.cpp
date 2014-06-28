#include <type_traits>

template<bool b, class T>
using enable_if_t = typename std::enable_if<b, T>::type;

template<bool b, class T>
using disable_if_t = typename std::enable_if<!b, T>::type;

template<typename T, enable_if_t<std::is_same<T, int>::value, T> = 1>
int a(){return 0;}

template<typename T, disable_if_t<std::is_same<T, int>::value, T> = T{}>
double a(){return 0.0;}

int main() {
    auto x = a<int>();
}