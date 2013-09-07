#include <iostream>
#include <string>
#include <vector>
#include <cstdint>
union IEEEF32
{
    float v;
    struct 
    {
      uint32_t fraction:23;
      uint32_t exponent:8;
      uint32_t sign:1;
    } fields;
};

std::ostream& operator<<(std::ostream& os, const IEEEF32& n)
{
  os << n.v << " sign " << n.sign << " exp " << n.exponent << " frac " << n.fraction;
  return os;
}

template<typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& vec)
{
    for (auto& el : vec)
    {
        os << el << ' ';
    }
    return os;
}

int main()
{
    std::vector<std::string> words = {
        "Hello", "from", "GCC", __VERSION__, "!"
    };
    std::cout << words << std::endl;
    IEEEF32 number;
    number.v = 1.0;
    std::cout << number << std::endl;    
}
