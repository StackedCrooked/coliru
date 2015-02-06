#include <algorithm>   //std::swap until C++11
#include <utility>     //std::swap since C++11
#include <iostream>    //std::cout
#include <iomanip>     //std::setw()

template <typename T>
static void htonT( T *input )
{
#if __BYTE_ORDER == __LITTLE_ENDIAN
    union U {
       T val;
       char c[sizeof(T)];
    };

    U *ptr = reinterpret_cast<U*>(input);

    for (std::size_t i = 0; i < sizeof(T)/2; i++)
    {
        std::swap( ptr->c[i], ptr->c[sizeof(T)-1 - i] );
    }
#endif
}

int main()
{
  std::cout << std::hex;
    
  std::uint8_t uc = 'B';                  std::cout << std::setw(16) << uc <<'\n';
  htonT( &uc );                           std::cout << std::setw(16) << uc <<'\n';

  std::uint16_t us = 0x1122;              std::cout << std::setw(16) << us <<'\n';
  htonT( &us );                           std::cout << std::setw(16) << us <<'\n';

  std::uint32_t ul = 0x11223344;          std::cout << std::setw(16) << ul <<'\n';
  htonT( &ul );                           std::cout << std::setw(16) << ul <<'\n';

  std::uint64_t ull = 0x1122334455667788; std::cout << std::setw(16) << ull <<'\n';
  htonT( &ull );                          std::cout << std::setw(16) << ull <<'\n';
  
  // in case 128 bits integer is available...
  std::intmax_t um = 0x1122334455667788; std::cout << std::setw(16) << um <<'\n';
  htonT( &um );                          std::cout << std::setw(16) << um <<'\n';
}
