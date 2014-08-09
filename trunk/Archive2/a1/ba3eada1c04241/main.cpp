#include <cstdio>
template <size_t N>
struct Vector {};

template <size_t ROWS, size_t COLS = ROWS>
struct Matrix {
    Matrix<ROWS, 1>(const Vector<ROWS>& vector) {
        puts("foo");
    }
};

int main() {
    Vector<1> v;
    Matrix<1, 2> m(v);
}
