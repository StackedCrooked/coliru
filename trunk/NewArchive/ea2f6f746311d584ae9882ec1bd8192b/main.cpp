#include <iostream>

// our numeric type, to allow easy modification later
typedef unsigned number;

// square root computation, using binary search
template <number num, number begin = 0, number end = num>
class sqrt {
        const static number mid = (begin+end) / 2;
        const static number midsqr = mid * mid;
    public:
        const static number res = sqrt<num,
                        (midsqr<num)?mid+1:begin,
                        (midsqr<num)?end:mid>::res;
};

// specialization to stop recursion
template <number num, number lim>
struct sqrt<num, lim, lim> {
    const static number res = lim;
};

// check if a certain number has any dividers within the range
template <number num, number begin = 2, number end = sqrt<num>::res>
struct has_any_divs {
    const static bool res = !(num%begin) ||
                    has_any_divs<num, begin+1, end>::res;
};

// specialization to stop recursion
template <number num, number lim>
struct has_any_divs<num, lim, lim> {
    const static bool res = !(num%lim);
};

// is the given number a prime?
template <number num>
struct is_prime {
    const static bool res = !has_any_divs<num>::res;
};

// these require specializations
template <> struct is_prime<2> { const static bool res = true;  };
template <> struct is_prime<1> { const static bool res = false; };
template <> struct is_prime<0> { const static bool res = false; };

int main () {
    std::cout << std::boolalpha;
    std::cout << "is 65537 prime? " << is_prime<65537>::res << std::endl;
    std::cout << "is 65549 prime? " << is_prime<65549>::res << std::endl;
    return 0;
}
