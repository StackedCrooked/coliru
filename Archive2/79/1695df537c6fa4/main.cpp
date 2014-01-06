#include <iostream>

struct S {
    //non-trivial because of i{}, so j must be uninitialized
    S() : i{} {std::cout << i << ' ' << j;}
    int i;
    int j;
};

int main() {
    S s[1] = {};
}