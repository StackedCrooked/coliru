#include <functional>
#include <iostream>
#include <string>
#include <cstdint>

using U64 = uint64_t;

// generate the next integer with the same number of bits as c
U64 next_combination(U64 c) 
{
    auto smallest = c & -c;
    auto ripple = c + smallest;
    auto ones = c ^ ripple;
    ones = (ones >> 2) / smallest;
    return ripple | ones;
}

// generate all integers with k of the first n bits set
U64 for_each_combination(std::size_t n, std::size_t k)
{
    U64 x, y;
    U64 count = 1;
    U64 const n_mask = (1ULL << n) - 1;
    U64 const k_mask = (1ULL << k) - 1;
    for (x = k_mask; (y = next_combination(x) & n_mask) > x; x = y)
        ++count;
    return count;
}

int main() 
{
    std::cout << for_each_combination(48, 8) << "\n";
}
