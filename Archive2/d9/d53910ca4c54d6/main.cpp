#include <type_traits>
#include <algorithm>

template<typename T>
struct CopyConstructible {
    static constexpr bool check() {
        static_assert(std::is_copy_constructible<T>(), "Concept Violation: Not CopyConstructible");
        return true;
    }
};

struct f {
    f(const f&) = delete;
    f() = default;
};

template<typename T>
void g(T&& t) {
    CopyConstructible<T>::check(); // why?
}

int main() {
    f lol;
    g(std::move(lol));
}