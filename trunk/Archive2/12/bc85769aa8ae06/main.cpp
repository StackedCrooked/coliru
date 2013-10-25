#include <functional>
#include <iostream>

void* Test() {
    return nullptr;
}

int main(int argc, char* argv[]) {
    std::function<void()> foo;
    std::cout << !!foo << std::endl;

    foo = nullptr;
    std::cout << !!foo << std::endl;

    foo = reinterpret_cast<void(*)()>(Test());
    std::cout << !!foo << std::endl;

    return 0;
}
