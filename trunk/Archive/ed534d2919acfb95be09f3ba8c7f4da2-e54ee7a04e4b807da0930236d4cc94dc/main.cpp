#include <functional>
#include <stdint.h>


template<class Traits>
struct TCPOption
{
    typedef typename Traits::Value Value;    
    uint8_t code;
    uint8_t length;
    Value value;
};


struct WindowScale
{
    enum { Code = 3 };
    typedef uint16_t Value;
};


struct MaximumSegmentSize
{
    enum { Code = 4 };
    typedef uint16_t Value;
};


struct Timestamp
{
    enum { Code = 8 };
    
    struct Value
    {
        uint32_t a;
        uint32_t b;
    };
};


template<class Traits>
TCPOption<Traits> make(typename Traits::Value v = {})
{
    return { Traits::Code, sizeof(typename Traits::Value), v };
}


int main()
{
    make<WindowScale>(2);
    make<Timestamp>({1, 2});
}