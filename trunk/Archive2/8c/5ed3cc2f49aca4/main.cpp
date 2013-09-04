#include <type_traits>
#include <set>
#include <iostream>

enum class enabler {};

template<typename T>
struct requires {
    static_assert(T::value, "Check failed");
    using type = enabler;
};

template<typename T>
using Requires = typename requires<T>::type;

template<typename T, Requires<std::is_integral<T>>...>
void f(T t) {
    // Requires<std::is_integral<T>>{}; // single error if upper is removed
    std::set<T> f;
    f.insert(t);
}

struct a{};

int main() {
    f(a());
}