#include <iostream>

template <typename T>
const T &sum(const T &v) { return v; }

//template <typename T, typename ... Ts>
//auto sum(const T &v, const Ts & ... params) -> decltype(v + sum(params...));

template <typename T, typename ... Ts>
auto sum(const T &v, const Ts & ... params) /*-> decltype(v + sum(params...))*/ {
    return v + sum(params...);
}

int main() {
    std::cout << sum(1, 2, 3) << '\n';
}
