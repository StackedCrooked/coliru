#include <cstdint>
#include <iomanip>
#include <iostream>
#include <random>
#include <boost/preprocessor/repetition/enum.hpp>
#include <boost/preprocessor/config/limits.hpp>

template<class = void>
class Zobrist
{
    static uint64_t gen_random() 
    {         
        static std::mt19937 engine;
        static std::uniform_int_distribution<uint64_t> dist;            
        return dist(engine);
    }
 
public:    


    static const uint64_t table[] ;

};

#ifndef PP_ZOBRIST_N
    #define PP_ZOBRIST_N BOOST_PP_LIMIT_REPEAT
#endif

#ifndef PP_RANDOM64
    #define PP_RANDOM64(z, i, data) gen_random()
#endif

template<class _>
const uint64_t Zobrist<_>::table[]= 
    { 
        BOOST_PP_ENUM(PP_ZOBRIST_N, PP_RANDOM64, ~)
    }; 

#undef PP_RANDOM64

int main()
{
    std::cout << PP_ZOBRIST_N << "\n";
    for (auto z : Zobrist<>::table)
        std::cout << std::hex << z << "\n";
}
