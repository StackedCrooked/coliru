#include <type_traits>
#include <cstdint>

template <int N>
struct int_type {
    using type = std::conditional_t<N <= 8, std::uint8_t,
                 std::conditional_t<N <= 16, std::uint16_t,
                 std::conditional_t<N <= 32, std::uint32_t,
                 std::conditional_t<N <= 64, std::uint64_t,
                 std::uintmax_t>>>>;
};

int main()
{
    int_type<10> t;
}