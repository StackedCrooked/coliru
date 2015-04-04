#include <algorithm>
#include <array>
#include <cstring>
#include <istream>
#include <type_traits>

enum class byte_order {
    big_endian,
    little_endian,
    network = big_endian,
    native = __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__ ? little_endian : big_endian,
};

template<typename T>
T read_integer(std::istream& stream, byte_order bo) {
    static_assert(std::is_integral<T>(), "read_integer can only read integers");
    std::array<char, sizeof(T)> data;
    stream.read(data.data(), data.size());
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
#include <sstream>

int main() {
    std::istringstream stream("\x01\x02\x03\x04", std::ios_base::in | std::ios_base::binary);
    stream.exceptions(std::istream::badbit | std::istream::eofbit | std::istream::failbit);
    std::cout << std::hex << read_integer<std::uint32_t>(stream, byte_order::big_endian) << '\n';
    return 0;
}