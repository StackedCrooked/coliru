#include <iostream>

struct Int128
{
    __int128_t value;
};
    
std::ostream& operator<<(std::ostream& os, Int128 x)
{    
    auto const upper = int64_t(x.value >> 64);
    if (upper)
        os << upper; 
    os << int64_t(x.value);
}

int main()
{
  __int128 t = 1234567890;

  std::cout << Int128{t} << std::endl;

  return t;
}
