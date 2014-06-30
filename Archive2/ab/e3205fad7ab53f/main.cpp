#include <cmath>
#include <type_traits>

template<typename T, typename U>
const U& type_assert(const U& u) {
    static_assert(std::is_same<T, U>::value, "...");
    return u;
}

int main() {
    double t = type_assert<double>(std::sin(2.2f));
}