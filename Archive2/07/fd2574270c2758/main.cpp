#include <type_traits>
struct none {};

template<typename T>
struct test {
    static constexpr bool b = std::is_same<T, none>::value;
};

int main() {
    test<int> x;
    return x.b;
}