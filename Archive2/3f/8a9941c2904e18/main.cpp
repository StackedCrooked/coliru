/* Public Domain Dedication
** License CC0 1.0 Universal (or any later version)
** http://creativecommons.org/publicdomain/zero/1.0/
**
** Written by olibre for stackoverflow question:
** http://stackoverflow.com/questions/809902/64-bit-ntohl-in-c
*/

#include <endian.h>    // __BYTE_ORDER
#include <algorithm>   // std::reverse

#include <iostream>    // std::cout
#include <iomanip>     // std::setw()


template <typename T>
constexpr T htonT( T value, char* ptr=0 ) noexcept
{
    return 
#if __BYTE_ORDER == __LITTLE_ENDIAN
     ptr = reinterpret_cast<char*>(& value), 
     std::reverse( ptr, ptr + sizeof(T) ),
#endif
    value;
}

int main()
{
  std::cout << std::hex;
  
  std::uint8_t uc = 'B';                  std::cout << std::setw(16) << uc <<'\n';
  uc = htonT( uc );                       std::cout << std::setw(16) << uc <<'\n';

  std::uint16_t us = 0x1122;              std::cout << std::setw(16) << us <<'\n';
  us = htonT( us );                       std::cout << std::setw(16) << us <<'\n';

  std::uint32_t ul = 0x11223344;          std::cout << std::setw(16) << ul <<'\n';
  ul = htonT( ul );                       std::cout << std::setw(16) << ul <<'\n';

  std::uint64_t ull = 0x1122334455667788; std::cout << std::setw(16) << ull <<'\n';
  ull = htonT( ull );                     std::cout << std::setw(16) << ull <<'\n';
  
  // in case 128 bits integer is available...
  std::intmax_t um = 0x1122334455667788;  std::cout << std::setw(16) << um <<'\n';
  um = htonT( um );                       std::cout << std::setw(16) << um <<'\n';
}
