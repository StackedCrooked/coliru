#include <functional>
#include <iostream>

int main() {
    int a = 2, b = 3;
    std::reference_wrapper<int> refs[] = {a, b};
    a = 5;
    std::cout << refs[0] << ' ' << refs[1];
}