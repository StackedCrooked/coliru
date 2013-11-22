#include <iostream>

template<std::size_t R, std::size_t C>
struct x {};

template<std::size_t R, std::size_t C>
class ctor {
public:
    using X = x<R, C>;
    ctor(const X& = X()) {}
};

int main() {
    ctor<10, 10> y;
    std::cout << 'x';
}
