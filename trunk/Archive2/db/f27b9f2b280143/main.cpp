#include <cmath>
#include <iostream>
#include <vector>
#include <future>

struct B {
    int a;
    int b;
};

struct A {
    int a;
    float b;
    B c;
    std::vector<char> d;
};


int main() {
    A myA{5, 5.5, {3, 5}, {'b', 'a', 'd'}};
}