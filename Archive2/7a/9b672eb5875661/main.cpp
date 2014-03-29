#include <complex>

template <typename T>
struct foo {
    operator T() const;
    operator T&();
};

int main() {
    static_cast<std::complex<double>>(foo<std::complex<double>>{});
}