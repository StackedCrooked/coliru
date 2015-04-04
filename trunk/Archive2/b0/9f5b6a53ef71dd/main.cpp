#include <algorithm>
#include <array>
#include <cstring>
#include <type_traits>

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
    for (auto& byte : data) {
        byte = *begin++;
    }
    if (bo != byte_order::native) {
        std::reverse(data.begin(), data.end());
    }
    T result;
    std::memcpy(&result, data.data(), sizeof(result));
    return result;
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