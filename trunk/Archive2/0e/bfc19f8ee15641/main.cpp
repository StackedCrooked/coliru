#include <iostream>

struct other {
    other() { std::cout << "other\n"; }
};
struct test {
    int x;
    other y;
    test() = default;
};

int main() {
    test t;
}
    