#include <iostream>

template<typename T>
T const& const_ref(T const& t) { return t; }

int main() {
    int x = 0;
    auto f = [&x = const_ref(x)] { return x; };
    ++x;
    std::cout << f() << "\n";
}