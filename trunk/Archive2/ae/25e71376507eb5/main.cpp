#include <iostream>

struct f {
    int x;
    f(): x(10) {}
    f(int x): x(x) {}
};

int main() {
    union y {
        f x;
        int z;
    };
}