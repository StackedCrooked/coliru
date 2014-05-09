#include <utility>
#include <cstddef>

template<typename T>
using enable = typename std::enable_if<sizeof(T)>=0>::type;

template<typename T, typename = void>
struct A;

template<typename T>
struct A<T, enable<T>>{ void f(); };

template<typename T>
void A<T, enable<T>>::  // compiles
// void A<T>::  // does not compile
f() { }

int main()
{
    A<int>();
}

