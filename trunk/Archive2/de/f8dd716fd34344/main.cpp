#include <exception>
#include <utility>

class bad_rational : public std::exception {
public:
    bad_rational() noexcept = default;

    const char* what() const noexcept override {
        return "bad_rational: denominator is zero";
    }
};

template<typename T>
constexpr T gcd(const T& x, const T& y) {
    return y == 0 ? x : gcd(y, x % y);
}

template<typename Integer>
struct rational {
private:
    Integer num = 0;
    Integer den = 1;
public:
    constexpr rational() = default;
    constexpr rational(Integer n): num(std::move(n)) {}
    constexpr rational(Integer n, Integer d): num(std::move(n)), den(d == 0 ? throw bad_rational() : std::move(d)) {}

    rational& operator=(Integer n) {
        num = n;
        return *this;
    }

    constexpr explicit operator bool() const noexcept {
        return num != 0;
    }

    constexpr Integer numerator() const noexcept {
        return num;
    }

    constexpr Integer denominator() const noexcept {
        return den;
    }
};

template<typename Integer>
constexpr rational<Integer> normalised(const rational<Integer>& r) noexcept {
    return r.numerator() == 0 ? rational<Integer>{ 0, 1 } :
           rational<Integer>{ r.numerator() / gcd(r.numerator(), r.denominator()),
                              r.denominator() / gcd(r.numerator(), r.denominator()) };
}

int main() {
    constexpr rational<int> test(4, 2);
    constexpr rational<int> normal = normalised(test);
    
    static_assert(normal.numerator() == 2 && normal.denominator() == 1, "...");
}
