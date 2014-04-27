#include <type_traits>
#include <iostream>

struct foo
{
    template<class T, class = typename std::enable_if< std::is_same<T, char const>{} >::type>
    foo(T* const&) { std::cout << "pointer\n"; }
    template<int N>
    foo(char const (&)[N]) { std::cout << "array\n"; }
};

int main()
{
    foo("hello");
}