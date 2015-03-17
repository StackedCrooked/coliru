#include <iostream>
#include <string>
#include <vector>

template<typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& vec)
{
    for (auto& el : vec)
    {
        os << el << ' ';
    }
    return os;
}

class YM2420Range {
    uint8_t address;
    uint8_t first_bit;
    uint8_t range;
    bool inverted;
  public:
    YM2420Range(
        uint8_t a, uint8_t b, uint8_t c, bool d): address(a), first_bit(b),
        range(c), inverted(d) {}
    uint8_t get_range() {
      return range;
    }
};

YM2420Range multi_sample_wave_carrier    (0x00, 0, 15, false);

int main()
{
    std::vector<std::string> words = {
        "Hello", "from", "GCC", __VERSION__, "!"
    };
    std::cout << multi_sample_wave_carrier.get_range() << std::endl;
}
