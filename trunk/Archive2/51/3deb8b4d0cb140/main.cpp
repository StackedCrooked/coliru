#include <utility>
#include <cstddef>

template<typename T>
using enable = typename std::enable_if<sizeof(T)>=0>::type;

template<typename T, typename = void>
struct my_class;

template<typename T>
struct my_class<T, enable<T>>{ void f(); };

template<typename T>
void my_class<T, enable<T>>::  // compiles
// void my_class<T>::  // does not compile
f() { }

int main()
{
    my_class<int>();
}

