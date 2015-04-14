#include <string>
#include <exception>
#include <type_traits>

struct bad_rational : public std::exception {
    bad_rational() = default;
    const char* what() const noexcept override {
        return "bad rational: division by zero";
    }
};

template<typename T>
constexpr T gcd(const T& x, const T& y) {
    return y == 0 ? x : gcd(y, x % y);
}

template<typename Integral>
struct rational {
public:
    static_assert(not std::is_floating_point<Integral>::value, "Only integral types allowed");
    using value_type = Integral;

    constexpr rational(value_type numerator, value_type denominator):
        top(numerator), bottom(denominator > 0 ? denominator : throw bad_rational()) {}
    constexpr rational(): rational(0, 1) {}
    constexpr rational(value_type numerator): rational(numerator, 1) {}

    constexpr value_type denominator() const noexcept {
        return bottom;
    }

    constexpr value_type numerator() const noexcept {
        return top;
    }
private:
    Integral top;
    Integral bottom;
};

template<typename Integral>
constexpr rational<Integral> simplify(const rational<Integral>& r) {
    using Rational = rational<Integral>;
    return r.numerator() == 0 ?
               Rational{} : (r.denominator() / gcd(r.numerator(), r.denominator()) < 0) ?
                                Rational{-(r.numerator() / gcd(r.numerator(), r.denominator())),
                                         -(r.denominator() / gcd(r.numerator(), r.denominator()))} :
                                Rational{r.numerator() / gcd(r.numerator(), r.denominator()),
                                         r.denominator() / gcd(r.numerator(), r.denominator())};

}

#include <iostream>

int main() {
    constexpr rational<int> x = { 21, 7 };
    constexpr auto simplified = simplify(x);
    std::cout << x.numerator() << '/' << x.denominator() << '\n';
    std::cout << simplified.numerator() << '/' << simplified.denominator() << '\n';
}
