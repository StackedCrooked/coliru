#include <cstdint>
#include <cstdio>


struct Byte
{
    Byte(const Byte&) = delete;
    Byte& operator=(const Byte&) = delete;
    
    template<typename T>
    Byte& operator=(T&& t)
    {
        puts(__PRETTY_FUNCTION__);
        value_ = t;
        return *this;
    }

    template<typename T>
    operator T() const
    {
        return value_;
    }

    std::uint8_t value_;
};


int main()
{
    Byte a { 0x0a };
    Byte b { 0x0b };

    a = b; // Which method or method sequence is invoked?
    a = 1; // Which method or method sequence is invoked?
}
