#include <cstddef>
#include <iostream>

template<std::size_t R, std::size_t C>
struct foo {};

template<std::size_t R, std::size_t C>
class bar {
public:
    bar(const foo<R, C>& = foo<R, C>()) {}
};

int main() {
    bar<10, 10> y;
    std::cout << 'x';
}