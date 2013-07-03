#include <iostream>
#include <sstream>
#include <string>


struct ScopedHex
{    
    friend std::ostream& operator<<(std::ostream& os, const ScopedHex& hex)
    {
        hex.os_ptr = &os;
        return os << std::hex;
    }
    
    ~ScopedHex()
    {
        if (os_ptr) *os_ptr << std::dec;
    }
    
    mutable std::ostream* os_ptr;
};


int main()
{
    std::cout << "Using std::hex: " << std::endl;
    {
        std::cout << std::hex << 10 << std::endl;
        std::cout << 10 << std::endl;
    }


    std::cout << "\nUsing ScopedHex: " << std::endl;
    {
        std::cout << ScopedHex() << 10 << std::endl;
        std::cout << 10 << std::endl;
    }
}
