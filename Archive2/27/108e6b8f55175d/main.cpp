#include <cstdint>
#include <type_traits>
#include <stdexcept>
#include <cmath>
#include <vector>
#include <tuple>
#include <set>

namespace op {
    template<class T>
    inline uint32_t isqrt(T x) {
        static_assert(std::is_integral<T>::value, "op::isqrt only works on integer types");

        if (x < 0) throw std::domain_error("op::isqrt");
        return op::isqrt<uint64_t>(x);
    }

    template<>
    inline uint32_t isqrt(uint64_t x) {
        // For small values using native functions is fastest.
        // Where "small" means maximum integer accurate after float conversion.
        if (x <= 16785406ull) {
            return uint32_t(std::sqrt(float(x)));
        } if (x <= 4503599761588223ull) {
            return uint32_t(std::sqrt(double(x)));
        }

        // Newton's method, adapted from Hacker's Delight.
        // Since we know x > 4503599761588223 we can skip some branches.
        uint64_t s, x1, g0, g1;
        x1 = (x - 1) >> 48;
        s = 25;
        if (x1 > 255) {s = s + 4; x1 = x1 >> 8;}
        if (x1 > 15)  {s = s + 2; x1 = x1 >> 4;}
        if (x1 > 3)   {s = s + 1;}

        g0 = 1 << s;
        g1 = (g0 + (x >> s)) >> 1;
        while (g1 < g0) {
            g0 = g1;
            g1 = (g0 + x/g0) >> 1;
        }

        return g0;
    }

    
    template<class T, class U>
    inline uint64_t gcd(T a_, U b_) {
        static_assert(std::is_integral<T>::value && std::is_integral<U>::value,
                      "op::gcd only works on integer types");

        uint64_t a = a_ >= 0 ? a_ : -a_;
        uint64_t b = b_ >= 0 ? b_ : -b_;
        if (a == b) return a;
        
        while (b > 0) {
            uint64_t tmp = a;
            a = b;
            b = tmp % b;
        }

        return a;
    }


    template<class T, class U>
    inline uint64_t lcm(T a_, U b_) {
        static_assert(std::is_integral<T>::value && std::is_integral<U>::value,
                      "op::lcm only works on integer types");

        uint64_t a = a_ >= 0 ? a_ : -a_;
        uint64_t b = b_ >= 0 ? b_ : -b_;

        return (a / gcd(a, b)) * b;
    }


    template<class OutIter>
    inline void primesbelow(uint64_t limit, OutIter out) {
        // http://stackoverflow.com/questions/4643647/fast-prime-factorization-module
        if (limit > 2) *out++ = 2;
        if (limit > 3) *out++ = 3;
        if (limit <= 5) return;

        uint64_t correction = limit % 6 > 1;
        uint64_t wheels[6] = { limit, limit - 1, limit + 4, limit + 3, limit + 2, limit + 1 };
        uint64_t n = wheels[limit % 6];

        std::vector<bool> sieve(n / 3, true);
        sieve[0] = false;

        for (uint64_t i = 0, upper = op::isqrt(n)/3; i <= upper; ++i) {
            if (sieve[i]) {
                uint64_t k = (3*i + 1) | 1;
                for (uint64_t j = (k*k) / 3;                   j < n/3; j += 2*k) sieve[j] = false;
                for (uint64_t j = (k*k + 4*k - 2*k*(i & 1))/3; j < n/3; j += 2*k) sieve[j] = false;
            }
        }

        for (uint64_t i = 1; i < n / 3 - correction; ++i) {
            if (sieve[i]) *out++ = (3 * i + 1) | 1;
        }
    }


    namespace detail {
        // Computes (a + b) % m, assumes a < m, b < m.
        inline uint64_t addmod64(uint64_t a, uint64_t b, uint64_t m) {
            if (b >= m - a) return a - m + b;
            return a + b;
        }

        // Computes (a || b) % m.
        inline uint64_t mod64(uint64_t a, uint64_t b, uint64_t m) {
            #if defined(__GNUC__) && defined(__x86_64__)
                uint64_t q, r;
                asm("divq %4"
                    : "=a"(q),"=d"(r)
                    : "a"(b), "d" (a), "rm"(m)
                    : "cc");
                return r;
            #endif

            // TODO: fallback implementation
        }


