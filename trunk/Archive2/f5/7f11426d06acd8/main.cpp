#include <cstdint>
#include <iostream>
#include <tuple>

// Intrinsic for 64x64->128 bit mult.
inline std::pair<uint64_t, uint64_t> mulu64(uint64_t a, uint64_t b) {
    uint64_t h, l;
    asm("mulq %3"
        : "=a"(l),"=d"(h)
        : "a"(a), "rm"(b)
        : "cc");
    return std::make_pair(h, l);
}

// Computes (a + b) % m, assumes a < m and b < m.
inline uint64_t addmod64(uint64_t a, uint64_t b, uint64_t m) {
    if (b >= m - a) return a - m + b;
    return a + b;
}

// Computes aR * bR mod N with R = 2**64.
inline uint64_t montmul64(uint64_t a, uint64_t b, uint64_t N, uint64_t Nneginv) {
    std::pair<uint64_t, uint64_t> T, mN;
    
    uint64_t Th, Tl, m, mNh, mNl, th;

    std::tie(Th, Tl) = mulu64(a, b);
    m = Tl * Nneginv;
    std::tie(mNh, mNl) = mulu64(m, N);

    bool lc = Tl + mNl < Tl;
    th = Th + mNh + lc;
    bool hc = (th < Th) || (th == Th && lc);

    if (hc > 0 || th >= N) th = th - N;

    return th;
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

inline uint64_t gcd(uint64_t a, uint64_t b) {
    if (a == b) return a;
    while (b > 0) {
        uint64_t tmp = a;
        a = b;
        b = tmp % b;
    }

    return a;
}

// Returns a factor of n, assumes n is odd.
inline uint64_t pollard_brent(uint64_t n) {
    static uint64_t rng = 0xdeafbeef;
    uint64_t a = rng*6364136223846793005ull + 1442695040888963407ull;
    uint64_t b = a*6364136223846793005ull + 1442695040888963407ull;
    rng = (a+b) ^ (a*b);

    uint64_t y = 1 + a % (n - 1);
    uint64_t c = 1 + b % (n - 1);
    uint64_t m = 100;
    
    uint64_t nneginv = mont_modinv(n).second;

    uint64_t g, r, q, x, ys;
    q = r = 1;

    do {
        x = y;
        for (uint64_t i = 0; i < r; ++i) {
            y = addmod64(montmul64(y, y, n, nneginv), c, n);
        }

        for (uint64_t k = 0; k < r && g == 1; k += m) {
            ys = y;
            for (uint64_t i = 0; i < std::min(m, r-k); ++i) {
                y = addmod64(montmul64(y, y, n, nneginv), c, n);
                q = montmul64(q, x < y ? y-x : x-y, n, nneginv);
            }

            g = gcd(q, n);
        }

        r *= 2;
    } while (g == 1);

    if (g == n) {
        do {
            ys = addmod64(montmul64(ys, ys, n, nneginv), c, n);
            g = gcd(x < ys ? ys-x : x-ys, n);
        } while (g == 1);
    }
    
    return g;
}


int main(int argc, char** argv) {
    std::cout << pollard_brent(1073741827ull * 1073741831ull) << "\n";
    return 0;
}
