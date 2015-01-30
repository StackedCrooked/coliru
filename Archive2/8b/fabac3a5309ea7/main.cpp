#include <iostream>
#include <type_traits>

template <size_t N>
void foo(const char (&s)[N]) {
    std::cout << "array, size=" << N-1 << std::endl;
}

template <typename T>
typename std::enable_if<std::is_same<T, char const*>{}>::type foo(T s) {
    std::cout << "raw, size=" << strlen(s) << std::endl;
}
int main()
{
    foo("hello"); // prints array, size=5
}

