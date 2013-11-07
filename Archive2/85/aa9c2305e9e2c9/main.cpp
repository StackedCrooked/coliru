#include <functional>
#include <iostream>

void* Test() {
    return reinterpret_cast<void*>(&Test);
}

int main() {
    std::function<void()> foo;
    std::cout << !!foo << std::endl;

    foo = nullptr;
    std::cout << !!foo << std::endl;

    foo = reinterpret_cast<void(*)()>(Test());
    std::cout << !!foo << std::endl;

    return 0;
}