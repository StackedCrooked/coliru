#include <cstdint>
#include <type_traits>

template <int N>
struct int_type {
    using type = typename std::conditional<N <= 8, std::uint8_t,
                 typename std::conditional<N <= 16, std::uint16_t,
                 typename std::conditional<N <= 32, std::uint32_t,
                 typename std::conditional<N <= 64, std::uint64_t,
                 typename std::uintmax_t>::type>::type>::type>::type;
};

int main()
{
    int_type<10> i;
    (void)i;
}
