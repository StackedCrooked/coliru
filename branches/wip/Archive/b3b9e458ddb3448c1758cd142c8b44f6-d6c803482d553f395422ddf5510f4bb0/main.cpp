#include <iostream>
#include <cstdint>


struct word{
    uint16_t value;

    inline  word(uint16_t value) noexcept
        :value(value)
    {}

    word &operator=(uint16_t rhs) noexcept{
        value = rhs;
        return *this;
    }

    operator uint16_t&() noexcept{
        return value;
    }
};


int main() {
    word w1 = 5;
    //w1 = w1 + w1;  //this works fine due to implicit conversion
    w1 += w1; //fails to compile.  lhs will not implicitly convert
    
    std::cout << w1;
}