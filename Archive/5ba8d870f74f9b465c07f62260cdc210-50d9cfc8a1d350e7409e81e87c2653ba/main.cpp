#include <iostream>
#include <functional>

template <typename T> void f();

template <void(*)()>
struct foo {};

int main () {
    foo<f<void>> x;
}
