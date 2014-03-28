#include <complex>

template <typename T>
struct foo {
    template <typename U = T>
    operator U() const;
};

int main() {
    static_cast<std::complex<double>>(foo<std::complex<double>>{});
}