#include <type_traits>

template<typename>
struct always_false : std::false_type {};

struct foo {
    template<typename T>
    foo(T) {
        static_assert(always_false<T>::value, "nope");
    }
};

static_assert(not std::is_constructible<foo, int>::value, "but it isn't constructible!");

int main() {}