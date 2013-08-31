#include <type_traits>

template <typename Test, typename Arg>
struct trait_of : decltype(Test::template test<Arg>(0)) {};


// silly example
struct has_arithmetic_type_test {
    template <typename T>
    std::is_arithmetic<typename T::type> test(int);
    template <typename>
    std::false_type test(...);
};

template <typename T>
struct has_arithmetic_type : trait_of<has_arithmetic_type_test, T> {};

struct foo {
    typedef int type;
};
static_assert(has_arithmetic_type<foo>::value, "yay");
static_assert(!has_arithmetic_type<int>::value, "yay");

#include <stdio.h>
int main() { perror("Error"); }
