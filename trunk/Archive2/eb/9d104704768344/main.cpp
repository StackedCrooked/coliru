#include <iostream>

template<typename T>
struct addable {
    friend T operator+(T lhs, const T& rhs) noexcept {
        lhs += rhs;
        return lhs;
    }
};

struct test {
    int x = 0;
    test(int x): x(x) {}
    test& operator+=(const test& t) {
        x += t.x;
        return *this;
    }
};

template struct addable<test>;

int main() {
    test x = { 10 };
    test y = { 20 };
    test z = x + y;
}
