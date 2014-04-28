#include <type_traits>
#include <iostream>
#include <string>

struct foo {
    template<typename T, typename=
      typename std::enable_if<
        std::is_same<typename std::remove_cv<T>::type, char>{}
      >::type>
    foo(T* const&) { std::cout << "pointer\n"; }
    template<int N>
    foo(char const (&)[N]) { std::cout << "array\n"; }
    foo(std::string) { std::cout << "string\n"; }
};

int main()
{
    // arrays
    char a[12]{};
    foo{a};
    const char ca[10]{};
    foo{ca};
    foo{"hello"};

    // pointers
    char* p{};
    foo{p};
    const char* cp{};
    foo{cp};
    char* const pc{};
    foo{pc};
    foo{&a[0]};
    foo{ca+4};

    // strings (Verify SFINAE)
    foo{std::string("foo")};
}