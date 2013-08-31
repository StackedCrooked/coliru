#include <iostream>
#include <iomanip>
#include <stdint.h>

enum class Binary : bool { No, Yes };
enum class Text : bool { No, Yes };

template<typename T, Binary, Text>
struct Wrap
{
    const T & get() const { return obj_; }
    T obj_;    
};

template<Binary b, Text t>
using Octet = Wrap<unsigned char, b, t>;

using Byte  = Octet<Binary::Yes, Text::No >;
using Ascii = Octet<Binary::No , Text::Yes>;
using Mixed = Octet<Binary::Yes, Text::Yes>;


std::ostream& operator<<(std::ostream& os, Byte b)
{
    return os << std::hex << "0x" << std::setw(2) << std::setfill('0') << static_cast<int>(b.get()) << std::dec;
}

std::ostream& operator<<(std::ostream& os, Ascii b)
{
    return os << std::hex << "  " << b.get() << ' ' << std::dec;
}

std::ostream& operator<<(std::ostream& os, Mixed b)
{
    enum { first = 36, last = 126 };
    if (b.get() >= first && b.get() <= last)
    {
        return os << Ascii{b.get()};
    }
    else
    {
        return os << Byte{b.get()};
    }
}


int main()
{
    for (int i = 0; i != 256; ++i)
    {
        if (i%16 == 0) std::cout << std::endl;
        unsigned char c = i;
        std::cout << Mixed{c} << " ";
    }
}