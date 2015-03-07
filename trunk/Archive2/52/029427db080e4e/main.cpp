#include <iostream>

struct S {
    int a;
    int b;
};

int main() {
    S s = S();
    (s.*(true ? &S::a : &S::b)) = 1;
    
    std::cout << s.a << ' ' << s.b;
}
