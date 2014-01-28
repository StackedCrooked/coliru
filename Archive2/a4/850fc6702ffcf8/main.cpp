#include <iostream>
#include <iomanip>
#include <cstdint>

template <size_t Bit>
struct bit {
    bit(std::uint8_t& data)
        : data_{data} { }
    
    void
    set() {
        data_ |= 1 << Bit;
    }
    
    void
    clear() {
        data_ &= ~(1 << Bit);
    }
    
    bool
    test() {
        return data_ & (1 << Bit);
    }
    
private:
    std::uint8_t& data_;
};

struct status {
    std::uint8_t reg;
    
    bit<0> carry    {reg};
    bit<1> zero     {reg};
    bit<2> negative {reg};
    // ...
    
    status(std::uint8_t value) : reg{value} { }
};

int
main() {
    status s{0};
    s.carry.set();
    s.negative.set();
    std::cout << std::showbase << std::hex << +s.reg << '\n';
}
