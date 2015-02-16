#include <iostream>
#include <type_traits>

int main() {
    auto x = 1;
    
    auto yar = [=](auto&& x) {
        std::cout << std::is_same<decltype((x)), int>::value << std::endl;
        std::cout << std::is_same<decltype((x)), int&&>::value << std::endl;
        std::cout << std::is_same<decltype((x)), int&>::value << std::endl;
    }; yar(x);
}
