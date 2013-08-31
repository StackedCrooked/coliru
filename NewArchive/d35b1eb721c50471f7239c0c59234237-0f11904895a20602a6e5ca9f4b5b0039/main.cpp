#include <iostream>
#include <functional>

auto fibonacci() {
    int a = 0;
    int b = 1;
    return [=] () mutable {
        auto x = b;
        b = a + b;
        a = x;
        return x;
    };
}

int main() {
    auto generator = fibonacci();
    for (int i = 0; i < 20; ++i) {
        std::cout << "F" << i << " = " << generator() << '\n';
    }
    return 0;
}
