#include <iostream>
#include <chrono>
#include <random>
#include <vector>
#include <algorithm>
#include <iterator>

using u64 = unsigned long long;
static_assert( sizeof(u64) == 8, "bad dimension" );

inline u64 pi ( u64 x)
{
    const unsigned char tab[64] ={58,50,42,34,26,18,10,2,60,52,44,36,28,20,12,4,62,54,46,38,30,22,14,6,0,56,48,40,32,24,16,8,57,49,41,33,25,17,9,1,59,51,43,35,27,19,11,3,61,53,45,37,29,21,13,5,63,55,47,39,31,23,15,7};
    u64 y=0;
    unsigned char i=0;
    while (i<64)
    {
        y=y|((x>>(tab[i]-1)&1)<<i);
        i++;
    }
    return y;
}

inline u64 pi2 ( u64 x )
{
    static const u64 tab[64] = { 1ull<<58,1ull<<50,1ull<<42,1ull<<34,1ull<<26,1ull<<18,1ull<<10,1ull<<2,1ull<<60
                               , 1ull<<52,1ull<<44,1ull<<36,1ull<<28,1ull<<20,1ull<<12,1ull<<4,1ull<<62,1ull<<54
                               , 1ull<<46,1ull<<38,1ull<<30,1ull<<22,1ull<<14,1ull<<6,1ull<<0,1ull<<56,1ull<<48
                               , 1ull<<40,1ull<<32,1ull<<24,1ull<<16,1ull<<8,1ull<<57,1ull<<49,1ull<<41,1ull<<33
                               , 1ull<<25,1ull<<17,1ull<<9,1ull<<1,1ull<<59,1ull<<51,1ull<<43,1ull<<35,1ull<<27
                               , 1ull<<19,1ull<<11,1ull<<3,1ull<<61,1ull<<53,1ull<<45,1ull<<37,1ull<<29,1ull<<21
                               , 1ull<<13,1ull<<5,1ull<<63,1ull<<55,1ull<<47,1ull<<39,1ull<<31,1ull<<23,1ull<<15,1ull<<7};
    u64 y {};
    for( size_t i {}, bit {1}; i != 64; ++i, bit<<=1 ) {
        y |= ( x & tab[i] ) ? bit : 0;
    }
    return y;
}

template < typename F >
inline void test( F f ) {
    size_t count = 100000;
    std::vector<u64> ins, outs;
    ins.resize( count );
    outs.resize( count );
    
    std::mt19937 gen( 42/*std::random_device{}()*/ );
    std::uniform_int_distribution<> dis;
    std::generate( std::begin( ins ), std::end( ins ), [&]() { return dis(gen); } );
    
    size_t loops = 100;
    
    auto t0 = std::chrono::high_resolution_clock::now();
    for ( size_t loop = 0; loop < loops; ++loop ) {
        std::transform( std::begin( ins ), std::end( ins ), std::begin( outs ), [=]( u64 v ) { return f(v); } );
        std::swap( ins, outs );
    }
    auto t1 = std::chrono::high_resolution_clock::now();
    
    std::cout << double(std::chrono::duration_cast<std::chrono::microseconds>(t1-t0).count())/1000.0 << "ms" << std::endl;
}
int main() {
    test(pi);
    test(pi2);
    
    unsigned int tab[64] ={58,50,42,34,26,18,10,2,60,52,44,36,28,20,12,4,62,54,46,38,30,22,14,6,64,56,48,40,32,24,16,8,57,49,41,33,25,17,9,1,59,51,43,35,27,19,11,3,61,53,45,37,29,21,13,5,63,55,47,39,31,23,15,7};
    std::sort( std::begin( tab ), std::end( tab ) );
    for( auto v : tab ) {
        std::cout << v << ",";
    }
}

