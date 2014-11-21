#include <type_traits>

template<typename T>
void foo(T &&t) {
    static_assert(std::is_const<std::remove_reference_t<decltype(t)>>{});
}

int main() {
    const int &r = 2;
    foo(r);
}