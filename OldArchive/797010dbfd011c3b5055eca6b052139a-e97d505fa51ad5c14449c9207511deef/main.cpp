#include <iostream>

template <typename T>
T test(T type) {
    static_assert(std::is_floating_point<T>::value, "Test shall be called with a floating point datatype");
    return type;
}

int main() {
    int x{0};
    test(x);
    float y{0};
    test(y);
}
