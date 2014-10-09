#include <iostream>
#include <type_traits>

struct Bar {
    template<class T, class T2, typename std::enable_if<std::is_same<T, int>::value, int>::type = 0>
    auto foo() {
        return 0;
    }
    template<class T, class T2, typename std::enable_if<!std::is_same<T, int>::value, int>::type = 0>
    auto foo() {
        return 10;
    }
};

int main() {
    Bar bq;
    std::cout << bq.foo<int, void>() << " " << bq.foo<double, void>() << "\n";
}