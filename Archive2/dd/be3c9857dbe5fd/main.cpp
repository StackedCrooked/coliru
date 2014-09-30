#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>
#include <algorithm>

typedef unsigned char byte;
typedef std::vector<byte> VectorOfByte;

template<typename T> T ExtractNumber(byte const * const p, size_t len)
{
   if ( sizeof( T ) < len )
   {
          std::string error("Type too small to contain data");
          throw std::runtime_error( error );
   }

    return std::accumulate(p, p + len, (T)0, 
       [](int total, int addition) { return (total << 8) + addition; });
}

template<typename T> T ExtractNumber(byte const * const p )
{
    return ExtractNumber<T>( p, sizeof(T) );
}

template<typename T> T ExtractNumber(VectorOfByte const & bytes )
{
    return ExtractNumber<T>( bytes.data(), sizeof(T) );
}

int main()
{
    const std::vector<unsigned char> bytes = { 1, 2, 3, 4 };
    const auto number = ExtractNumber<int>( bytes );
    const bool ok = number == 16909060;
    
    std::cout << std::boolalpha << ok << " - " << number << std::endl;
}
