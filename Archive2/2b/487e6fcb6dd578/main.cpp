#include <iostream>
#include <type_traits>

int foo();

int main() {
    using F = int();
    std::cout << std::boolalpha
            << std::is_same<int(), int(*)()>::value << '\n'
            << std::is_same<void(int()), void(int(*)())>::value << '\n'
            << std::is_same<F, F*>::value << '\n'
            << std::is_same<void(F), void(F*)>::value << '\n'
            << std::is_same<void(F), void(F**)>::value << '\n'
            << std::is_same<decltype(foo), F>::value << '\n'
            << std::is_same<decltype(*foo), F&>::value << '\n'
            << std::is_same<decltype(******foo), F&>::value << std::endl;
}
