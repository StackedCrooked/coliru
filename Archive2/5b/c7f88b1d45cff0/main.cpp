#include <iostream>
#include <vector>

struct Type {
    Type(int i) : m(i) {}
    int m;
};

using NumericType = unsigned long long;

Type operator""_y(NumericType i) {
    return Type(i);
}

int main() {
    auto x = 1_y;
    (decltype(x)) x; // just to avoid "unused variable" warning
}