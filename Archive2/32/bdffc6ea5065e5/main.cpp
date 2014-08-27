struct test {
    int x;
    int y;
    int z;
};

struct other {
    int x;
    int y;
    int z;
};

#include <iostream>

int main() {
    test x = { 1, 2, 3 };
    other* t = reinterpret_cast<other*>(&x); // UB?
    std::cout << t->x << '\n' << t->y << '\n' << t->z << '\n';
}