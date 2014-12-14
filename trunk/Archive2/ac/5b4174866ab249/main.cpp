#include <iostream>
#include <string>

template <typename T>
struct replace_type {
    using type = T;
};

template <>
struct replace_type<long> {
    using type = double;
};

template <typename... Args>
void
real_foo(Args... args) {
    std::cout << __PRETTY_FUNCTION__ << '\n';
}

template <typename... Args>
void
foo(Args... args) {
    real_foo<typename replace_type<Args>::type...>(args...);
}

int
main() {
    foo(5, 6l, 5, 6l);
}
