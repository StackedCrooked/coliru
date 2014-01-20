#include <type_traits>
#include <utility>

int _a;

template <typename T> auto set_a(T&& a) -> decltype((void)(_a = std::forward<T>(a))) { _a = std::forward<T>(a); }

int main() {
    set_a(12);
    set_a(3.14);
    set_a("feep");
}
