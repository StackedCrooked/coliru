#include <iostream>
#include <type_traits>

int main() {
    std::cout << std::is_same<int(), int(*)()>::value << '\n'
            << std::is_same<void(int()), void(int(*)())>::value << std::endl;
}
