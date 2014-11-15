#include <type_traits>
#include <iostream>

enum class enabled {};

template<typename T>
using enable_if_t = typename std::enable_if<T::value, enabled>::type;

template<typename T>
using disable_if_t = typename std::enable_if<!T::value, enabled>::type;

template<typename T>
struct test {
    template<typename U, enable_if_t<std::is_integral<U>>...>
    explicit test(U u) {
        std::cout << "explicit\n";
    }
    
    template<typename U, disable_if_t<std::is_integral<U>>...>
    test(U u) {
        std::cout << "implicit\n";
    }
};

int main() {
    test<int> x(10);
    test<float> y(1.f);
}