#include <functional>

template<class F, class ...Ts> void for_each_argument(F f, Ts &&...args) {
    (void)(int[]){ (f(std::forward<Ts>(args)), 0)... };
}

void foo(int) {}

int main() {
    for_each_argument(foo, 1, 2, 3);
}