#include <algorithm>
#include <array>
#include <cstring>
#include <type_traits>

template<typename R, typename I>
R memcpy_cast(I input) {
    static_assert(sizeof(R) == sizeof(I), "R and I must have the same size!");
    R result;
    std::memcpy(&result, &input, sizeof(result));
    return result;
}

enum class byte_order {
    big_endian,
    little_endian,
    network = big_endian,
    native = __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__ ? little_endian : big_endian,
};

template<typename T, typename It>
T read_integer(It begin, byte_order bo) {
    static_assert(std::is_integral<T>(), "read_integer can only read integers");
    std::array<char, sizeof(T)> data;
    std::copy_n(begin, data.size(), data.begin());
    if (bo != byte_order::native) {
        std::reverse(data.begin(), data.end());
    }
    return memcpy_cast<T>(data);
}

// example:
#include <cstdint>
#include <ios>
#include <iostream>
#include <vector>

int main() {
    std::vector<char> data{ 0x01, 0x02, 0x03, 0x04 };
    std::cout << std::hex << read_integer<std::uint32_t>(data.begin(), byte_order::big_endian) << '\n';
    return 0;
}