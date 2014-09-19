#include <stdint.h>
#include <type_traits>
#include <iostream>
#include <tuple>


template<typename T>
T switch_endianness(T t, typename std::enable_if<sizeof(T) == 1>::type* = 0)
{
    return t;
}

template<typename T>
T switch_endianness(T input, typename std::enable_if<sizeof(T) >= 2 && (sizeof(T) % 2) == 0>::type* = 0)
{
    typedef typename std::aligned_storage<sizeof(T)/2, sizeof(T)/2>::type Half;
    T result;
    static_cast<Half*>(static_cast<void*>(&result))[0] = switch_endianness(static_cast<Half*>(static_cast<void*>(&input))[1]);
    static_cast<Half*>(static_cast<void*>(&result))[1] = switch_endianness(static_cast<Half*>(static_cast<void*>(&input))[0]);
    return result;
}

template<typename T, typename U>
std::ostream& operator<<(std::ostream& os, std::pair<T, U> p)
{
    return os << p.first << p.second;
}

int main() {
    std::cout << std::hex << switch_endianness(0x01020304) << std::endl;
    std::cout << std::hex << switch_endianness(0x0102030405060708) << std::endl;
    
    // 2 x 64 -bit
    auto n128 = switch_endianness(std::pair<uint64_t, uint64_t>{ 0x0102030405060708,  0x090A0B0C0D0E0F00 });
    std::cout << std::hex << n128.first << n128.second << std::endl;
    
    // 32-bit + 2 x 16-bit
    auto tuple = switch_endianness(std::tuple<uint32_t, uint16_t, uint16_t>{ 0x01020304, 0x0506, 0x0708 });
    std::cout << std::hex << std::get<0>(tuple) << std::get<1>(tuple) << std::get<2>(tuple) << std::endl;
}
