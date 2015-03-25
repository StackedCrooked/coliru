#include <iostream>
#include <string>
#include <stdexcept>

#include <cmath>

namespace euler009 {

namespace impl {

constexpr static inline auto sqr(uint64_t a) -> uint64_t {
    return a * a;
}

constexpr static inline auto fast_sqrt(unsigned x, unsigned next_x, unsigned a) -> unsigned {
    return (next_x >= x) ? x : fast_sqrt(next_x, 
        ((sqr(next_x) + a)/next_x) >> 1, a);
}

constexpr static inline auto fast_sqrt(unsigned x, unsigned a) -> unsigned {
    return fast_sqrt(x, ((sqr(x) + a)/x) >> 1, a);
}

constexpr static inline auto sbc(unsigned a, unsigned c = 0u) -> unsigned {
    return a == 0 ? c : sbc(a >> 1, c + 1);
}

constexpr static inline auto fast_sqrt(unsigned a) -> unsigned {
    return fast_sqrt(1 << (sbc(a) + 1), a);
}

constexpr static inline auto check(uint64_t a, uint64_t b, uint64_t c) -> bool {
    return a != b && b < c && sqr(a) + sqr(b) == sqr(c);
}

constexpr static inline auto prod(unsigned b, unsigned c, unsigned sum) -> uint64_t {
    return check(sum - b - c, b, c) ? ((sum - b - c) * b * c) : 0u;
}

constexpr static inline auto calc_d(unsigned c, unsigned sum) -> 
        unsigned {
    return fast_sqrt(sqr(c) + 2u * sum * c - sqr(sum));
}

constexpr static inline auto calc_prod(unsigned c, unsigned sum) -> uint64_t {
    return (c + calc_d(c, sum) <= sum) ? prod(((sum - c - calc_d(c, sum)) / 2), c, sum) : 0u;
}

constexpr static inline auto solution(unsigned sum, unsigned c) -> uint64_t {
    return (c > sum - 4u) ? 0u :
        (calc_prod(c, sum) != 0u) ? (calc_prod(c, sum)) : solution(sum, c + 1);
}

}  // namespace impl


constexpr static inline auto solution(unsigned sum) -> uint64_t {
    return impl::solution(sum, sum/3u);
}

extern "C" uint64_t solution() {
    return solution(1000u);
}

}  // namespace euler009

int main() {
    std::cout << euler009::solution() << std::endl;
    
    std::cout << euler009::impl::fast_sqrt(30625) << std::endl;
    
    std::cout << euler009::impl::sbc(30625) << std::endl;
}
