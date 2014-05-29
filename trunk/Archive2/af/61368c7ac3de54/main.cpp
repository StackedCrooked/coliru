#include <type_traits>

template<typename T>
void stacktrace() {
    static_assert(std::is_same<T, signed char>::value, "...");
    static_assert(std::is_same<T, unsigned char>::value, "...");
}

int main() {
    stacktrace<char>();
}