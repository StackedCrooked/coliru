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
  os << n.v << " sign " << n.fields.sign << " exp " << n.fields.exponent << " frac " << std::hex << n.fields.fraction << std::dec; 
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
    for (int i = 0; i < 33; ++i)
    {
    number.v = i;
    std::cout << number << std::endl;    
    }
}
