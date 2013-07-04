#include <iomanip>
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


std::ostream& operator<<(std::ostream& os, uint8_t b)
{
    return os << std::hex << static_cast<int>(b);
}


struct DynamicBuffer : std::vector<uint8_t>
{
    using std::vector<uint8_t>::vector;
    
    // for convenience
    void append(const std::vector<uint8_t>& buf)
    {
        insert(end(), buf.begin(), buf.end());
    }
    
    // for convenience
    void prepend(const std::vector<uint8_t>& buf)
    {
        insert(begin(), buf.begin(), buf.end());
    }
};


int main()
{
    DynamicBuffer buf;
    
    std::vector<uint8_t> abc = { 0x0a, 0x0b, 0x0c };
    buf.prepend(abc);
    
    std::vector<uint8_t> def = { 0x0d, 0x0e, 0x0f };
    buf.append(def);
    
    std::cout << buf << std::endl;
}
