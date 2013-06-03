#include <iostream>

template<typename T>
void echo(T &&t) {
    std::cout << t;
}

int main() {
    auto $ten = 10;
    auto $twenty = 20;
    echo($ten + $twenty);
}