        inline std::pair<uint64_t, uint64_t> mul64(uint64_t a, uint64_t b) {
            #if defined(__GNUC__) && defined(__x86_64__)
                uint64_t h, l;
                asm("mulq %3"
                    : "=a"(l),"=d"(h)
                    : "a"(a), "rm"(b)
                    : "cc");
                return std::make_pair(h, l);
            #endif

            // TODO: fallback implementation
        }


        // Finds 2^-64 mod m and (-m)^-1 mod m for odd m (hacker's delight).
        inline std::pair<uint64_t, uint64_t> mont_modinv(uint64_t m) {
            uint64_t a = 1ull << 63;
            uint64_t u = 1;
            uint64_t v = 0;

            while (a > 0) {
                a = a >> 1;
                if ((u & 1) == 0) {
                    u = u >> 1; v = v >> 1;
                } else {
                    u = ((u ^ m) >> 1) + (u & m);
                    v = (v >> 1) + (1ull << 63);
                }
            }

            return std::make_pair(u, v);
        }


        // Computes aR * bR mod N with R = 2**64.
        inline uint64_t montmul64(uint64_t a, uint64_t b, uint64_t N, uint64_t Nneginv) {
            uint64_t Th, Tl, m, mNh, mNl, th;

            std::tie(Th, Tl) = mul64(a, b);
            m = Tl * Nneginv;
            std::tie(mNh, mNl) = mul64(m, N);

            bool lc = Tl + mNl < Tl;
            th = Th + mNh + lc;
            bool hc = (th < Th) || (th == Th && lc);

            if (hc > 0 || th >= N) th = th - N;

            return th;
        }


        // Computes (a*b) % m safely, considering overflow. Requires b < m;
        inline uint64_t mulmod64(uint64_t a, uint64_t b, uint64_t m) {
            #if defined(__GNUC__) && defined(__x86_64__)
                uint64_t q, r;
                asm("mulq %3;"
                    "divq %4;"
                    : "=a"(q), "=d"(r)
                    : "a"(a), "d"(b), "rm"(m)
                    : "cc");
                return r;
            #else
                // No overflow possible.
                if (a == 0) return b;
                if (b <= std::numeric_limits<uint64_t>::max() / a) return (a*b) % m;

                uint64_t res = 0;
                while (a != 0) {
                    if (a & 1) res = addmod64(res, b, m);
                    a >>= 1;
                    b = addmod64(b, b, m);
                }

                return res;
            #endif
        }
    }


    inline uint64_t powmod(uint64_t b, uint64_t e, uint64_t m) {
        uint64_t r = 1;

        b %= m;
        while (e) {
            if (e % 2 == 1) r = detail::mulmod64(r, b, m);
            b = detail::mulmod64(b, b, m);
            e >>= 1;
        }

        return r;
    }


    template<class T>
    inline bool isprime(T x) {
        static_assert(std::is_integral<T>::value, "op::isprime only works on integer types");

        if (x < 2) return false;
        return op::isprime<uint64_t>(x);
    }


    template<>
    inline bool isprime(uint64_t n) {
        // Miller-rabin with a check for small primes first. Uses Montgomery modular multiplication.
        constexpr int max_smallprimeset = 100000;
        static std::set<int> smallprimeset;

        if (smallprimeset.size() == 0) {
            op::primesbelow(max_smallprimeset, std::inserter(smallprimeset, smallprimeset.begin()));
        }

        if (n <= 3) return n >= 2;
        if (n % 2 == 0) return false;
        if (n < max_smallprimeset) return smallprimeset.count(n);

        // We only ever have to compare to 1 and n-1, instead of converting back and forth, compute
        // once and compare in Montgomery form.
        uint64_t nneginv = detail::mont_modinv(n).second;
        uint64_t mont1 = detail::mod64(1, 0, n);
        uint64_t montn1 = detail::mod64(n-1, 0, n);

        uint64_t d = n - 1;
        int s = -1;
        while (d % 2 == 0) {
            d /= 2;
            s += 1;
        }

        uint64_t bases[] = {2, 325, 9375, 28178, 450775, 9780504, 1795265022};
        for (auto base : bases) {
            uint64_t x = mont1;
            uint64_t b = detail::mod64(base % n, 0, n);
            uint64_t e = d;
            while (e) {
                if (e % 2 == 1) x = detail::montmul64(x, b, n, nneginv);
                b = detail::montmul64(b, b, n, nneginv);
                e >>= 1;
            }

            if (x == mont1 || x == montn1) continue;
            for (int i = 0; i < s; ++i) {
                x = detail::montmul64(x, x, n, nneginv);

                if (x == mont1) return false;
                if (x == montn1) goto next_base;
            }

            return false;
        next_base: ;
        }

        return true;
    }
    

