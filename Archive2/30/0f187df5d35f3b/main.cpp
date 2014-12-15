#include <type_traits>
#include <cstdint>

template <int N>
struct mytype {
    using type = typename std::conditional<N <= 8, std::uint8_t,
                 typename std::conditional<N <= 16, std::uint16_t,
                 typename std::conditional<N <= 32, std::uint32_t,
                 typename std::conditional<N <= 64, std::uint64_t,
                 typename std::uintmax_t>::type>::type>::type>::type;
};

int main() {
    mytype<16>::type n = 123.456;
}