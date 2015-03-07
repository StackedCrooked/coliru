#include <iostream>

struct S {
    int a;
    int b;
};

int main() {
    S s = {1, 2};
    std::cout << s.*(true ? &S::a : &S::b) << ' ';
    std::cout << s.*(false ? &S::a : &S::b);
}
