#include <iostream>
#include <type_traits>
#include <functional>
#include <bitset>

template <std::size_t N>
class bit_array;

namespace detail
{
    template <std::size_t N, typename E = void>
    struct closest_int;
    template <std::size_t N>
    struct closest_int<N, std::enable_if_t<(N > 0 && N <= 8)>>
    { using type = uint8_t; };
    template <std::size_t N>
    struct closest_int<N, std::enable_if_t<(N > 8 && N <= 16)>>
    { using type = uint16_t; };
    template <std::size_t N>
    struct closest_int<N, std::enable_if_t<(N > 16 && N <= 32)>>
    { using type = uint32_t; };
    template <std::size_t N>
    struct closest_int<N, std::enable_if_t<(N > 32 && N <= 64)>>
    { using type = uint64_t; };
    
    template <std::size_t N>
    struct wrapper
    {
        wrapper& operator =(bool const value)
        {
            /* Simple but makes my point. */
            if(value)
            { arr.get().data |= (1 << index); }
            else
            { arr.get().data &= ~(1 << index); }
            
            return *this;
        }
        
        std::reference_wrapper<bit_array<N>> arr;
        std::size_t index;
    };
}

template <std::size_t N>
struct bit_array
{
    auto operator [](std::size_t const i)
    { return detail::wrapper<N>{ *this, i }; }

    typename detail::closest_int<N>::type data;
};

/* Hack for easy printing. */
template <std::size_t N>
std::ostream& operator <<(std::ostream &os, bit_array<N> const &ba)
{ return os << (std::bitset<N>{ ba.data }).to_string(); }

int main()
{
    {
        bit_array<3> ba3{};
        
        std::cout << "ba3 size: " << sizeof(ba3) << " byte" << std::endl;
        std::cout << "contents: " << ba3 << std::endl;
        
        std::cout << "setting bit 2 of ba3" << std::endl;
        ba3[2] = true;
        std::cout << "contents: " << ba3 << std::endl;
    }
    std::cout << std::endl;
    {
        bit_array<17> ba17{};
        
        std::cout << "ba17 size: " << sizeof(ba17) << " bytes" << std::endl;
        std::cout << "contents: " << ba17 << std::endl;
        
        std::cout << "setting bits 2, 6, and 16 of ba17" << std::endl;
        ba17[2] = true; ba17[6] = true; ba17[16] = true;
        std::cout << "contents: " << ba17 << std::endl;
    }
}