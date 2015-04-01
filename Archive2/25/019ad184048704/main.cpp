/* Public Domain Dedication
** License CC0 1.0 Universal (or any later version)
** http://creativecommons.org/publicdomain/zero/1.0/
**
** Written by olibre for stackoverflow question:
** http://stackoverflow.com/questions/809902/64-bit-ntohl-in-c
*/

#include <endian.h>    // __BYTE_ORDER and bswap macros
#include <iostream>    // std::cout
#include <iomanip>     // std::setw()

#if __BYTE_ORDER == __BIG_ENDIAN

template <typename T>
constexpr T
htonT( T value ) noexcept
{
    return value;
}

#else

template <typename T>
constexpr typename std::enable_if< sizeof(T) == 1, T >::type
htonT( T value ) noexcept
{
    return value;
}

template <typename T>
constexpr typename std::enable_if< sizeof(T) == 2, T >::type
htonT( T value ) noexcept
{
    return __bswap_constant_16(value); //htons(value);
}

template <typename T>
constexpr typename std::enable_if< sizeof(T) == 4, T >::type
htonT( T value ) noexcept
{
    return __bswap_constant_32(value); //htonl(value);
}

template <typename T>
constexpr typename std::enable_if< sizeof(T) == 8, T >::type
htonT( T value ) noexcept
{
    return __bswap_constant_64(value); //htobe64(value);
}

#endif


int main()
{
  std::cout << std::hex;
  
  constexpr uint8_t  a1 = 'B';                std::cout<<std::setw(16)<< a1 <<'\n';
  constexpr auto     b1 = htonT(a1);          std::cout<<std::setw(16)<< b1 <<'\n';

  constexpr uint16_t a2 = 0x1122;             std::cout<<std::setw(16)<< a2 <<'\n';
  constexpr auto     b2 = htonT(a2);          std::cout<<std::setw(16)<< b2 <<'\n';

  constexpr uint32_t a4 = 0x11223344;         std::cout<<std::setw(16)<< a4 <<'\n';
  constexpr auto     b4 = htonT(a4);          std::cout<<std::setw(16)<< b4 <<'\n';

  constexpr uint64_t a8 = 0x1122334455667788; std::cout<<std::setw(16)<< a8 <<'\n';
  constexpr auto     b8 = htonT(a8);          std::cout<<std::setw(16)<< b8 <<'\n';
}
