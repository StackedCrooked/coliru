#include <iostream>
#include <functional>

int main() {
    std::cout << sizeof(std::function<void()>);
}
