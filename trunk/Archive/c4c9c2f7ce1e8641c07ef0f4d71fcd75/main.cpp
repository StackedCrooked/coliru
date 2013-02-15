#include <iterator>
#include <iostream>

template<typename T>
struct xrange {
    struct xiterator : std::iterator<std::random_access_iterator_tag,T,T> {
        T i;
        T step;
        constexpr xiterator(T a, T b): i(a), step(b) {}
        constexpr xiterator(xiterator it, T a): i(*it), step(a) {}

        constexpr T operator*() {
            return i;
        }
        xiterator operator++() {
            ++i;
            return *this;
        }
        xiterator operator--() {
            --i;
            return *this;
        }
        xiterator operator++(int) {
            auto copy = *this;
            ++(*this);
            return copy;
        }
        xiterator operator--(int) {
            auto copy = *this;
            --(*this);
            return copy;
        }
        constexpr xiterator operator+(T n) {
            return xiterator((i+n)/step, step);
        }
        constexpr xiterator operator-(T n) {
            return xiterator((i-n)/step, step);
        }
        constexpr T operator-(xiterator other) {
            return (i - *other) / step;
        }
        constexpr bool operator==(xiterator other) {
            return i == *other;
        }
        constexpr bool operator!=(xiterator other) {
            return i != *other;
        }

        xiterator& operator+=(T other) {
            i += other * step;
            return *this;
        }
        xiterator& operator-=(T other) {
            i -= other * step;
            return *this;
        }
    };
    T step;
    xiterator a, b;
    constexpr xrange(T x, T y, T step = 1): step(step), a(x,step), b(y,step) {}
    constexpr xrange(xiterator x, xiterator y, T step = 1): step(step), a(x,step), b(y,step) {}

    constexpr xiterator begin() {
        return a;
    }
    constexpr xiterator end() {
        return b;
    }
};

template<typename T>
constexpr xrange<T> range(T a, T b, T step = 1) {
    return b > a ? xrange<T>(a,b+1,step) : xrange<T>(b,a,-step);
}

int main() {
    for(auto i : range(0,10)) {
        std::cout << i << ' ';
    }
}