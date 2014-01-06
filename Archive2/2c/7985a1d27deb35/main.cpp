#include <iostream>

struct S {
    S(std::initializer_list<int>){}
    int i;
    int j;
};

int main() {
    S{};
    //S();
    S a[1] = {};
}