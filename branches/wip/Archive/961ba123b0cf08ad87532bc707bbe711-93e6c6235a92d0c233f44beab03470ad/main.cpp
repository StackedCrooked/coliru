#include <iostream>

struct A {
    int a;
    A(int b): a(b) { std::cout << "A()\n"; }
    A(A&& a): a(a.a) { std::cout << "A(A&&)\n"; }
    A(const A&) = delete;
    A& operator=(const A&) = delete;
    A& operator=(const A&&) = delete;
};

#include <vector>

int main() {
    std::vector<A> a;
    a.push_back(A(20));
    a.push_back(A(30));
}