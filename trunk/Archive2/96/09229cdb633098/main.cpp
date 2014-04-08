#include <iostream>

template <typename>
struct outer {
    template <typename>
    struct inner {
        int data;
    };
};

template <typename T, typename U>
bool
operator == (typename outer<T>::template inner<U> lhs,
             typename outer<T>::template inner<U> rhs) {
    return lhs.data == rhs.data;
}

int
main() {
    outer<double>::inner<int> x{5}, y{5};
    std::cout << (x == y) << '\n';  // Won't find the operator.
}
