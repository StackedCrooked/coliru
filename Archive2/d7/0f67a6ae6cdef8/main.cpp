#include <type_traits>

decltype(auto) g(int& t) {
    return t;
}

int main() {
    int x = 10;
    int& y = x;
    auto f = [&](int& t) {
            return t;
    };
    static_assert(std::is_same<decltype(f(y)), int&>{}, "..");
    static_assert(std::is_same<decltype(g(y)), int&>{}, "..");
}