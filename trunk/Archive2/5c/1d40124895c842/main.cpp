#include <type_traits>

template<typename T>
void f(T&& t) {
    static_assert(std::is_array<typename std::remove_reference<T>::type>::value, "...");
}

int main() {
    int x[] = { 1, 2, 3 };
    f(x);
}