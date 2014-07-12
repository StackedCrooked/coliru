int c = 0;

constexpr int f(int x) {
    return x == 0? ++c : x;
}

#include <cassert>
int main() {
    assert(f(1) == f(1));
    assert(f(0) != f(0));
}