#include <iostream>
#include <type_traits>

struct Bar {
    template<class T, typename std::enable_if<std::is_same<T, int>::value>::type>
    auto foo() {
        return 0;
    }
    template<class T, typename std::enable_if<!std::is_same<T, int>::value>::type>
    auto foo() {
        return 10;
    }
};

int main() {
    Bar bq;
    std::cout << bq.foo<int>() << " " << bq.foo<double>() << "\n";
}