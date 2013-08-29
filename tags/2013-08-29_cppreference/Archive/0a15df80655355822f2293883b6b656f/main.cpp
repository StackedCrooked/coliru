#include <iostream>

template <class T>
struct S {
    S* s = new S();
    int t = 5;
    void f() { std::cout << s->t; }
    ~S() { delete s; }
};

int main() {
    S<int> s;
    s.f();
}