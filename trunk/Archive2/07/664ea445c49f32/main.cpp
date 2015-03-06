#include <vector>
#include <array>
#include <iostream>

namespace detail {
    template <typename C, typename Enable = void>
    struct foo_impl {
        using value_type = typename C::value_type;

        static void foo(C const& c) {
            std::cout << "OK!\n";   
        }
    };
}

template <typename C>
void foo(C const& c) {
    detail::foo_impl<C>::foo(c);
}

int main() {
    std::vector<int> test = {1, 2, 3};
    std::array<int, 3> test1 = {1, 2, 4};
    foo(test);
    foo(test1);
}
