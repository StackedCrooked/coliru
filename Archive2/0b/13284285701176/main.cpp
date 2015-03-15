#include <iostream>
#include <type_traits>

template <class T> using foo = T*;

template <class T> using bar = T*;

template <class T> using buz = foo<T>;

template <typename T>
struct Template{};

template <typename T>
using Alias = Template<T>;

template
    <
        template <typename>
        class T1,
        template <typename>
        class T2
    >
struct is_same_template : std::false_type{};

template
    <
        template <typename>
        class T
    >
struct is_same_template<T, T> : std::true_type{};

#define CHECK_IS_SAME(T1, T2) \
    std::cout << #T1 " == " #T2 ": " << is_same_template<T1, T2>::value << std::endl

int main()
{
    std::cout << std::boolalpha;
    CHECK_IS_SAME(foo, bar);
    CHECK_IS_SAME(foo, buz);
    CHECK_IS_SAME(bar, buz);
}