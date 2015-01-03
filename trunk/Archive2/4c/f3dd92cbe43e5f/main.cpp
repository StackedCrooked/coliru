#include <iostream>

template<typename Acc>
constexpr Acc min_acc(Acc x) {
    return x;
}

template<typename Acc, typename... Rest>
constexpr Acc min_acc(Acc x, Acc y, Rest... args) {
    return min_acc(((y < x) ? y : x), args...);
}

template<typename Head, typename... Rest>
constexpr Head min(Head x, Rest... args) {
    return min_acc(x, args...);
}

int main() {
    std::cout << min(2, 5, 1);
}