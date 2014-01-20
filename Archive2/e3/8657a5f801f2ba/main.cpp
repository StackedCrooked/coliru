#include <iostream>

int main() {
    const char x[] = "hello";
    std::cout << sizeof(x) << '\n';
    for(auto&& i : x) {
        std::cout << "C: " << i << '\n';
    }
}
