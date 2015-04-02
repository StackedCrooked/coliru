#include <iostream>
#include <string>
#include <vector>
#include <type_traits>
#include <cstring>

struct A {
    operator int() { return 0; }
};

struct B {
    B() {}
    B(const A&) {}
};

template <typename T>
void foo(const std::vector<T>&) {
    std::cout << "vector\n";
}

template <typename T>
void foo(std::vector<T>&) {
    std::cout << "vector&\n";
}


void foo(const int&) {
    std::cout << "int\n";
}

void foo(const B&) {
    std::cout << "A\n";
}

void foo(B&) {
    std::cout << "A&\n";
}

template <typename T>
void foo(const T&) {
    std::cout << "T\n";
}

template <typename T>
void foo(T&) {
    std::cout << "T&\n";
}

#define FOO(arg) std::cout << #arg << ": "; foo(arg)

int main() {
    std::vector<int> v;
    int i = 0;
    
    FOO(v);
    FOO(std::vector<int>{});
    FOO(i);
    
    FOO(1);
    FOO(1.0);
    FOO({});
    FOO(A{});
    A aa;
    FOO(aa);
    FOO(B{});
    B bb;
    FOO(bb);
}
