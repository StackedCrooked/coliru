#include <iostream>
#include <functional>

int main() {
    int x = 16;
    int y = 14;
    std::cout << std::hash<int>()(std::hash<int>()(x) + y);
}