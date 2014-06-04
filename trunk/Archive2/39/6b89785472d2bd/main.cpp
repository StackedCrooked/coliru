#include <iostream>

template<typename T>
struct id {};

template<typename T>
void f(const T& t) {}

int main() {
    f(id<int>());
}