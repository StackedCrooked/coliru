#include <cassert>
#include <iostream>
#include <iomanip>
#include <vector>


namespace utils {


// Byte represents a byte.
// I didn't like using uint8_t because ostream prints it as as text char.
// Also it being a user-defined type enables ADL.
// ADL will even work for typedefs like: `using IPv4 = std::array<Byte, 4>;`
// Interoperation with char is convenient. This however, required me to also support `int` for disambiguation.
struct Byte
{
    Byte() = default;
    
    // int, char and unsigned char are the three
    // native types that can be converted to
    // Byte and vice-versa
    
    Byte(char c) : value_(c) {}
    
    Byte(unsigned char c) : value_(c) { }
    
    Byte(int n) : value_(n)
    {
        // not sure if assertion is desirable here
        // maybe unsigned roll-over mechanism is ok
        assert(n >= 0 && n <= unsigned_char(-1));
    }
    
    Byte& operator=(char n)
    {
        value_ = n;
        return *this;
    }
    
    Byte& operator=(unsigned char n)
    {
        value_ = n;
        return *this;
    }
    
    Byte& operator=(int n)
    {
        // not sure if assertion is desirable here
        // maybe unsigned roll-over mechanism is ok
        assert(n >= 0 && n <= unsigned_char(-1));
        value_ = n;
        return *this;
    }
    
    // this enables all operators like <, ==, etc...
    operator int() const { return value_; }
    operator char() const { return value_; }
    operator unsigned char() const { return value_; }
    
    typedef unsigned char unsigned_char;
    unsigned_char value_;
};


// Can be used with memcpy on raw network data
static_assert(std::is_pod<Byte>::value, "");


// Always print as hex. It's a reasonable default.
std::ostream& operator<<(std::ostream& os, Byte b)
{
    return os << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(b.value_);
}


// ADL also applies here
using Buffer = std::vector<Byte>;


// Printing a binary buffer can be useful.
// But be careful: blobs can be very large.
std::ostream& operator<<(std::ostream& os, const Buffer& buffer)
{
    for (auto& b : buffer)
    {
        if (&b != &buffer[0])
        {
            os << ' ';
        }
        os << b;
    }
    return os;
}


} // namespace utils



int main()
{
    using namespace utils;
    
    Buffer buf = { 0x01, 0x02, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c };
    
    Byte a = 0x0a;
    Byte b = 0x0b;
    
    // check if basic comparison compiles
    assert(a < b && b > a && a != b);
    
    std::cout << buf << std::endl;
    
}

