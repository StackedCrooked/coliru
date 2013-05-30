#include <iostream>

template<typename F>
int applyTo10(F f) {
    return f(10);
}

int main() {
    std::cout << applyTo10([] (int x) { return x + 2; }) << '\n'; // capture nothing
    
    int y = 3;
    std::cout << applyTo10([=] (int x) { return x + y; }) << '\n'; // capture y by-value
    std::cout << y << '\n';
    
    int z = 3;
    std::cout << applyTo10([&] (int x) { return x + (++z); }) << '\n'; // capture z by-reference
    std::cout << z << '\n';
}
