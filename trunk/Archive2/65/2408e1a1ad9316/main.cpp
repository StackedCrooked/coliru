struct test {
    int x;
    int& y = x;
};

#include <iostream>

int main() {
    test t;
    t.y = 20;
    std::cout << t.x << '\n';
}