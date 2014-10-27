#include <string>
#include <iostream>

template <typename F>
void fizz_buzz(int i, F const& f) {
    if(i % 15 == 0) {
        f("FizzBuzz");
    } else if(i % 5 == 0) {
        f("Buzz");
    } else if(i % 3 == 0) {
        f("Fizz");
    } else {
        f(i);
    }
}

int main() {
    for(int i = 1; i <= 100; ++i) fizz_buzz(i, [](auto const& v) { std::cout << v << '\n'; });
}