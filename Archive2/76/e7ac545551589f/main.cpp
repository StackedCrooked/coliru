#include <iostream>

int main() {
    int value{1};
    int const& a{value};
    int const b{value};
    
    ++value;
    std::cout << a << ' ' << b << '\n';
}
