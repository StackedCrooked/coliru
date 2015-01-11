#include <array>
#include <iostream>

//////////////////////////////////////// INT SEQ
template<unsigned... Is> struct seq{};
template<unsigned N, unsigned... Is> struct gen_seq : gen_seq<N-1, N-1, Is...>{};
template<unsigned... Is> struct gen_seq<0, Is...> : seq<Is...>{};

//////////////////////////////////////// Concat
template<unsigned N1, unsigned... I1, unsigned N2, unsigned... I2>
constexpr std::array<char const, N1+N2-1> concat(char const (&a1)[N1], 
                                                 char const (&a2)[N2], 
                                                 seq<I1...>, 
                                                 seq<I2...>)
{
    return {{ a1[I1]..., a2[I2]... }};
}

template<unsigned N1, unsigned N2>
constexpr std::array<char const, N1+N2-1> concat(char const (&a1)[N1], char const (&a2)[N2])
{
    return concat(a1, a2, gen_seq<N1-1>{}, gen_seq<N2>{});
}

/////////////////////////////////////////////// Format things

int main(void)
{
    std::cout << concat("hello", "world").data() << std::endl;
    //std::cout << concat("hello", "world", "foo").data() << std::endl;
}
