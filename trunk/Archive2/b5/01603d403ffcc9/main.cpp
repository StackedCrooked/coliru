auto f() {
    struct result {
        int x, y;
    };
    return result{10, 11};
}

#include <iostream>

int main() {
    auto stuff = f();
    std::cout << stuff.x << ", " << stuff.y << '\n';
}