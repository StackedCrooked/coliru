#include <utility>

namespace detail {
    namespace using_std_swap {
        using std::swap;
        template<class T, class U, class = decltype(swap(std::declval<T&>(), std::declval<U&>()))>
        std::true_type swappable_test(int);
        std::false_type swappable_test(...);
    }
}

template<class T, class U = T>
struct is_swappable : decltype(detail::using_std_swap::swappable_test<T, U>(0)) { };

struct A {
    A() {}
    ~A() {}
    A(const A&) = delete;
    A(A&&) = delete;
};

#include <iostream>
int main(int argc, char** argv) {
    std::cout << is_swappable<int>::value << "\n";
    std::cout << is_swappable<A>::value << "\n";
    return 0;
}
