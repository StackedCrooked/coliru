#include <algorithm>
#include <type_traits>
#include <iostream>

namespace detail {
    template<bool C>
        struct call_if { template<typename F> void operator<<(F) { } };

    template<>
        struct call_if<true> {
            template<typename F>
                void operator<<(F f) { f(); }
        };
}

#define static_if(cond) detail::call_if<cond>() << [&]

template<class Iter>
void reverse(Iter first, Iter last) {
    std::reverse(first, last);
}

uint32_t byteswap32(uint32_t& x) { return x; }
 
template<typename T>
void reverse(T& x)
{
    static_if(sizeof(T) == sizeof(uint32_t))
    {
        std::cout << "fast lane\n";
        *reinterpret_cast<uint32_t*>(&x) = byteswap32(*reinterpret_cast<uint32_t*>(&x));
    };
    static_if(sizeof(T) != sizeof(uint32_t))
    {
        std::cout << "slow lane\n";
        auto f = reinterpret_cast<unsigned char*>(&x);
        auto l = f + sizeof(T);
        return reverse(f,l);
    };
}
 
int main(int argc, char **argv) {
    char x = 0;
    
    reverse(x);
    
    return 0;
}
