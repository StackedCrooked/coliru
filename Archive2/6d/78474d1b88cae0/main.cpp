#include <iostream>

template<int(*F)(int)>
int wrapper() {
    return F(10);
}

int test(int x) {
    return x * 10;
}

int main() {
    std::cout << wrapper<test>();
}