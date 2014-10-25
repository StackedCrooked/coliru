#include <iostream>
#include <limits>
#include <cmath>

template<typename Float>
bool better_equals(Float a, Float b) {
    return std::abs(a - b) < 100*std::numeric_limits<float>::epsilon()*(1 + std::max(std::abs(a), std::abs(b)));
}

template<typename Float>
bool bad_equals(Float a, Float b) {
    return std::abs(a - b) < 1e-5; // 1e-5 is roughly 100*std::numeric_limits<float>::epsilon() FYI;
}

int main() {
    // (1/3)^(-5) == 243 exactly
    // pow(1/3, -5) will have some roundoff error because 1/3 is also a "repeating decimal" in binary
    float a = std::pow(1/3.0f, -5),
          b = 243;

    std::cout << std::boolalpha
              << "a: " << a << "\nb: " << b << "\n\n"
              << "|a - b| < 1e-5  (absolute error):\n    a ≈ b  =>  "
                 << bad_equals<float>(a, b) << '\n'
              << "|a - b| < 1e-5 * (1 + max(|a|, |b|))  (relative error if |a|,|b| > 1, otherwise absolute error):\n    a ≈ b  =>  "
                 << better_equals<float>(a, b) << '\n';
}