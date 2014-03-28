#include <complex>

template <typename T>
struct foo {
    // add code here
};

int main() {
    static_cast<std::complex<double>>(foo<std::complex<double>>{});
}