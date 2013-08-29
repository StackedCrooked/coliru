#include <cassert>

void g(int) {
    assert(false);
}

template <typename T>
void f() {
    g(T{});
}

void g(double) {}

int main() {
    f<double>();
}
