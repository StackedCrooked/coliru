#include <iostream>

template<typename F>
auto fix(F f) {
    return f(f);
}

class Fac {
public:
    explicit Fac(unsigned long long n) : n(n) { }

    unsigned long long operator()(Fac const& f) const {
        if (n < 2) {
            return 1;
        } else {
            return n * f(Fac(n - 1));
        }
    }

private:
    unsigned long long n;
};

int main() {
    std::cout << fix(Fac(20)) << '\n';
    return 0;
}
