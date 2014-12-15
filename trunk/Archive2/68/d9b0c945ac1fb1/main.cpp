#include <iostream>
#include <functional>
#include <vector>

int main() {
    std::vector<std::function<void(int)>> functions {
        [](int i) { std::cout << i << "\n"; },
        [](int i) { std::cout << "fizz\n";  },
        [](int i) { std::cout << "buzz\n";  },
        [](int i) { std::cout << "fizzbuzz\n"; }
    };


    for(int i = 1; i <= 100; ++i) {
        functions[(i % 3 == 0) + 2 * (i % 5 == 0)](i);
    }
}