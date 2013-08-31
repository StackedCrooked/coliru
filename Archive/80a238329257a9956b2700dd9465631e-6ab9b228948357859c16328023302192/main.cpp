#include <functional>
#include <iostream>
#include <vector>

std::function<void()> li1;

template <typename T>
void _li(T t) {
    for ( auto& lis : t)
        std::cout << static_cast<char>(lis);
}

int main() {
    std::function<void(std::vector<int>)> li2 = _li;
    return 0;
}