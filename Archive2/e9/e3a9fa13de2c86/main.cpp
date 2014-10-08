#include <iostream>
#include <type_traits>

namespace detail {
    enum class enabler;
}

template <typename Condition>
using EnableIf = typename std::enable_if<Condition::value, detail::enabler>::type;

template <typename Condition>
using DisableIf = typename std::enable_if<!Condition::value, detail::enabler>::type;

struct Bar {
    template<class T, class T2, EnableIf<std::is_same<T, int>> = detail::enabler{}>
    auto foo() {
        return 0;
    }
    template<class T, class T2, DisableIf<std::is_same<T, int>> = detail::enabler{}>
    auto foo() {
        return 10;
    }
};

int main() {
    Bar bq;
    std::cout << bq.foo<int, void>() << " " << bq.foo<double, void>() << "\n";
}