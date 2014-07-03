struct test {
    static const int x = 10;
};

#include <iostream>

int main() {
    test* t = new test;
    std::cout << t.x;
}