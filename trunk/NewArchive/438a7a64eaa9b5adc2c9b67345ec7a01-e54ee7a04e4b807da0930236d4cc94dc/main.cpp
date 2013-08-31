#include <iostream>
#include <cstdint>

using U64 = uint64_t;

// generate the next integer with the same number of bits as c
U64 next_combination(U64 c) 
{
    auto const smallest = c & -c;
    auto const ripple = c + smallest;
    auto ones = c ^ ripple;
    ones = (ones >> 2) / smallest;
    return ripple | ones;
}

// generate all integers with k of the first n bits set
template<class Function>
void for_each_combination(std::size_t n, std::size_t k, Function fun)
{
    U64 y;
    auto const n_mask = (1ULL << n) - 1;
    auto const k_mask = (1ULL << k) - 1;
    for (auto x = k_mask; (y = next_combination(x) & n_mask) > x; x = y)
        fun(y);
}

int main() 
{
    auto const million = 1ULL;
    auto count = U64 { 1 };
    for (auto i = 12; i < 19; ++i) {
        for_each_combination(48, i, [&](int /* c */) {
            if (count++ % million == 0) /* std::cout << c << "\n" */;
        });
    }
    std::cout << count << "\n";
}
