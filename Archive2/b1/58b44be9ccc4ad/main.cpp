#include <functional>
#include <iostream>

int main() {
    std::function<void(int)> test[] = {
        [](int x) { std::cout << x << '\n'; },
        [](int  ) { std::cout << "fizz\n"; },
        [](int  ) { std::cout << "buzz\n"; },
        [](int  ) { std::cout << "fizzbuzz\n"; }
    };

    for(unsigned i = 0; i <= 100; ++i) {
        test[(i % 3 == 0) + 2 * (i % 5 == 0)](i);
    }
}
