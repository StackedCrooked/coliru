#include <type_traits>

template<typename It>
void f(It begin, It end) {
    static_assert(std::is_pointer<It>::value, "..");
}

int main() {
    int x[] = { 1, 2, 3 };
    f(x, x + sizeof(x));
}