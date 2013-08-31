#include <bitset>
#include <iostream>

// drop bits outside the range [R, L) == [R, L - 1]
template<std::size_t R, std::size_t L, std::size_t N>
std::bitset<N> project_range(std::bitset<N> b)
{
    static_assert(R <= L && L <= N, "invalid bitrange");
    b >>= R;            // drop R rightmost bits
    b <<= (N - L + R);  // drop L-1 leftmost bits
    b >>= (N - L);      // shift back into place
    return b;
}

int main()
{
    std::bitset<8> b2(42); // [0,0,1,0,1,0,1,0]
    std::cout << project_range<0,8>(b2).to_ulong() << "\n"; // 42 == entire bitset
    std::cout << project_range<2,5>(b2).to_ulong() << "\n"; // 8, only middle bit
}