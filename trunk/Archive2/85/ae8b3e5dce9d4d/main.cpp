#include <iostream>
#include <functional>

template<typename T>
void f(int x, T&& t) {
    std::cout << x << ' ' << t << '\n';
}

struct test {
    template<typename T>
    void operator()(int x, const T& t) {
        std::cout << x << ' ' << t << '\n';
    }
};

int main() {
    // auto g = std::bind(test{}, 1); works
    auto g = std::bind(f, 1); // error
    // auto g = std::bind(f<int>, 1); // works
}