    namespace detail {
        inline uint64_t pollard_brent(uint64_t n) {
            // Richard P. Brent (1980) – An Improved Monte Carlo Factorization Algorithm
            //
            // A cool optimization is used here. Firstly we use the much faster Montgomery reduction
            // for modular multiplication. However, note that:
            //
            //     a = b (mod n)   =>    gcd(a, n) = gcd(b, n)
            //
            // Since our result is always derived through a gcd involving n, and all logic and
            // branching is done on the result of such a gcd, it means we'll never have to convert
            // between Montgomery form and regular integers. In other words, Pollard-Brent just
            // works if you change all multiplications with Montgomery multiplication!
            //
            // The only precomputation needed is (-N)*2^64 (mod n)
            
            // Really simple LCG with a twist. Don't know how it works, but it works and is faster
            // than "better" RNGs for some reason.
            static uint64_t rng = 0xdeafbeef;
            uint64_t a = rng*6364136223846793005ull + 1442695040888963407ull;
            uint64_t b = a*6364136223846793005ull + 1442695040888963407ull;
            rng = (a+b) ^ (a*b);

            uint64_t y = 1 + a % (n - 1);
            uint64_t c = 1 + b % (n - 1);
            uint64_t m = 100;
            
            uint64_t mneginv = detail::mont_modinv(n).second;

            uint64_t g, r, q, x, ys;
            q = r = 1;

            do {
                x = y;
                for (uint64_t i = 0; i < r; ++i) {
                    y = detail::addmod64(detail::montmul64(y, y, n, mneginv), c, n);
                }

                for (uint64_t k = 0; k < r && g == 1; k += m) {
                    ys = y;
                    for (uint64_t i = 0; i < std::min(m, r-k); ++i) {
                        y = detail::addmod64(detail::montmul64(y, y, n, mneginv), c, n);
                        q = detail::montmul64(q, x < y ? y-x : x-y, n, mneginv);
                    }

                    g = op::gcd(q, n);
                }

                r *= 2;
            } while (g == 1);

            if (g == n) {
                do {
                    ys = detail::addmod64(detail::montmul64(ys, ys, n, mneginv), c, n);
                    g = op::gcd(x < ys ? ys-x : x-ys, n);
                } while (g == 1);
            }
            
            return g;
        }
    }


    inline std::vector<uint64_t> primefactors(uint64_t n) {
        static std::vector<int> smallprimes;
        if (smallprimes.size() == 0) op::primesbelow(1000, std::back_inserter(smallprimes));

        std::vector<uint64_t> factors;
        for (uint64_t checker : smallprimes) {
            while (n % checker == 0) {
                factors.push_back(checker);
                n /= checker;
            }

            if (checker > n) break;
        }

        std::vector<uint64_t> to_factor = {n};
        while (to_factor.size()) {
            n = to_factor.back();
            to_factor.pop_back();

            if (n == 1) continue;
            if (op::isprime(n)) {
                factors.push_back(n);
                continue;
            }

            // Get a (not necessarily prime) factor of n.
            uint64_t factor = detail::pollard_brent(n);
            to_factor.push_back(factor);
            to_factor.push_back(n / factor);
        }

        return factors;
    }
}



#include <iostream>

int main(int argc, char** argv) {
    for (auto factor : op::primefactors(123509238490234654ull)) std::cout << factor << " ";
    std::cout << "\n";
    return 0;
}
