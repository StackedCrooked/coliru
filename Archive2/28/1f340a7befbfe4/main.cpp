#include <iomanip>
#include <iostream>
#include <vector>
#include <type_traits>


template<typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& vec)
{
    for (auto& el : vec)
    {
        os << el << ' ';
    }
    return os;
}


struct Byte
{
    Byte() = default;
    Byte(uint8_t value) : value_(value) {}
    
    friend std::ostream& operator<<(std::ostream& os, Byte b)
    {
        auto backup = os.flags();
        
        if (os.flags() & std::ios_base::hex)
        {
            os << std::setfill('0') << std::setw(2) << static_cast<int>(b.value_);
        }
        else
        {
            os << static_cast<int>(b.value_);
        }
        
        os.flags(backup);
        return os;
    }
    
    uint8_t value_;
};


int main()
{
    std::vector<Byte> b{ 9, 10, 15, 16 };
    
    std::cout << "dec: " << std::dec << b << std::endl;
    std::cout << "hex: " << std::hex << b << std::dec << std::endl;
    
    std::vector<Byte> ip = { 10, 0, 0, 1 };
    std::cout << ip << std::endl;
}
