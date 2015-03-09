#include <iostream>

template <int... n>
struct sum {
    static int value();
};

template <int m, int... n>
struct sum<m, n...> {
    static int value() {
        return m + sum<n...>::value();
    }
};

template <>
struct sum<> {
    static int value() {
        return 0;
    }
};

int main() {
    std::cout << sum<1,2,3,4,5>::value() << std::endl;
    return 0;
}
