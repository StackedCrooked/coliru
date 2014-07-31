#include <functional>
#include <iostream>

template <typename T>
void add_print(T arg1, T arg2) {
    std::cout << arg1 << " + " << arg2 << " = " << arg1 + arg2 << '\n';
}

int main() {
    using namespace std::placeholders;
    add_print(150, 240);
    
    auto add_to_320 = std::bind(add_print<int>, 320, _1);
    
    add_to_320(50);
    add_to_320(100);
    
    auto add_320_to = std::bind(add_print<int>, _1, 320);
    
    add_320_to(777);
    add_320_to(1000);
}
